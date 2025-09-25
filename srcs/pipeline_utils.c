#include "minishell.h"

int	redir_helper(t_token *token, t_pl *pipeblock)
{
	if (token->type == REDIR_IN)
		pipeblock->cmd->in->type = REDIR_IN;
	if (token->type == REDIR_OUT)
		pipeblock->cmd->out->type = REDIR_OUT;
	if (token->type == REDIR_APPEND)
		pipeblock->cmd->out->type = REDIR_APPEND;
	if (token->type == REDIR_HEREDOC)
		pipeblock->cmd->in->type = REDIR_HEREDOC;
	return (1);
}

int	argc(t_token *token)
{
	int		count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == REDIR_APPEND || token->type == REDIR_HEREDOC)
		{
			token = token->next;
			if (token)
				token = token->next;
			continue ;
		}
		if (token->type == WORD)
			count++;
		token = token->next;
	}
	return (count);
}

t_pl	*add_pipeblock(t_shell *shell)
{
	t_pl	*temp;

	temp = arena_alloc(shell->arena, sizeof(*temp));
	if (!temp)
		return (NULL);
	temp->cmd = NULL;
	temp->next = NULL;
	return (temp);
}
