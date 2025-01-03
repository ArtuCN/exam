#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
	if (!str)
		return 0;
	int i = -1;
	while (str[++i])
		;
	return i;
}

void print_error(char *str, char *arg)
{
	write(2, str, ft_strlen(str));
	if (arg)
		write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}

int ft_execute(char **av, int i, int tmp, char **envp)
{
	av[i] = NULL;
	dup2(tmp, 0);
	close(tmp);
	execve(av[0], av, envp);
	print_error("error: cannot execute ", av[0]);
	exit(1);
}

int main(int ac, char **av, char **envp)
{
	int i = 0;
	int fd[2];
	int tmp;
	(void)ac;

	while (av[i] && av[i + 1])
	{
		av = &av[i + 1];
		i = 0;
		while (av[i] && strcmp(av[i], ";") == 0 && strcmp(av[i], "|") == 0)
			i++;
		if (strcmp(av[0], "cd") == 0)
		{
			if (i != 2)
				print_error("error: cd: bad arguments\n", NULL);
			else if (chdir(av[1]) == -1)
				print_error("error: cd: cannot change directory to ", av[1]);
		}
		else if (i != 0 && (strcmp(av[i], NULL) == 0 || strcmp(av[i], ";") == 0))
		{
			if (fork() != 0)
				ft_execute(av, i, tmp, envp);
			else
			{
				close(tmp);
				while (waitpid(-1, NULL, 2) != -1)
					;
				tmp = dup(0);
			}
		}
		else if (i != 0 && strcmp(av[i], "|") == 0)
		{
			if (pipe(fd) != 0)
			{
				print_error("error: pipe failed\n", NULL);
				exit(1);
			}
			if (fork() == 0)
			{
				dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
				ft_execute(av, i, tmp, envp);
			}
			else
			{
				dup2(fd[0], 0);
				close(fd[0]);
				close(fd[1]);
				close(tmp);
				while (waitpid(-1, NULL, 2) != -1)
					;
				tmp = dup(0);
			}
		}
	}
	close(tmp);
}