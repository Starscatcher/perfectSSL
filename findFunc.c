#include "ssl.h"

void	findFunc(char *input, t_flags *flags)
{
	const t_alg alg[ALGO_NUM] = {MD5, SHA256, SHA224, SHA384, SHA512, BASE64};

	alg[flags->algInd](input, flags);
}
