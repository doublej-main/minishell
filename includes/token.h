/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:25:32 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/09/04 11:21:51 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

# define DEL "\f\n\r\t\v"

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
char	*gettokentype(t_token_type type);
char	**loop_token_array(char **token, t_arr *elem, t_arena arena, size_t wc);
char	**handle_quotes(char **token_arr, t_arena *arena);
size_t	wordcount(char **array);
void	free_array(char **array);

#endif
