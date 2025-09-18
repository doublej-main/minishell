#include "minishell.h"

void	shell_destroy(t_shell *shell)
{
	env_free(shell->env);
	// arena_destroy(&shell->arena);
}

void	consume_line(t_shell *shell, char *line)
{
	if (line && *line)
		add_history(line);
	if (line && *line)
		shell->status = 0;// set an env to shell status??
}
