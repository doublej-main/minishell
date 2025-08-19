/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:10:04 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/06/23 15:29:44 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*haystack;
	const char	*needle;
	size_t		i;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (*big && len > 0)
	{
		haystack = big;
		needle = little;
		while (*haystack && *needle && (*haystack == *needle))
		{
			haystack++;
			needle++;
			i++;
		}
		if (!*needle && i <= len)
			return ((char *)big);
		i = 0;
		big++;
		len--;
	}
	return (0);
}
