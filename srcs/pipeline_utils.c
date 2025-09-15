
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
