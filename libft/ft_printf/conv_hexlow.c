/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_hexlow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:13:26 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/05/06 14:59:48 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conv_hexlow(va_list ap)
{
	unsigned int	n;
	char			*arr;
	int				len;

	n = va_arg(ap, unsigned int);
	len = ft_uintlen(n, 16);
	arr = malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (write(1, "(null)", 6));
	ft_hextoa(n, arr, 16, 0);
	ft_putstr(arr);
	free(arr);
	return (len);
}
