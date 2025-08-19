/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:17:19 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/05/06 11:42:29 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conv_int(va_list ap)
{
	int	i;

	i = va_arg(ap, int);
	ft_putnbr(i);
	return (ft_numlen(i));
}
