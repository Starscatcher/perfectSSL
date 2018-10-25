#include "ssl.h"

int findAlgo(t_algo *algo, t_flags *flags, char *arg)
{
	int i;

	i = 0;
	while (i < ALGO_NUM)
	{
		if (!ft_strcmp(algo->name, arg))
		{
			flags->algName = ft_strdup(algo->name);
			return (i);
		}
		algo = algo->next;
		i++;
	}
	return (-1);
}
