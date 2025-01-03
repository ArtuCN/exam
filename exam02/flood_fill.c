#include <stdio.h>
#include <stdlib.h>

typedef struct s_point
{
	int x;
	int y;
}t_point;


void flood_fill(char **tab, t_point size, t_point begin)
{
	t_point new_begin;
	if (begin.x < 0 || begin.x >= size.y || begin.y < 0 || begin.y >= size.x)
        return;
	if (tab[begin.x][begin.y] == 'F' || tab[begin.x][begin.y] == '0')
		return ;
	else
		tab[begin.x][begin.y] = 'F';
	if (begin.x + 1 >= 0 && begin.y + 1 < size.y)
	{
		new_begin.x = begin.x + 1;
		new_begin.y = begin.y;
		flood_fill(tab, size, new_begin);
	}
	if (begin.x - 1 >= 0 && begin.x - 1 < size.y)
	{
		new_begin.x = begin.x - 1;
		new_begin.y = begin.y;
		flood_fill(tab, size, new_begin);
	}
	if (begin.y + 1 >= 0 && begin.y + 1 < size.x)
	{
		new_begin.x = begin.x;
		new_begin.y = begin.y + 1;
		flood_fill(tab, size, new_begin);
	}
	if (begin.y - 1 >= 0 && begin.y - 1 < size.x)
	{
		new_begin.x = begin.x;
		new_begin.y = begin.y - 1;
		flood_fill(tab, size, new_begin);
	}
}

char** make_area(char** zone, t_point size)
{
	char **new;

	new = malloc(sizeof(char*) * size.y);
	for (int i = 0; i < size.y; ++i)
	{
		new[i] = malloc(size.x + 1);
		for (int j = 0; j < size.x; ++j)
			new[i][j] = zone[i][j];
		new[i][size.x] = '\0';
	}

	return new;
}

int main(void)
{
	t_point size = {8, 5};
	char *zone[] = {
		"11111111",
		"10001001",
		"10000001",
		"10110001",
		"11111111",
	};

	char**  area = make_area(zone, size);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	printf("\n");

	t_point begin = {0, 0};
	flood_fill(area, size, begin);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	return (0);
}
