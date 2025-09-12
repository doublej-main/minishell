/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:11:34 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/09/10 15:04:51 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_token *lst)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = (t_token *)lst;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
