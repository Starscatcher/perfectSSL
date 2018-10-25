#include "ssl.h"

int		findArgc(char **argv)
{
	int size;

	size = 0;
	while (argv && argv[size])
		size++;
	return (size);
}

char	**fromStdin(int *argc, t_flags *flags)
{
	char **argv;
	char *input;

	input = readFd(0);
	argv = sslSplit(input, ' ');
	*argc = findArgc(argv);
	flags->stdin++;
	if (!*argc)
		usage();
	return (argv);
}
