
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int		*ft_range(int start, int end)
{
	int		*range;
	int		i;

	if (start > end)
		range = (int *)malloc(sizeof(int) * (start - end) + 1);
	else
		range = (int *)malloc(sizeof(int) * (end - start) + 1);
	i = 0;
	while (start != end)
	{
		range[i++] = start;
		start += (start > end) ? -1 : 1;
	}
	range[i] = start;
	return (range);
}

int main()
{
	int start = -5;
	int end = -10;

	int *result = ft_range(start, end);

	printf("Range: ");
	for (int i = 0; i <= abs(start - end); ++i)
		printf("%d ", result[i]);
	printf("\n");

	free(result); // No te olvides de liberar la memoria asignada dinámicamente

	return 0;
}