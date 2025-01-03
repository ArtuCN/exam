#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 2222
#endif

char *fstrchr(char *s, char c)
{
	while(*s)
	{
		if(*s == c)
			return(s);
		s++;
	}
	return(NULL);
}

int ft_strlen(char *s)
{
	int i = 0;
	while(s[i])
		i++;
	return(i);
}

char *ft_strdup(char *s)
{
	char *x = malloc(ft_strlen(s)+1);
	int i = 0;
	while(s[i])
	{
		x[i] = s[i];
		i++;
	}
	x[i] = '\0';
	return x;
}

char *ft_strjoin(char *s1, char *s2)
{
	if(!s1 || !s2)
		return(NULL);
	int len1 = ft_strlen(s1);
	int len2 = ft_strlen(s2);
	char *new = malloc(len1+len2+1);
	int i = 0;
	int x = 0;
	while(s1[i])
	{
		new[x] = s1[i];
		i++;
		x++;
	}
	i=0;
	while(s2[i])
	{
		new[x] = s2[i];
		i++;
		x++;
	}
	free(s1);
	new[x] = '\0';
	return(new);
}

char *get_next_line(int fd)
{
	static char cont[BUFFER_SIZE+1];
	char *line;
	char *next_line;
	int letti;
	int	size;

	line = ft_strdup(cont);
	while(!(fstrchr(line, '\n')) && (letti = read(fd, cont, BUFFER_SIZE)) > 0)
	{
		cont[letti] = '\0';
		line = ft_strjoin(line, cont);
	}
	if(ft_strlen(line) == 0)
		return(free(line),NULL);

	next_line = fstrchr(line, '\n');
	int i = 1;
	int x = 0;
	if(next_line != NULL)
	{
		size = next_line - line +1;
		while(x < BUFFER_SIZE+1)
			cont[x++] = '\0';
		x=0;
		while(next_line[i] && x < BUFFER_SIZE+1)
			cont[x++] = next_line[i++];
	}	
	else
	{
		size = ft_strlen(line);
		while(x < BUFFER_SIZE+1)
			cont[x++] = '\0';
	}
	line[size] = '\0';
	return(line);
}


int main()
{
    int fd = open("../test", O_RDONLY);
    char *line;

    if (fd < 0)
    {
        printf("Could not open file\n");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return (0);
}
