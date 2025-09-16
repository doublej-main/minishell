
#include "minishell.h"

int	redir_helper(t_token *token, t_pl *pipeblock)
{
	if (token->type == REDIR_IN)
	{
		pipeblock->cmd->in->type = REDIR_IN;
		return (1);
	}
	else if (token->type == REDIR_OUT)
	{
		pipeblock->cmd->out->type = REDIR_OUT;
		return (1);
	}
	else if (token->type == REDIR_APPEND)
	{
		pipeblock->cmd->in->type = REDIR_APPEND;
		return (1);
	}
	else
	{
		pipeblock->cmd->out->type = REDIR_HEREDOC;
		return (1);
	}
}

int	argc(t_token *token)
{
	int		count;

	printf("%s\n", token->value);
	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == REDIR_APPEND || token->type == REDIR_HEREDOC)
		{
			token = token->next;
			if (token)
				token = token->next;
		}
		if (token->type == WORD)
			count++;
		if (token)
			token = token->next;
	}
	return (count);
}

t_pl *new_pipeblock(t_arena *arena)
{
    t_pl *new;

    new = arena_alloc(arena, sizeof(t_pl));
    if (!new)
        return (NULL);
    new->cmd = arena_alloc(arena, sizeof(t_cmd));
    if (!new->cmd)
        return (NULL);
    new->next = NULL;
    return (new);
}

t_pl *add_pipeblock(t_arena *arena)
{
    t_pl *temp;

    temp = new_pipeblock(arena);
    temp->next = NULL;
    return (temp);
}
