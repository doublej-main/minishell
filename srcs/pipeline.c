
#include "minishell.h"

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
	else
	{
		pipeblock->cmd->out->target = next;//outs
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

int	def_pipeblock(t_arena *arena, t_token *token, t_pl *pipeblock, int ac)
{
	t_token	*curr;
	int		i;

	curr = token;
	i = 0;
	while (curr)
	{
		if (curr->type == PIPE)
		{
			pipeblock->next = add_pipeblock(arena);
			pipeblock = pipeblock->next;
		}
		else if (curr->type == REDIR_IN || curr->type == REDIR_OUT
            || curr->type == REDIR_APPEND || curr->type == REDIR_HEREDOC)
		{
			redir_helper(curr, pipeblock);
			token = token->next;
			if (token->type != WORD)
				return(FAILURE);
			else
				redirs_quoted(curr, pipeblock, token->value);
		}
		else if (curr->type == WORD)
		{
			if (i < ac)
			{
				pipeblock->cmd->argv[i] = def_argv(arena, curr->value);
				if (!pipeblock->cmd->argv[i])
					return (FAILURE);
			}
			else
				pipeblock->cmd->argv[i] = 0;
			i++;
		}
		curr = curr->next;
	}
	return (SUCCESS);
}

int	pipeline_init(t_arena *arena, t_token *token, t_pl *pipeblock)
{
	int		ac;

	printf("here0\n");
	ac = argc(token);
	printf("here1\n");
	pipeblock = arena_alloc(arena, sizeof(t_pl));
	if (!pipeblock)
		return (perror("pipeblock"), FAILURE);
	pipeblock->cmd = arena_alloc(arena, sizeof(t_cmd));
	printf("here2\n");                       
	if (!pipeblock->cmd)
		return (perror("cmds"), FAILURE);
	pipeblock->cmd->in = arena_alloc(arena, sizeof(t_redir));
	printf("here3\n");                           
	if (!pipeblock->cmd->in)                                                                  
		return (perror("in"), FAILURE);
	pipeblock->cmd->out = arena_alloc(arena, sizeof(t_redir));
	printf("here4\n");                                 
	if (!pipeblock->cmd->out)                                                                  
		return (perror("out"), FAILURE);
	pipeblock->cmd->argv = arena_alloc(arena, (ac + 1) * sizeof(char *));
	printf("here5\n"); 
	if (!pipeblock->cmd->argv)
		return (perror("args"), FAILURE);
	if (!def_pipeblock(arena, token, pipeblock, ac))
		return (perror("def_pipeblock"), FAILURE);
	return (SUCCESS);
}
