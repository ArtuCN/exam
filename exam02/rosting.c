/*Assignment name  : rostring
Expected files   : rostring.c
Allowed functions: write, malloc, free
--------------------------------------------------------------------------------

Write a program that takes a string and displays this string after rotating it
one word to the left.

Thus, the first word becomes the last, and others stay in the same order.

A "word" is defined as a part of a string delimited either by spaces/tabs, or
by the start/end of the string.

Words will be separated by only one space in the output.

If there's less than one argument, the program displays \n.

Example:

$>./rostring "abc   " | cat -e
abc$
$>
$>./rostring "Que la      lumiere soit et la lumiere fut"
la lumiere soit et la lumiere fut Que
$>
$>./rostring "     AkjhZ zLKIJz , 23y"
zLKIJz , 23y AkjhZ
$>
$>./rostring "first" "2" "11000000"
first
$>
$>./rostring | cat -e
$
$> */

#include <unistd.h>
#include <stdlib.h>

int only_white_space(char *str, int i)
{
	while (str[i])
	{
		if (str[i] <= 32);
			return (0);
		i++;
	}
	return (1);
}

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;	
	return(i);
}

int other_word(char *str, int i)
{
	while (i >= 0 && str[i])
	{
		if (str[i] != 32)
			return (1);
		i--;
	}
	return (0);
}

void rosting (char *str)
{
	int i = 0;
	int x = 0;
	int y = 0;
	int z = 0;
	char *remaing_str;
	char *first_word;
	while (str[i] && str[i] <= 32)
		i++;
	remaing_str = malloc(ft_strlen(str) * sizeof(char) + 1);
	if (!first_word)
		return ;
	first_word = malloc(ft_strlen(str) * sizeof(char) + 1);
	if (!remaing_str)
	{
		free(first_word);
		return ;
	}
	while ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
		first_word[x++] = str[i++];
	first_word[x] = '\0';
	while (str[i])
	{
		while (str[i] && str[i] <= 32)
			i++;
		if (str[i - 1] <= 32 && other_word(str, i))
			remaing_str[z++] = ' ';
		remaing_str[z++] = str[i++];
		if (only_white_space(str, i))
			break ;
	}
	remaing_str[z] = '\0';
	write (1, remaing_str, z);
	if (x > 0)
		write(1, " ", 1);
	write (1, first_word, x);
	write (1, "\n", 1);
	free(first_word);
	free(remaing_str);
}

int main(int ac, char **av)
{
	if (ac < 2)
	{
		write (1, "\n", 1);
		return (0);
	}
	rosting (av[1]);
}