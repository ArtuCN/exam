#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/ip.h>

int		count = 0, max_fd = 0;
int		ids[65536];
char	*msgs[65536];

fd_set	rfds, wfds, afds;
char	buf_read[1001], buf_write[42];

// START COPY-PASTE FROM GIVEN MAIN

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}


// END COPY-PASTE
void fatal_error()
{
    write(2, "Fatal error\n", 12);
    exit(1);
}

void notify_other(int author, char *str)
{
    for (int i = 0; i <= max_fd; i++)
    {
        if (FD_ISSET(i, &wfds) && i != author)
        {
            send(i, str, strlen(str), 0);
        }
    }
}

void register_client(int fd)
{
    if (fd > max_fd)
        max_fd = fd;
    ids[fd] = count++;
    msgs[fd] = NULL;
    FD_SET(fd, &afds);
    sprintf(buf_write, "server: client %d has arrived\n", ids[fd]);
    notify_other(fd, buf_write);
}

void remove_client(int fd)
{
    sprintf(buf_write, "server: client %d has left\n", ids[fd]);
    notify_other(fd, buf_write);
    free(msgs[fd]);
    FD_CLR(fd, &afds);
    close(fd);
}

void send_msg(int fd)
{
    char *msg;
    while (extract_message(&(msgs[fd]), &msg))
    {
        sprintf(buf_write, "client %d: %s", ids[fd], msg);
        notify_other(fd, buf_write);
        notify_other(fd, msg);
        free(msg);
    }
}

int create_socket()
{
    max_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (max_fd < 0)
        fatal_error();
    FD_SET(max_fd, &afds);
    return max_fd;
}

int main (int ac, char **av)
{
    if (ac != 2)
    {
        write(2, "wrong arguments input\n", 22);
        exit(1);
    }
    FD_ZERO(&afds);
    int sockfd;
    struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(2130706433);
    servaddr.sin_port = htons(atoi(av[1]));

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)))
		fatal_error();
	if (listen(sockfd, SOMAXCONN)) // the main uses 10, SOMAXCONN is 180 on my machine
		fatal_error();

    while(1)
    {
        rfds = wfds = afds;
        
        if (select(max_fd + 1, &rfds, &wfds, NULL, NULL) < 0)
            fatal_error();

        for (int fd = 0; fd < max_fd; fd++)
        {
            if (!FD_ISSET(fd, &rfds))
                continue;

            if (fd == sockfd)
            {
                socklen_t addr_len = sizeof(servaddr);
                int client_fd = accept(sockfd, (struct sockaddr *)&servaddr, &addr_len);
                if (client_fd >= 0)
                {
                    register_client(client_fd);
                    break ;
                }
            }
            else
            {
                int read_bytes = recv(fd, buf_read, 1000, 0);
                if (read_bytes <= 0)
                {
                    remove_client(fd);
                    break ;
                }
                buf_read[read_bytes] = '\0';
                msgs[fd] = str_join(msgs[fd], buf_read);
                send_msg(fd);
            }
        }
    }
    return 0;

}