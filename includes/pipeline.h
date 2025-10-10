/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:37:19 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/10 14:26:58 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int				type;
	char			*target;
	int				quoted;
	int				hd_tmp;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*in;
	t_redir			*out;
	int				ac;
}					t_cmd;

typedef struct s_pl
{
	t_cmd			*cmd;
	struct s_pl		*next;
}					t_pl;

int		pipeline_init(t_shell *shell, t_pl **pipeblock);
int		def_pipeblock(t_shell *shell, t_pl *pipeblock, t_token *curr, int i);
char	*def_argv(t_arena *arena, char *value);
int		argc(t_token *token);
int		init_segment(t_shell *shell, t_pl *pipeblock, t_token *tok);
t_pl	*new_pipeblock(t_arena *arena);
t_pl	*add_pipeblock(t_shell *shell);
int		count_quotes(char *next);

//refactoring

int		argv_builder(t_pl *pb, t_shell *shell, t_token *curr, int i);
int		pipeblock_helper(t_pl **pipeblock, t_shell *shell, t_token *cur, int i);

//redirs

t_redir	*add_redir(t_shell *shell);
void	ft_lstadd_back_redir(t_redir **lst, t_redir *new);
void	redirs_quoted(t_token *current, t_pl *pb, char *next, t_shell *shell);
#endif
