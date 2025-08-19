/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:24:34 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/05/06 12:08:12 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conv_str(va_list ap)
{
	char	*arr;

	arr = va_arg(ap, char *);
	if (!arr)
		return (write(1, "(null)", 6));
	ft_putstr(arr);
	return (ft_strlen(arr));
}
