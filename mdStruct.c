#include "ssl.h"

t_md	*createMdStruct(t_md *lst)
{
	lst = (t_md*)malloc(sizeof(t_md));
	lst->a = 0;
	lst->aa = 0;
	lst->next = NULL;
	return (lst);
}

void	delMdStruct(t_md *md)
{
	int		i;
	t_md	*tmp;

	i = 0;
	while (i < 4)
	{
		tmp = md->next;
		free(md);
		md = tmp;
		i++;
	}
}
