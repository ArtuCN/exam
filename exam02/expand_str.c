/*Assignment name  : expand_str
Expected files   : expand_str.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays it with exactly three spaces
between each word, with no spaces or tabs either at the beginning or the end,
followed by a newline.

A word is a section of string delimited either by spaces/tabs, or by the
start/end of the string.

If the number of parameters is not 1, or if there are no words, simply display
a newline.

Examples:

$> ./expand_str "See? It's easy to print the same thing" | cat -e
See?   It's   easy   to   print   the   same   thing$
$> ./expand_str " this        time it      will     be    more complex  " | cat -e
this   time   it   will   be   more   complex$
$> ./expand_str "No S*** Sherlock..." "nAw S*** ShErLaWQ..." | cat -e
$
$> ./expand_str "" | cat -e
$
$>
*/

#include <unistd.h>
#include <stdio.h>

int still_word(char *str, int i)
{
	while (str[i])
	{
		if (str[i] > 32)
			return 1 ;
		i++;
	}
	return (0);
}

int main (int ac, char **av)
{
	if (ac != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	int i = 0;
	if (!still_word(av[1], 0))
	{
		write(1, "\n", 1);
		return(0);
	}
	int len = 0;
	while (av[1][len])
		len++;
	av[1][len] = '\0';
	while (av[1][i] == ' ' || av[1][i] == '\t' )
		i++;
	while (i < len)
	{
		if (av[1][i] <= 32 && still_word(av[1], i))
		{
			write(1, "   ", 3);
			while (av[1][i] <= 32)
				i++;
		}
		else if (av[1][i])
		{
			write(1, &av[1][i], 1);
			i++;
		}
		if (!still_word(av[1], i))
			break ;
	}
	write (1, "\n", 1);
}