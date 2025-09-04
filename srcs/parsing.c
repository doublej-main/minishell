
#include "minishell.h"

/*
DEFINING AST LOGIC

Step 1: Create AST nodes based on type
Step 2: Define the root node (pipe)
Step 3: Define priority for other nodes
Step 4: Create hierarchy in tree according to node priority
Step 5: Implement node hierarchy with a valid logic using linked lists

*/

t_ast_node	newnode(char *value, t_token type, t_arena *arena)
{
	t_ast_node *newnode = arena_alloc(arena, sizeof(t_ast_node));
	if (!newnode)
		return (NULL);
	newnode.value = arena_strdup(arena, value);
	if (!newnode.value)
		return (NULL);
	newnode.type = type;
	newnode.left = NULL;
	newnode.right = NULL;
	return (newnode);
}

/* token reading and implementing in linked lists

find root (if pipe, root = last pipe or redir(?))
root->left = pipe;
root->right = outfile;
root->left(pipe)->right = cmd;
root->left(pipe)->left = if pipe, pipe;
root->left(pipe)->left(pipe)->right = cmd;
root->left(pipe)->left(pipe)->left = if redir, redir;
root->left(pipe)->left(pipe)->left->right = infile;

							root(pipe or redir)
							/		\
						pipe		outfile
						/	\
					pipe	cmd
					/	\
				redir	cmd
					\
					infile

	< infile | cmd | cmd > outfile

	so if pipe, pipe.left = pipe, or redir_in, pipe.right = cmd or outfile
	if redir_in right = infile
	if redir_out, right = outfile
	maybe if redir, skip and left is infile, right is cmd(?)
*/
