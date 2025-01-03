#include <unistd.h>

int	ft_atoi(char *str)
{
	int n = 0;

	while (*str != '\0')
	{
		n = n * 10;
		n = n + *str - '0';
		++str;
	}
	return (n);
}

void print_hex(int n)
{
	char base[] = "0123456789abcdef";

	if (n >= 16)
		print_hex(n / 16);
	write (1, &base[n % 16], 1);
}

int main(int ac, char **av)
{
	int num;

	if (ac == 2)
		print_hex(ft_atoi (av[1]));
	write(1, "\n", 1);
}