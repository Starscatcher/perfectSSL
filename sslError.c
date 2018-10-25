#include "ssl.h"

void	algoError(t_algo *algo, char *arg)
{
	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", arg);
	ft_printf("Standard commands:\n\n");
	ft_printf("Message Digest commands:\n");
	while (algo)
	{
		ft_printf("%s\n", algo->name);
		algo = algo->next;
	}
	ft_printf("\nCipher commands:\n");
}

void	optionError(char *arg)
{
	ft_printf("unknown option '%s'\noptions are\n", arg);
	ft_printf("-p   echo STDIN to STDOUT ");
	ft_printf("and append the checksum to STDOUT\n");
	ft_printf("-r   reverse the format of the output\n");
	ft_printf("-q   quiet mode\n");
	ft_printf("-s   print the sum of the given string\n");
}

void	fileError(char *arg, t_flags *flags)
{
	ft_printf("ft_ssl: ");
	ft_printf("%s: ", flags->algName);
	ft_printf("%s: ", arg);
	ft_printf("No such file or directory\n");
}

void	usage()
{
	ft_printf("usage: ft_ssl command [command opts] [command args]\n");
}
