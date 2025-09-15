
#include "minishell.h"

int	def_redirs(t_arena *arena, t_token *token, t_pl *pipeblock, int type)
{
	if (type == 0)
		return (redir_helper(token, pipeblock));
	else if (type == 1 || type == 3) // ins
	{
		pipeblock->cmd->in->target = token->value;
		if (token->value[0] == '\''
			&& token->value[ft_strlen(token->value) - 1] == '\'')
			pipeblock->cmd->in->quoted = 1;
		else if (token->value[0] == '\"'
			&& token->value[ft_strlen(token->value) - 1] == '\"')
			pipeblock->cmd->in->quoted = 2;
		else
			pipeblock->cmd->in->quoted = 0;
		return (5);
	}
	else
		pipeblock->cmd->out->target = token->value;
	return (5);
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
		if (token->type == WORD && (type == 0 || type > 4 || type == 6))
		{
			return (6);
		}
		else if (type == 0 || token->type == REDIR_IN || token->type == REDIR_OUT          
			|| token->type == REDIR_APPEND || token->type == REDIR_HEREDOC)
			return (def_redirs(arena, token, pipeblock, type));
		else if (type > 0 && type < 5)
			return (def_redirs(arena, token, pipeblock, type));
	}
	else
		return (7);
}

int	pipeline_init(t_arena *arena, t_token *token)
{
	t_pl		*pipeblock;
	t_redir		*redir;
	t_cmd		*cmds;
	int			*type;
	static char	*stash;

	type = 0;
	cmd->argc = 0;
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
		*type = create_pipeline(arena, token, pipeblock, type);	//redir types 1,2,3,4 redir->target type 5
		if (type == 6)
		{
			cmd->argc++;
			stash = token->value;
		}
		else if (type != 6 && arvc != 0)
		{
			pipeblock->cmd->argv = arena_alloc(arena, cmd->argc + 1 * sizeof(char *);
			if (!pipeblock->cmd->argv)
				return (free(stash), FAILURE);
			create_av(arena, pipeblock, stash, token);
		}
		else if (!create_pipeline(arena, token, pipeblock))
			return (perror("pipeline"), FAILURE);
	}
	return (SUCCESS);
}
