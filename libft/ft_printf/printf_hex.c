/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:38:48 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/05/08 16:20:33 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_tohex(unsigned long int n, unsigned long int base, int type)
{
	char	*hexlow;
	char	*hexup;
	int		numlen;

	numlen = 0;
	hexlow = "0123456789abcdef";
	hexup = "0123456789ABCDEF";
	if (type == 1)
		hexlow = hexup;
	if (n >= base)
	{
		numlen += ft_tohex(n / base, base, type);
		ft_putchar(hexlow[n % base]);
	}
	else
		ft_putchar(hexlow[n % base]);
	numlen++;
	return (numlen);
}

int	ft_convertptr(void *p)
{
	uintptr_t	address;

	address = (uintptr_t) p;
	if (address == 0)
		return (ft_putstr("(nil)"));
	ft_putstr("0x");
	return (ft_tohex(address, 16, 0) + 2);
}
