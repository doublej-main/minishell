#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

int	shell_init(t_shell *shell, char **environ)
{
	shell->env = env_from_environ(environ);
	if (!shell->env)
		return (perror("env fail"), FAILURE);
	if (arena_init(shell->arena, 10000) < 0)
		return (perror("arena fail"), FAILURE);
	disable_echoctl();
	shell->status = 0;
	return (SUCCESS);
}

/**
 * REPL -- READ - EVALUATE - PRINT - LOOP
 * Next we need Lexer: tokenize operators, handle quotes etc.
 * Then parser and error handling
 * $VAR and $?, expansion in general
 * Heredoc
 * Exec, child processes etc
 * Built-ins
 * Edge case testing, polishing, memory leaks, norm checks etc.
 */
void	shell_loop(t_shell *shell)
{
	char	*line;
	char	*prompt;
	t_token	*token;
	t_pl	*pipeblock;

	token = NULL;
	pipeblock = NULL;
	while (1)
	{
		signals_interactive();
		prompt = make_prompt(shell->arena);
		line = readline(prompt);
		if (!line)
			break ;
		shell->head = NULL;
		tokenize_input(line, shell, token);
		shell->pipe_head = NULL;
		pipeline_init(shell, &pipeblock);
		shell->status = execute_pipeline(shell->pipe_head, shell);
		consume_line(shell, line);
		if (line)
			free(line);
		arena_reset(shell->arena);
	}
}

// Need to implement detection of logical operators && and || 
// and report them as not supported
// Do we close all fds?
// Does it handle incorrect use of redirections? i.e. multiple
// Needs to handle environemtn variable expansion
// Heredoc
int	main(int argc, char **argv, char **environ)
{
	t_shell	shell;
	t_arena	arena;

	(void)argc;
	(void)argv;
	arena = (t_arena){0};
	shell.arena = &arena;
	print_banner();
	if (!shell_init(&shell, environ))
		return (EXIT_FAILURE);
	shell_loop(&shell);
	shell_destroy(&shell);
	return (EXIT_SUCCESS);
}
