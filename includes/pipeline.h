
#ifndef PIPELINE_H
# define PIPELINE_H

# include "arena.h"
# include "token.h"

# define PIPE 0
# define REDIR_IN 1
# define REDIR_OUT 2
# define REDIR_APPEND 3
# define REDIR_HEREDOC 4
# define ENV_VAR 5
# define WORD 6

typedef struct s_redir
{
	int type;     //<, >, >>, <<
	char *target; // file or heredoc delimiter
	int quoted;   // heredoc quoted?
	int	hd_tmp;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char **argv;  //["echo", "hello", NULL]
	t_redir *in;  // input redirs
	t_redir *out; // output redirs
	int				argc;
}					t_cmd;

typedef struct s_pl
{
	t_cmd			*cmd;
	struct s_pl *next; // next pipeblock
}					t_pl;

int					pipeline_init(t_shell *shell, t_pl **pipeblock);
int					def_pipeblock(t_shell *shell, t_pl *pipeblock, int ac);
char				*def_argv(t_arena *arena, char *value);
void				redirs_quoted(t_token *current, t_pl *pipeblock,
						char *next);
int					redir_helper(t_token *token, t_pl *pipeblock);
int					argc(t_token *token);
t_pl				*new_pipeblock(t_arena *arena);
t_pl				*add_pipeblock(t_shell *shell);
#endif
