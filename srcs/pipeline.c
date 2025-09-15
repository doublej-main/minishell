
#include "minishell.h"

int	def_redirs(t_arena *arena, t_token *token, t_pl *pipeblock, int type)
{
	if (type == 0)
		return (redir_helper(token, pipeblock));
	else if (type == 1 || type == 3) // ins
	{
		pipeblock->cmd->in->target = token->value;
		return (5);
	}
	else
	{
		pipeblock->cmd->out->target = token->value;
		return (5);
	}
	//IS IT QUOTED?
}

int	def_cmds(t_arena *arena, t_token *token, t_cmd *cmds)
{

}

int	def_pipeblock(t_arena *arena, t_token *token, t_pl *pipeblock)
{

}

int	create_pipeline(t_arena *arena, t_token *token, t_pl *pipeblock, int *type)
{
		if (token->type != PIPE)
		{
			if (token->type == WORD)
			{
			
			}
			if (type == 0 || token->type == REDIR_IN || token->type == REDIR_OUT          
                || token->type == REDIR_APPEND || token->type == REDIR_HEREDOC)
				return (def_redirs(arena, token, pipeblock, type));
			else if (type > 0 && type < 5)
				return (def_redirs(arena, token, pipeblock, type));
		}
}

int	pipeline_init(t_arena *arena, t_token *token)
{
	t_pl		*pipeblock;
	t_redir		*redir;
	t_cmd		*cmds;
	int			*type;

	type = 0;
	redirs = arena_calloc(arena, sizeof(t_redir));
	if (!redirs)
		return (perror("redirs"), FAILURE);
	cmds = arena_calloc(arena, sizeof(t_cmd));
	if (!cmds)
		return (perror("cmds"), FAILURE);
	pipeblock = arena_calloc(arena, sizeof(t_redir));
	if (!pipeblock)
		return (perror("pipeblock"), FAILURE);
	while (token->next)
	{
		type = create_pipeline(arena, token, pipeblock, type);	//redir types 1,2,3,4 redir->target type 5
		if (!create_pipeline(arena, token, pipeblock))
			return (perror("pipeline"), FAILURE);
	}
	return (SUCCESS);
}
