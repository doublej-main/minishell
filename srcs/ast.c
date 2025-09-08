
#include "minishell.h"

/*
DEFINING AST LOGIC

Step 1: Create AST nodes based on type
Step 2: Define the root node (pipe)
Step 3: Define priority for other nodes
Step 4: Create hierarchy in tree according to node priority
Step 5: Implement node hierarchy with a valid logic using linked lists

*/

t_ast_node	*newnode(char *value, t_token *token, t_arena *arena)
{
	t_ast_node *newnode;
	newnode = arena_alloc(arena, sizeof(t_ast_node));
	if (!newnode)
		return (NULL);
	newnode->value = arena_strdup(arena, value);
	if (!newnode->value)
		return (NULL);
	newnode->type = token->type;
	newnode->left = NULL;
	newnode->right = NULL;
	return (newnode);
}
/*
void	ast_init(t_arena *arena, t_token *token)
{
	t_ast	*ast;
	t_token	*tmp;
	size_t	i;

	i = 0;
	ast = arena_alloc(arena, sizeof(t_ast));
	tmp = token;
	while(tmp)
	{
		token = token->next;
		i++;
	}
	ast->tokens = arena_alloc(arena, (i + 1) * (sizeof(char *)));
	i = 0;
	while(tmp)
	{
		ast->tokens[i] = token->value;
		token = token->next;
		i++;
	}
	ast->tokens[i] = '\0';
	ast_parser(arena, ast, token);
}

void	ast_parser(t_arena *arena, t_ast *ast, t_token *token)
{
	
}
*/
/*

token reading and implementing in linked lists

find root (last pipe3)
root->left = pipe2;
root->right = redir_out3;
root->left(pipe2)->right = redir_out1;
root->left(pipe2)->right(redr_out1)->left = cmd3;
root->left(pipe2)->left = pipe1;
root->left(pipe2)->left(pipe1)->right = cmd2;
root->left(pipe2)->left(pipe1)->left = redir_out0;
root->left(pipe2)->left(pipe1)->left(redir_out0)->left = redir_in2;
root->left(pipe2)->left(pipe1)->left(redir_out0)->left(redir_in2)->left = red_in1;
root->left(pipe2)->left(pipe1)->left(redir_out0)->left(redir_in2)->left(red_in1)->left = cmd param1

				PIPE BLOCK 1					PB2			PB3				PIPE BLOCK 4

	cmd param1 < infile1 < infile2 > outfile0 | cmd2 | cmd3 > outfile1 | cmd4 > outfile2 > outfile3


										root(pipe3)
								/						\
							pipe2						red(> outfile3)
						/			\						/
					pipe1			red(> outfile1)		red(> outfile2)
					/	\			/						/
		red(> outfile0)	cmd2	cmd3					cmd4
				/											
		red(< infile2)
			/
		red(< infile1)
		/
	cmd param1


	- Root is always last pipe
	- Branching nodes are always pipes
	- Each pipe-block should contain at most one command. Other tokens will be treated as arguments, and their order may not be correct
	- Each redirection token should be followed by a file argument
	- Each pipe sign must be accompanied by a left child and a right child
*/
