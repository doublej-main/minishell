
#include "minishell.h"

char	*make_prompt(t_arena *arena)
{
	char	*cwd;
	char	*tmp;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = arena_strdup("?", arena);
	if (!cwd)
		return (NULL);
	tmp = arena_strjoin("minishell ", cwd, arena);
	free(cwd);
	if (!tmp)
		return (NULL);
	prompt = arena_strjoin(tmp, " $> ", arena);
	free(tmp);
	return (prompt);
}
