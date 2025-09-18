/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:25:32 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/09/18 12:21:32 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "arena.h"
# include "stddef.h"

typedef struct s_arena	t_arena;

//typedef enum e_token_type
//{
//	WORD,          // For commands and arguments
//	PIPE,          // For '|'
//	REDIR_IN,      // For '<'
//	REDIR_OUT,     // For '>'
//	REDIR_APPEND,  // For '>>'
//	REDIR_HEREDOC, // For '<<'
//	ENV_VAR,       // For environment variables '$'
//}						t_token_type;

typedef struct s_token
{
	int					type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_parser
{
	int					q_flag;
	size_t				del_flag;
	int					i;
	int					j;
	int					start;
	char				**array;
}						t_parser;

struct s_shell;
typedef struct s_shell	t_shell;

int						tokenize_input(char *line, t_shell *shell,
							t_token *token);
t_token					*new_token(void);
t_token					*add_token(t_shell *shell);
char					*gettokentype(int type);
int						quote_handler(char c, int *q_flag);
int						isdel(char c);
void					parser_helper(t_parser *p, int type);
size_t					wdcount(const char *s, t_parser *p);

#endif
