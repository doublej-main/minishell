
#ifndef PIPELINE_H
# define PIPELINE_H

#include "token.h"
#include "arena.h"

typedef struct	s_redir
{
	int				type;		//<, >, >>, <<
	char			*target;	//file or heredoc delimiter
	int				quoted;		//heredoc quoted?
	struct s_redir	*next;
}	t_redir;

typedef struct	s_cmd
{
	char			**argv;	//["echo", "hello", NULL]
	t_redir			*in;	//input redirs
	t_redir			*out;	//output redirs
	int				argc;
}	t_cmd;

typedef struct	s_pl
{
	t_cmd				*cmd;
	struct s_pipeline	*next; // next pipeblock
}	t_pl;

int	pipeline_init(t_arena *arena, t_token *token);
int	create_pipeline(t_arena *arena, t_token *token, t_pl *pipeblock
int	def_pipeblock(t_arena *arena, t_token *token, t_pl *pipeblock);
int	def_cmds(t_arena *arena, t_token *token, t_cmd *cmds);
int	def_redirs(t_arena *arena, t_token *token, t_pl *pipeblock, int type);
int	redir_helper(t_token *token, t_pl *pipeblock);
int	create_av(t_arena *arena, t_pl *pipeblock, char *stash, t_token *token);

#endif
