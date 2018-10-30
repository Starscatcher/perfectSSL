#include "ssl.h"

void	startHashFunc(char *input, t_flags *flags, const t_alg *alg)
{
	if (flags->algInd < 4 && (flags->p || flags->s ) && !flags->q && !flags->file && !flags->r)
	{
		ft_print_upper(flags->algName);
		ft_printf(" (\"%s\") = ", input);
	}
	alg[flags->algInd](input, ft_strlen(input));
	if (flags->algInd < 4 && flags->r && !flags->q && !flags->file)
		ft_printf(" \"%s\"\n", input);
	else if (flags->algInd < 4 && flags->file)
		ft_printf(" %s\n", input);
	else if (flags->algInd < 4)
		ft_printf("\n");
}

void	startCipherFunc(char *input, t_flags *flags, const t_alg *alg)
{
	if (flags->d)
		flags->algInd++;
	alg[flags->algInd](input, ft_strlen(input));
}

void	findFunc(char *input, t_flags *flags)
{
	const t_alg alg[ALGO_NUM] = {MD5, SHA256, SHA224, SHA384, SHA512, BASE64, decBASE64};

	if (flags->hash)
		startHashFunc(input, flags, alg);
	else if (flags->cipher)
		startCipherFunc(input, flags, alg);
}
