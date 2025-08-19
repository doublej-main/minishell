/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:48:22 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/06/23 15:29:11 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char			*zero;
	unsigned char	*mem;
	size_t			total;

	if (nmemb == 0 || size == 0)
	{
		zero = malloc(1);
		return (zero);
	}
	else if (nmemb > 0x7FFFFFFF || size > 0x7FFFFFFF)
		return (NULL);
	total = nmemb * size;
	mem = malloc(total);
	if (!mem)
		return (NULL);
	ft_bzero(mem, total);
	return (mem);
}
