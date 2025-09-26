#include "minishell.h"

t_token	*add_token(t_shell *shell)
{
	t_token	*temp;

	temp = arena_alloc(shell->arena, sizeof(*temp));
	if (!temp)
		return (NULL);
	temp->value = NULL;
	temp->type = 0;
	temp->next = NULL;
	return (temp);
}

char	*gettokentype(int type)
{
	if (type == PIPE)
		return ("PIPE");
	else if (type == REDIR_IN)
		return ("REDIR IN");
	else if (type == REDIR_OUT)
		return ("REDIR OUT");
	else if (type == REDIR_APPEND)
		return ("REDIR APPEND");
	else if (type == REDIR_HEREDOC)
		return ("REDIR HEREDOC");
	else if (type == ENV_VAR)
		return ("ENV VAR");
	else
		return ("WORD");
}
