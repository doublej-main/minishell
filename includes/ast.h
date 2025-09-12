
#ifndef AST_H
# define AST_H

#include "token.h"

enum e_token_type;
typedef enum e_token_type t_token_type;

typedef struct	s_ast
{
	struct t_ast_node	*root;
	char				**tokens;
	int					fd_in;
	int					fd_out;
	t_env				*env;
}	t_ast;

typedef struct	s_ast_node
{
	char				*value;
	t_token_type		type;	//command, pipeline, redirection, file
	char				*args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

struct s_node;
typedef struct s_node t_node;

t_ast_node	*newnode(char *value, t_token *token, t_arena *arena);

#endif
