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
			if (i < HASH_NUM)
				flags->hash++;
			else if (i >= HASH_NUM && i < HASH_NUM + CIPHER_NUM)
				flags->cipher++;
			return (i);
		}
		algo = algo->next;
		i++;
	}
	return (-1);
}
