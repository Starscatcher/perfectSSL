#include "ssl.h"

void	clearFlags(t_flags * flags)
{
	flags->p = 0;
	flags->s = 0;
}

void	startHashFunc(char *input, t_flags *flags, const t_alg *alg)
{
	if (flags->p)
		ft_printf("%s", input);
	else if (!flags->q && flags->s && !flags->file && !flags->r)
	{
		ft_print_upper(flags->algName);
		ft_printf(" (\"%s\") = ", input);
	}
	alg[flags->algInd](input, ft_strlen(input));
	if (!flags->q && flags->r && !flags->file && !flags->p)
		ft_printf(" \"%s\"\n", input);
	else if (!flags->q && flags->file)
		ft_printf(" %s", input);
	else
		ft_printf("\n");
	clearFlags(flags);
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
