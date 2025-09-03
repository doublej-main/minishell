
#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

static void	consume_line(t_shell *shell, char *line)
{
	if (line && *line)
		add_history(line);
	if (line && *line)
		shell->status = 0;
}

int	shell_init(t_shell *shell, char **environ, t_arena *arena)
{
	shell->env = env_from_environ(environ);
	if (!shell->env)
		return (perror("env fail"), FAILURE);
	if (arena_init(arena, 10000) < 0)
		return (perror("arena fail"), FAILURE);
	disable_echoctl();
	shell->status = 0;
	return (SUCCESS);
}

void	shell_destroy(t_shell *shell, t_arena *arena)
{
	env_free(shell->env);
	arena_destroy(arena);
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

	while (1)
	{
		signals_interactive();
		prompt = make_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		tokenize_input(line, DEL);
		// TODO do what the line specifies
		consume_line(shell, line);
		free(line);
	}
}

int	main(int argc, char **argv, char **environ)
{
	t_shell	shell;
	t_arena	arena;

	(void)argc;
	(void)argv;
	print_banner();
	if (!shell_init(&shell, environ, &arena))
		return (EXIT_FAILURE);
	shell_loop(&shell);
	shell_destroy(&shell, &arena);
	return (EXIT_SUCCESS);
}
