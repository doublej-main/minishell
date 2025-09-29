/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:08:33 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/05/08 16:02:31 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int	ft_putchar(int c);
int	ft_putstr(char *s);
int	ft_numlen(int nbr, unsigned int base);
int	ft_putnbr(int nb);
int	ft_tohex(unsigned long int n, unsigned long int base, int type);
int	ft_convertptr(void *p);
int	print_format(va_list *ap, char c);
int	ft_printf(const char *format, ...);

#endif
