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

int extract_message(char **buf, c
}

