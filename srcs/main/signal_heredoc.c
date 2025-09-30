#include "minishell.h"

void	signals_init(void)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
	signals_interactive();
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
