/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:38:09 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/07 14:40:17 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "arena.h"
# include "stddef.h"

typedef struct s_arena	t_arena;

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

struct					s_shell;
typedef struct s_shell	t_shell;

int		tokenize_input(char *line, t_shell *shell, t_token *token, size_t i);
t_token	*new_token(void);
t_token	*add_token(t_shell *shell);
char	*gettokentype(int type);
int		quote_handler(t_shell *shell, char c, int *q_flag);
int		isdel(char c);
int		get_type(char *token);
int		tokenization_helper(t_shell *shell, t_parser *p, t_token *token, int i);
void	parser_helper(t_parser *p, int type);
size_t	wdcount(t_shell *shell, const char *s, t_parser *p);
int		check_for_env(t_shell *shell, char **str);
int		replace_with_val(t_shell *shell, char **str);
int		syntax_compare(char *token, char *next);
int		syntax_helper(char *token);

#endif
