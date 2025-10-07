#include "minishell.h"

void	shell_destroy(t_shell *shell)
{
	env_free(shell->env);
	arena_destroy(shell->arena);
	close(shell->fd_in);
}

void	consume_line(t_shell *shell, char *line)
{
	(void)shell;
	if (line && *line)
		add_history(line);
}
