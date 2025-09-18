#include "minishell.h"

static int	init_segment(t_shell *shell, t_pl *pipeblock, int ac)
{
	pipeblock->cmd = arena_alloc(shell->arena, sizeof(t_cmd));
	if (!pipeblock->cmd)
		return (FAILURE);
	pipeblock->cmd->in = (t_redir *)&(t_redir){0};
	pipeblock->cmd->out = (t_redir *)&(t_redir){0};
	pipeblock->cmd->argv = arena_alloc(shell->arena, sizeof(char *) * (ac + 1));
	if (!pipeblock->cmd->argv)
		return (FAILURE);
	pipeblock->cmd->argv[0] = NULL;
	return (SUCCESS);
}

void	redirs_quoted(t_token *current, t_pl *pipeblock, char *next)
{
	if (current->type == REDIR_IN || current->type == REDIR_APPEND)//ins
	{
		pipeblock->cmd->in->target = next;
		if (next[0] == '\''
			&& next[ft_strlen(next) - 1] == '\'')
			pipeblock->cmd->in->quoted = 1;
		else if (next[0] == '\"'
			&& next[ft_strlen(next) - 1] == '\"')
			pipeblock->cmd->in->quoted = 2;
		else
			pipeblock->cmd->in->quoted = 0;
	}
	if (current->type == REDIR_OUT || current->type == REDIR_HEREDOC)//outs
	{
		pipeblock->cmd->out->target = next;
		if (next[0] == '\''                                               
            && next[ft_strlen(next) - 1] == '\'')                              
            pipeblock->cmd->out->quoted = 1;                                      
        else if (next[0] == '\"'                                                
            && next[ft_strlen(next) - 1] == '\"')                              
            pipeblock->cmd->out->quoted = 2;                                      
        else                                                                     
            pipeblock->cmd->out->quoted = 0;
	}
}

char	*def_argv(t_arena *arena, char *value)
{
	char	*temp;

	temp = arena_strdup(arena, value);
	if (!temp)
		return (NULL);
	return (temp);
}

int	def_pipeblock(t_shell *shell, t_pl *pipeblock, int ac)
{
	t_token	*curr;
	int		i;

	curr = shell->head;
	i = 0;
	while (curr)
	{
		if (curr->type == PIPE)
		{
			pipeblock->cmd->argv[i] = NULL;
			pipeblock = add_pipeblock(shell);
			ft_lstadd_back_pipe(&shell->pipe_head, pipeblock);
			ac = argc(curr->next);
			if (!init_segment(shell, pipeblock, ac))
				return (FAILURE);
			i = 0;
		}
		else if (curr->type == REDIR_IN || curr->type == REDIR_OUT
            || curr->type == REDIR_APPEND || curr->type == REDIR_HEREDOC)
		{
			if (!curr->next || curr->next->type != WORD)
				return (FAILURE);
			redir_helper(curr, pipeblock);
			redirs_quoted(curr, pipeblock, curr->next->value);
			curr = curr->next;
			if (curr->next)
				curr = curr->next;
			break;
		}
		else if (curr->type == WORD)
		{
			if (i < ac)
			{
				pipeblock->cmd->argv[i] = def_argv(shell->arena, curr->value);
				i++;
			}
		}
		curr = curr->next;
	}
	pipeblock->cmd->argv[i] = NULL;
	return (SUCCESS);
}

int	pipeline_init(t_shell *shell, t_pl **pipeblock)
{
	int		ac;

	ac = argc(shell->head);
	(*pipeblock) = arena_alloc(shell->arena, sizeof(t_pl));
	if (!*pipeblock)
		return (perror("pipeblock"), FAILURE);
	(*pipeblock)->cmd = arena_alloc(shell->arena, sizeof(t_cmd));            
	if (!(*pipeblock)->cmd)
		return (perror("cmds"), FAILURE);
	(*pipeblock)->cmd->in = arena_alloc(shell->arena, sizeof(t_redir));                    
	if (!(*pipeblock)->cmd->in)                                                                  
		return (perror("in"), FAILURE);
	(*pipeblock)->cmd->out = arena_alloc(shell->arena, sizeof(t_redir));                       
	if (!(*pipeblock)->cmd->out)                                                                  
		return (perror("out"), FAILURE);
	(*pipeblock)->cmd->argv = arena_alloc(shell->arena, (ac + 1) * sizeof(char *));
	if (!(*pipeblock)->cmd->argv)
		return (perror("args"), FAILURE);
	ft_lstadd_back_pipe(&shell->pipe_head, *pipeblock);
	if (!def_pipeblock(shell, *pipeblock, ac))
		return (perror("def_pipeblock"), FAILURE);
	return (SUCCESS);
}
