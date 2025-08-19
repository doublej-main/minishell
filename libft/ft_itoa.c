/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:27:46 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/07/02 13:10:07 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lennum(int n)
{
	int			len;
	long int	nb;

	len = 0;
	nb = n;
	if (n == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*arr;
	char	*digits;
	int		len;

	len = ft_lennum(n);
	digits = "0123456789";
	arr = malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	arr[len] = 0;
	if (n == 0)
		arr[0] = '0';
	if (n < 0)
		arr[0] = '-';
	while (n)
	{
		if (n > 0)
			arr[--len] = digits[n % 10];
		else
			arr[--len] = digits[n % 10 * -1];
		n /= 10;
	}
	return (arr);
}
