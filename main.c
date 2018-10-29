#include "ssl.h"

int main(int argc, char **argv)
{
	t_algo	*algo;
	t_flags	*flags;
	char	allAlgs[] = "md5 sha256 sha224 sha384 sha512 base64";

	algo = createAlgoStruct(allAlgs);
	flags = createFlagsStruct();
	readArgs(flags, algo, argc, argv);
	delAlgoStruct(algo);
	delFlagsStruct(flags);
}
