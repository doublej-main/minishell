#ifndef MINISHELL_H
# define MINISHELL_H

/*
** Includes
*/
# include "arena.h"
# include "builtins.h"
# include "env.h"
# include "exec.h"
# include "heredoc.h"
# include "libft.h"
# include "pipeline.h"
# include "prompt.h"
# include "signals.h"
# include "token.h"
# include "utils.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

/*
** Macros
*/
# define SUCCESS 1
# define FAILURE 0

/*
** Variables and structs
*/
extern volatile sig_atomic_t	g_sig;

typedef struct s_shell
{
	t_env						*env;
	int							status;
	t_arena						*arena;
	t_token						*head;
	t_pl						*pipe_head;
	int							fd_in;
	int							single;
	int							doppel;
}								t_shell;

/*
** Prototypes
*/
int								shell_init(t_shell *shell, char **environ);
void							shell_loop(t_shell *shell, t_token *token,
									t_pl *pipeblock);
void							shell_destroy(t_shell *shell);
void							consume_line(t_shell *shell, char *line);
int								syntax_error_checker(t_shell *shell,
									char *line);
void							init_token_and_pipeline(t_shell *shell,
									t_token *token, t_pl *pipeblock,
									char *line);

#endif
