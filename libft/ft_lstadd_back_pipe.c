#include "libft.h"

static t_pl	*ft_lstlast_pipe(t_pl *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_pipe(t_pl **lst, t_pl *new)
{
	t_pl	*last;

	if (!lst || !new)
		return ;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_pipe(*lst);
	if (last)
		last->next = new;
}
