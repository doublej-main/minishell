/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_ptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:24:16 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/05/06 12:16:20 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conv_ptr(va_list ap)
{
	uintptr_t	address;
	char		*arr;
	int			len;

	address = (uintptr_t)va_arg(ap, void *);
	if (address == 0)
		return (write(1, "(nil)", 5));
	len = ft_uintlen(address, 16);
	arr = malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (-1);
	ft_hextoa(address, arr, 16, 0);
	ft_putstr("0x");
	ft_putstr(arr);
	free(arr);
	return (len + 2);
}
