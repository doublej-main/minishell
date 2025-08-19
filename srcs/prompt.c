/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:43:37 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/08/19 15:07:27 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_prompt(int status)
{
	char	*num;
	char	*t;
	char	*s;

	num = ft_itoa(status);
	if (!num)
		return (NULL);
	t = ft_strjoin("minishell ", num);
	free(num);
	if (!t)
		return (NULL);
	s = ft_strjoin(t, "> ");
	free(t);
	return (s);
}
