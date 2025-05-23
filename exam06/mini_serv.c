#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

int ft_strlen(char *str)
{
    int i = 0;
    if (str == NULL)
        return (0);
    while (*str != '\0')
    {
        i++;
        str++;
    }
    return (i);
}


int ft_error(char *str, char *obj, int ret)
{
    write(2, str, ft_strlen(str));
    if (obj != NULL)
        write(2, obj, ft_strlen(obj));
    return (ret);
}


int main(int ac, char **av)
{
    int sockfd;
    struct sockaddr_in servaddr;
    if (ac != 2)
        return (ft_error( "Wrong number of arguments\n", NULL, 1));
    int port = atoi(av[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        return(ft_error("fatal error\n", NULL, 1));
    
    //azzero qua tutta la struttura di servaddr
    bzero(&servaddr, sizeof(servaddr));
    
    //AF_INET = USERO IPV4
    servaddr.sin_family = AF_INET;

    // 127.0.0.1
    servaddr.sin_addr.s_addr = htonl(2130706433); 
    
    //dice che starò in ascolto su la porta che è stata inserita CAPIRE HOST TO NETWORK LONG E SHORT
    servaddr.sin_port = htons(port);

    //associamo il socket all'indirizzo ip
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        return (ft_error("Fatal error\n", NULL, 1));
    //adesso siamo pronti ad accettare connessioni su questa porta (quella che fu av[1])
    if (listen(sockfd, SOMAXCONN) < 0)
        return (ft_error("Fatal error\n", NULL, 1));

    while(1)
    {
        
    }
}