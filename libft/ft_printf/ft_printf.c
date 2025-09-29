/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:42:58 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/05/14 11:37:09 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(va_list *ap, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar(va_arg(*ap, int));
	else if (c == 's')
		count += ft_putstr(va_arg(*ap, char *));
	else if (c == 'p')
		count += ft_convertptr(va_arg(*ap, void *));
	else if (c == 'd')
		count += ft_putnbr(va_arg(*ap, int));
	else if (c == 'i')
		count += ft_putnbr(va_arg(*ap, int));
	else if (c == 'u')
		count += ft_tohex(va_arg(*ap, unsigned int), 10, 0);
	else if (c == 'x')
		count += ft_tohex(va_arg(*ap, unsigned int), 16, 0);
	else if (c == 'X')
		count += ft_tohex(va_arg(*ap, unsigned int), 16, 1);
	else if (c == '%')
		count += ft_putchar('%');
	else
		return (-1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				return (va_end(ap), -1);
			count += print_format(&ap, *format);
		}
		else
			count += ft_putchar(*format);
		format++;
	}
	va_end(ap);
	return (count);
}
