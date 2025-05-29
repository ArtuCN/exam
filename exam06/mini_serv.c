#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>

typedef struct s_client {
    int id;
} t_client;

t_client *clients[FD_SETSIZE];
int max_fd = 0, next_id = 0;


void cleanup(int sockfd, int fatal) {
	if (fatal == 1)
	    write(2, "Fatal error\n", strlen("Fatal error\n"));
    if (sockfd != -1)
        close(sockfd);
    for (int i = 0; i <= max_fd; ++i) {
        if (clients[i])
        {
            close(i);
            free(clients[i]);
            clients[i] = NULL;
        }
    }
}//ok

void broadcast(int sender_fd, char *msg) {
    for (int i = 0; i <= max_fd; ++i) {
        if (clients[i] && i != sender_fd) {
            if (send(i, msg, strlen(msg), 0) < 0) {
                close(i);
                free(clients[i]);
                clients[i] = NULL;
            }
        }
    }
}//OK

int main(int argc, char **argv) {
    int sockfd = -1, connfd, port, r;
    struct sockaddr_in servaddr, cliaddr;
    fd_set active, read_fds;

    if (argc != 2) {
        write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
        exit(1);
    }

    port = atoi(argv[1]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        cleanup(sockfd, 1);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(2130706433);  // 127.0.0.1
    servaddr.sin_port = htons(port);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        cleanup(sockfd, 1);
    if (listen(sockfd, 10) < 0)
        cleanup(sockfd, 1);

    FD_ZERO(&active);
    FD_SET(sockfd, &active);
    max_fd = sockfd;

    while (1) 
    {
        read_fds = active;
        if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0)
            continue;

        for (int fd = 0; fd <= max_fd; ++fd) {
            if (FD_ISSET(fd, &read_fds)) 
            {
                if (fd == sockfd) 
                {
                    socklen_t len = sizeof(cliaddr);
                    connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
                    if (connfd < 0)
                        continue;
                    clients[connfd] = (t_client *)calloc(1, sizeof(t_client));
                    if (!clients[connfd])
                        cleanup(sockfd, 1);
                    clients[connfd]->id = next_id++;
                    FD_SET(connfd, &active);
                    if (connfd > max_fd)
                        max_fd = connfd;

                    char msg[64];
                    sprintf(msg, "server: client %d just arrived\n", clients[connfd]->id);
                    broadcast(connfd, msg);
                } 
                else 
                {
                    char buf[4096], msg[100000];
                    r = recv(fd, buf, sizeof(buf) - 1, 0);
                    if (r <= 0)
                    {
                        char left_msg[100];
                        sprintf(left_msg, "server: client %d just left\n", clients[fd]->id);
                        broadcast(fd, left_msg);
                        close(fd);
                        free(clients[fd]);
                        clients[fd] = NULL;
                        FD_CLR(fd, &active);
                    }
                    else
                    {
                        buf[r] = '\0';
                        int i = 0;
                        while (i < r) 
                        {
                            char line[5000];
                            int line_len = 0;

                            while (i < r && buf[i] != '\n') 
                            {
                                line[line_len++] = buf[i++];
                            }
                            if (i < r && buf[i] == '\n') 
                            {
                                i++;
                            }
                            line[line_len] = '\0';
                            sprintf(msg, "client %d: %s\n", clients[fd]->id, line);
                            broadcast(fd, msg);
                        }
                    }
                }
            }
        }
    }

    cleanup(sockfd, 0);
    return 0;
}

/*
| Variabile  | Tipo                 | Descrizione                                                         |
| ---------- | -------------------- | ------------------------------------------------------------------- |
| `sockfd`   | `int`                | Socket principale del server (usato per `bind`, `listen`, `accept`) |
| `connfd`   | `int`                | Socket creato da `accept()` per ogni nuovo client                   |
| `port`     | `int`                | Porta del server (ottenuta da `argv[1]`)                            |
| `r`        | `int`                | Valore di ritorno di `recv()` (lunghezza dei dati ricevuti)         |
| `servaddr` | `struct sockaddr_in` | Indirizzo e porta del server per il `bind()`                        |
| `cliaddr`  | `struct sockaddr_in` | Indirizzo del client connesso (da `accept()`)                       |
| `active`   | `fd_set`             | Set di file descriptor attivi, gestito da `select()`                |
| `read_fds` | `fd_set`             | Copia temporanea di `active`, usata a ogni ciclo `select()`         |
*/