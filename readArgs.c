#include "ssl.h"

int		isFlag(t_flags *flags, char *arg)
{
	if (!strcmp("-p", arg))
		flags->p++;
	else if (!strcmp("-s", arg))
		flags->s++;
	else if (!strcmp("-q", arg))
		flags->q++;
	else if (!strcmp("r", arg))
		flags->r++;
	else if (arg[0] == '-')
		return (1);
	else
		return (0);
	return (1);
}

int		checkFile(char *name, t_flags *flags)
{
	int		fd;
	char	*file;

	fd = open(name, O_RDONLY);
	if (fd > 0)
	{
		flags->file++;
		file = readFd(fd);
		findHashFunc(file, flags);
		flags->file = 0;
		return (1);
	}
	else
		return (0);
}

void	readArgs(t_flags *flags, t_algo *algo, int argc, char **argv)
{
	int i;

	i = 1;
	if (argc == 1)
	{
		argv = fromStdin(&argc, flags);
		i = 0;
	}
	if ((flags->algInd = findAlgo(algo, flags, argv[i])) == -1)
		algoError(algo, argv[i]);
	i++;
	while (i < argc)
	{
		if (i == 1 && (flags->algInd = findAlgo(algo, flags, argv[i])) == -1)
		{
			algoError(algo, argv[i]);
			break;
		}
		else if (!isFlag(flags, argv[i]))
			optionError(argv[i]);
		else
		{
			if (flags->s && argv[i + 1])
			{
				i++;
				findHashFunc(argv[i], flags);
			}
			else if (flags->p)
				findHashFunc(readFd(0), flags);
			else if (!checkFile(argv[i], flags))
				fileError(argv[i], flags);
		}
		i++;
	}
	if (flags->stdin)
		ft_del_doublestr(&argv);
}
