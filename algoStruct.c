#include "ssl.h"

t_algo	*createAlgoStruct(char *allAlgs)
{
	t_algo	*algo;
	t_algo	*head;
	char 	**allAlgsCpy;
	int		i;

	algo = (t_algo*)(malloc(sizeof(t_algo)));
	head = algo;
	allAlgsCpy = ft_strsplit(allAlgs, ' ');
	i = 0;
	while (i < ALGO_NUM)
	{
		algo->name = ft_strdup(allAlgsCpy[i]);
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
		ft_strdel(&algo->name);
		free(algo);
		algo = head;
	}
}
