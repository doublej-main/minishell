
#include "minishell.h"

int	redir_helper(t_token *token, t_pl *pipeblock)
{
	if (token->type == REDIR_IN)
	{
		pipeblock->cmd->in->type = 1;
		return (1);
	}
	else if (token->type == REDIR_OUT)
	{
		pipeblock->cmd->out->type = 2;
		return (2);
	}
	else if (token->type == REDIR_APPEND)
	{
		pipeblock->cmd->in->type = 3;
		return (3);
	}
	else if (token->type == REDIR_HEREDOC)
	{
		pipeblock->cmd->out->type = 4;
		return (4);
	}
}

int	create_av(t_arena *arena, t_pl *pipeblock, char *stash, t_token *token)
{
	int	i;

	i = 0;
	while (token->next)
	{
		if (ft_strncmp(stash, token->value, ft_strlen(token->value)))
		{
			pipeblock->cmd->argv[i] = arena_alloc(arena, ft_strlen(token->value)
			* sizeof(char));
			if(!pipeblock->cmd->argv[i])
				return (perror("argv"), FAILURE);
			pipeblock->cmd->argv[i] = token->value;
			i++;
		}
	}
	pipeblock->cmd->argv[i] = 0;
	return (SUCCESS);
}
