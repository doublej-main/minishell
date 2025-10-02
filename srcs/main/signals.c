/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:45:28 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/02 17:45:31 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

/**
* Write a newline
* Clear input buffer
* Mark cursor at the new line
* Redraw prompt
 */
static void	handle_sigint(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/**
* Set mask to 0, no need to mask incoming signals
* Tell the function to use the handler that is passed as @param
* Set the flags that are passed as @param
* "Install" the instructions
*/
void	set_sigaction(int sig, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = flags;
	sigaction(sig, &sa, NULL);
}

/**
* "Installs" instructions what to do when receiving SIGINT or SIGQUIT
*/
void	signals_interactive(void)
{
	set_sigaction(SIGINT, handle_sigint, SA_RESTART);
	set_sigaction(SIGQUIT, SIG_IGN, 0);
}

/**
* Restores default settings for when receiving SIGINT or SIGQUIT
*/
void	signals_default(void)
{
	set_sigaction(SIGINT, SIG_DFL, 0);
	set_sigaction(SIGQUIT, SIG_DFL, 0);
}

/** 
* Disables echo for control characters, such as ctrl + c
*/
void	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_lflag += -ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
