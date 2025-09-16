
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
	t_token	*current;

	count = 0;
	current = token;
	while (current)
	{
		if (current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == REDIR_APPEND || current->type == REDIR_HEREDOC)
		{
			token = token->next;
			current = token->next;
		}
		if (current->type == WORD)
			count++;
		else if (current->type == PIPE)
			return (count);
		current = current->next;
		token = current;
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
