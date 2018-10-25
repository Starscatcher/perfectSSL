#include "ssl.h"

size_t	algoLen(const char *allAlgs)
{
	size_t len;

	len = 0;
	while (allAlgs[len] != ' ' && allAlgs[len] != '\0')
		len++;
	return (len);
}

t_algo	*put2Algo(t_algo *algo, const char *allAlgs, int *i)
{
	size_t j;
	size_t len;

	j = 0;
	len = algoLen(allAlgs + *i);
	algo->name = ft_strnew(len);
	while (j < len)
	{
		algo->name[j] = allAlgs[*i];
		j++;
		++*i;
	}
	++*i;
	return (algo);
}

t_algo	*createAlgoStruct(char *allAlgs)
{
	t_algo	*algo;
	t_algo	*head;
	int		i;
	int		j;

	algo = (t_algo*)(malloc(sizeof(t_algo)));
	head = algo;
	i = 0;
	j = 0;
	while (i < ALGO_NUM)
	{
		put2Algo(algo, allAlgs, &j);
		i++;
		if (i == ALGO_NUM)
			algo->next = NULL;
		else
			algo->next = (t_algo*)(malloc(sizeof(t_algo)));
		algo = algo->next;
	}
	return (head);
}

void	delAlgoStruct(t_algo *algo)
{
	t_algo *head;

	head = algo;
	while (head)
	{
		head = algo->next;
		free(algo);
		algo = head;
	}
}
