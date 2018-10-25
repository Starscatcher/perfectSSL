#include "ssl.h"

int main(int argc, char **argv)
{
	t_algo	*algo;
	t_flags	*flags;
	char	*allAlgs;

	allAlgs = ft_strdup("md5 sha256 whirlpool");
	algo = createAlgoStruct(allAlgs);
	flags = createFlagsStruct();
	ft_strdel(&allAlgs);
	readArgs(flags, algo, argc, argv);
	delAlgoStruct(algo);
	//delFlagsStruct(flags);
}
