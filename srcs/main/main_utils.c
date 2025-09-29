#include "minishell.h"

void	shell_destroy(t_shell *shell)
{
	env_free(shell->env);
	arena_destroy(shell->arena);
}

void	consume_line(t_shell *shell, char *line)
{
	(void)shell;
	if (line && *line)
		add_history(line);
}
