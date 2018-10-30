#include "ssl.h"

t_flags	*createFlagsStruct(void)
{
	t_flags	*flags;

	flags = (t_flags*)malloc(sizeof(t_flags));
	flags->p = 0;
	flags->q = 0;
	flags->r = 0;
	flags->s = 0;
	flags->d = 0;
	flags->e = 0;
	flags->i = 0;
	flags->o = 0;
	flags->algName = NULL;
	flags->algInd = -1;
	flags->file = 0;
	flags->stdin = 0;
	flags->hash = 0;
	flags->cipher = 0;
	return (flags);
}

void	delFlagsStruct(t_flags *flags)
{
	ft_strdel(&flags->algName);
	free(flags);
}
