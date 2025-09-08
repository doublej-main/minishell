/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:25:32 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/09/08 18:26:42 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

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
	enum e_token_type	type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct	s_arr
{
	size_t	qcount;
	size_t	w_countin_q;
	char	*line;
	char	**token_array;
}	t_arr;

struct	s_shell;
typedef struct	s_shell t_shell;

void	tokenize_input(char *line, t_shell *shell);
t_token	*new_token();
t_token	*add_token(t_shell *shell);
char	*gettokentype(t_token_type type);
char	**mini_split(char const *s, const char *del);
char	**loop_token_array(char **token, t_arr *elem, t_arena *arena, size_t wc);
char	**handle_quotes(char **token_split, t_arr *elem, t_arena *arena);
size_t	wordcount(char **array);
void	free_array(char **array);

#endif
