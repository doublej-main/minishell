/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:38:28 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/08/27 14:27:21 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

static void	consume_line(t_shell *shell, char *line)
{
	if (line && *line)
		add_history(line);
	if (line && *line)
		shell->status = 0;
}

int	shell_init(t_shell *shell, char **environ)
{
	t_arena	arena;

	arena = (t_arena){0};
	shell->env = env_from_environ(environ);
	if (!shell->env)
		return (FAILURE);
	if (arena_init(&arena, 10000) < 0)
		return (perror("arena fail"), FAILURE);
	disable_echoctl();
	shell->status = 0;
}

void	shell_destroy(t_shell *shell)
{
	env_free(shell->env);
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
		// TODO do what the line specifies
		consume_line(shell, line);
		free(line);
	}
}

int	main(int argc, char **argv, char **environ)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	print_banner();
	if (!shell_init(&shell, environ))
		return (EXIT_FAILURE);
	shell_loop(&shell);
	shell_destroy(&shell);
	return (EXIT_SUCCESS);
}
