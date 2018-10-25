#include "ssl.h"

void	findHashFunc(char *input, t_flags *flags)
{
	const t_alg alg[3] = {MD5, SHA256, SHA256};
	alg[flags->algInd](input, flags);
}
