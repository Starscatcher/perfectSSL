#include "ssl.h"

int		isFlag(t_flags *flags, char *arg)
{
	if (flags->hash && !strcmp("-p", arg)) // hash
		flags->p++;
	else if (flags->hash && !strcmp("-s", arg))
		flags->s++;
	else if (flags->hash && !strcmp("-q", arg))
		flags->q++;
	else if (flags->hash && !strcmp("-r", arg))
		flags->r++;
	else if (flags->cipher && !strcmp("-d", arg)) // cipher
		flags->d++;
	else if (flags->cipher > 4 && !strcmp("-e", arg))
		flags->e++;
	else if (flags->cipher > 4 && !strcmp("-i", arg))
		flags->i++;
	else if (flags->cipher > 4 && !strcmp("-o", arg))
		flags->o++;
	else if (arg[0] == '-')
		return (0);
	else if (arg[0] != '-')
		return (-1);
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
		findFunc(file, flags);
		return (1);
	}
	else
		return (0);
}

int 	hashRead(t_flags *flags, char **argv, int *i)
{
	if (!argv[*i])
		findFunc(readFd(0), flags);
	else if (((isFlag(flags, argv[*i])) == -1 || flags->file) && !checkFile(argv[*i], flags))
		fileError(argv[*i], flags);
	else if (!flags->file && flags->s && argv[*i + 1])
	{
		++*i;
		findFunc(argv[*i], flags);
	}
	else if (!flags->file && flags->p)
		findFunc(readFd(0), flags);
	return (1);
}

int 	cipherRead(t_flags *flags)
{
	findFunc(readFd(0), flags);
	return (1);
}

void	readArgs(t_flags *flags, t_algo *algo, int argc, char **argv)
{
	int i;
	int first;

	first = 0;
	i = 1;
	if (argc == 1)
	{
		argv = fromStdin(&argc, flags);
		i = 0;
	}
	if ((flags->algInd = findAlgo(algo, flags, argv[i])) == -1)
	{
		algoError(algo, argv[i]);
		return ;
	}
	i++;
	while (i < argc || !first)
	{
		if (i < argc && !isFlag(flags, argv[i]))
		{
			optionError(argv[i]);
			break ;
		}
		if (flags->hash)
			hashRead(flags, argv, &i);
		else if (flags->cipher)
			cipherRead(flags);
		i++;
		first++;
	}
	if (flags->stdin)
		ft_del_doublestr(&argv);
}
