
#ifndef PARSING_H
# define PARSNG_H

#include "minishell.h"

typedef struct	s_ast_node
{
	t_node type			type; //command, pipeline, redirection, file
	char				*args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

#endif
