#include <unistd.h>

int ft_atoi(char *str)
{
	int neg = 1;
	int num = 0;
	int i = 0;

	if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		num = (num * 10) + (str[i++] - 48);
	}
	return (num * neg);
}

void put_num(int num)
{
	if (num < 0)
	{
		num *= -1;
		write(1, "-", 1);
	}
	if(num >= 10)
		put_num(num / 10);
	char c = (num % 10) + 48;
	write(1, &c, 1);
}

int main(int ac, char **av)
{
	int n = ft_atoi(av[1]);
	int len = 0;
	int t = n;
	if (ac == 2)
	{
		if (t == 0)
			len = 1;
		while (t != 0)
		{
			if (t < 0)
			{
				len++;
				t *= -1;
			}
			len++;
			t /= 10;
		}
		int i = 0;
		while (++i < 10)
		{
			put_num(i);
			write (1, " x ", 3);
			put_num(n);
			write (1, " = ", 3);
			put_num(n * i);
			write (1, "\n", 1);
		}
	}
	write(1, "\n", 1);
}
