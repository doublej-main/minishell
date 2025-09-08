
#ifndef PARSING_H
# define PARSNG_H

#include "minishell.h"

typedef struct	s_ast
{
	t_ast_node	*root;
	char		**tokens;
	int			fd_in;
	int			fd_out;
	t_env		*env;
}	t_ast;

typedef struct	s_ast_node
{
	char				*value;
	t_node type			type;	//command, pipeline, redirection, file
	char				*args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

t_ast_node	*newnode(char *value, t_token type, t_arena *arena);

#endif
