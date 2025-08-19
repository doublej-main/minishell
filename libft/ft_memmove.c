/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:49:51 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/04/16 11:50:18 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*src_arr;
	unsigned char		*dest_arr;

	src_arr = src;
	dest_arr = dest;
	if (dest_arr <= src_arr)
	{
		while (n > 0)
		{
			*dest_arr++ = *src_arr++;
			n--;
		}
	}
	else if (dest_arr > src_arr)
	{
		dest_arr += n - 1;
		src_arr += n - 1;
		while (n > 0)
		{
			*dest_arr-- = *src_arr--;
			n--;
		}
	}
	return (dest);
}
