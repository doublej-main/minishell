/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:45:07 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/10 15:20:19 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_children_signal(void)
{
	set_sigaction(SIGINT, SIG_IGN, 0);
	set_sigaction(SIGQUIT, SIG_IGN, 0);
}

static void	sigint_hd(int sig)
{
	extern int	rl_done;

	(void)sig;
	g_sig = SIGINT;
	rl_done = 1;
	close(STDIN_FILENO);
}

void	signals_heredoc(void)
{
	g_sig = 0;
	set_sigaction(SIGINT, sigint_hd, 0);
	set_sigaction(SIGQUIT, SIG_IGN, 0);
}
