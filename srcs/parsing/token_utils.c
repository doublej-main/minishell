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

int	tokenization_helper(t_shell *shell, t_parser *p, t_token *token, int i)
{
	if (!check_for_env(shell, &p->array[i]))
		return (SUCCESS);
	token = add_token(shell);
	token->value = arena_strdup(shell->arena, p->array[i]);
	if (!token->value)
		return (perror("token"), FAILURE);
	token->type = get_type(token->value);
	ft_lstadd_back(&shell->head, token);
	return (SUCCESS);
}
