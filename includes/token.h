/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:25:32 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/08/29 15:42:10 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

# define DEL "\f\n\r\t\v"

typedef enum	e_token_type
{
	TOKEN_WORD,				// For commands and arguments
	TOKEN_PIPE,				// For '|'
	TOKEN_REDIR_IN,			// For '<'
	TOKEN_REDIR_OUT,		// For '>'
	TOKEN_REDIR_APPEND,		// For '>>'
	TOKEN_REDIR_HEREDOC,	// For '<<'
	TOKEN_ENV_VAR,			// For environment variables '$'
}	t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct	s_arr
{
	size_t	qcount;
	size_t	w_countin_q;
	char	*line;
}	t_arr;

void	tokenize_input(char *line, DEL, t_shell *shell);
t_token	*new_token();
t_token	*add_token(t_shell *shell);
char	*gettokentype(t_token_type type); // for testing

#endif
