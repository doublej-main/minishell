#include "minishell.h"

void    shell_destroy(t_shell *shell)                                            
{                                                                                
	env_free(shell->env);
	token_free(shell->head);
	pipeline_free(shell->pipe_head);
	arena_destroy(shell->arena);
}

void    env_free(t_env *env)
{
	t_env   *next;

	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->val);
		free(env);
		env = next;
	}
}

void	token_free(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		free(head->value);
		free(head);
		head = next;
	}
}

void	pipeline_free(t_pl *pipe_head)
{

}
