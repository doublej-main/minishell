#include "minishell.h"

int	argv_builder(t_pl *pb, t_shell *shell, t_token *curr, int i)
{
	if (i < pb->cmd->ac)
	{
		pb->cmd->argv[i] = def_argv(shell->arena, curr->value);
		i++;
	}
	return (i);
}
