/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:25:32 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/09/11 16:29:49 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "arena.h"

typedef struct s_arena t_arena;

typedef enum	e_token_type
{
	WORD,			// For commands and arguments
	PIPE,			// For '|'
	REDIR_IN,		// For '<'
	REDIR_OUT,		// For '>'
	REDIR_APPEND,	// For '>>'
	REDIR_HEREDOC,	// For '<<'
	ENV_VAR,		// For environment variables '$'
	WORD_SINGLE_Q,	// For strings in single quotes
	WORD_DOUBLE_Q,	// For strings in double quotes
}	t_token_type;

typedef struct	s_token
{
	enum e_token_type	type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct	s_parser
{
	int		q_flag;
	char	**array;
}	t_parser;

struct	s_shell;
typedef struct	s_shell t_shell;

int		tokenize_input(char *line, t_shell *shell);
t_token	*new_token();
t_token	*add_token(t_shell *shell);
char	*gettokentype(t_token_type type);
int		quote_handler(char c, int *q_flag);
int		isdel(char c);
size_t	wdcount(const char *s, t_parser *p);

#endif
