/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:27:46 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/05/06 12:50:41 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_hextoa(uint64_t n, char *arr, int base, int upper)
{
	char	*digits;
	char	*upper_digits;
	int		len;

	len = ft_uintlen(n, base);
	upper_digits = "0123456789ABCDEF";
	digits = "0123456789abcdef";
	if (upper == 1)
		digits = upper_digits;
	arr[len] = 0;
	if (n == 0)
		arr[0] = '0';
	while (n)
	{
		if (n > 0)
			arr[--len] = digits[n % base];
		else
			arr[--len] = digits[n % base * -1];
		n /= base;
	}
	return (arr);
}
