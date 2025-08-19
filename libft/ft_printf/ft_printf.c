/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:36:57 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/05/06 12:54:19 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_conv	g_conv[128] = {
['c'] = conv_char,
['s'] = conv_str,
['p'] = conv_ptr,
['d'] = conv_int,
['i'] = conv_int,
['u'] = conv_uint,
['x'] = conv_hexlow,
['X'] = conv_hexup,
['%'] = NULL,
};

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		written;

	va_start(ap, format);
	written = ft_vprintf(format, ap);
	va_end(ap);
	return (written);
}

int	ft_vprintf(const char *format, va_list ap)
{
	int	total;

	total = 0;
	while (*format)
	{
		if (*format != '%')
		{
			write(1, format, 1);
			++total;
		}
		else
		{
			++format;
			if (*format == '%')
			{
				write(1, "%", 1);
				++total;
			}
			else if (g_conv[(int)*format])
				total += g_conv[(int)*format](ap);
		}
		++format;
	}
	return (total);
}
