/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:27:59 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/05/06 14:40:07 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef int	(*t_conv)(va_list);

int			ft_printf(const char *format, ...);
int			ft_vprintf(const char *format, va_list ap);
int			conv_char(va_list ap);
int			conv_str(va_list ap);
int			conv_int(va_list ap);
int			conv_ptr(va_list ap);
int			conv_uint(va_list ap);
int			conv_hexlow(va_list ap);
int			conv_hexup(va_list ap);
void		ft_putchar(char c);
void		ft_putnbr(int n);
int			ft_numlen(int n);
size_t		ft_strlen(const char *s);
void		ft_putstr(char *s);
int			ft_uintlen(uint64_t n, int base);
char		*ft_hextoa(uint64_t n, char *arr, int base, int upper);

#endif