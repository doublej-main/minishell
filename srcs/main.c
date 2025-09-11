/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:38:28 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/09/11 12:50:58 by vahdekiv         ###   ########.fr       */
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
	shell->env = env_from_environ(environ);
	if (!shell->env)
		return (perror("env fail"), FAILURE);
	if (arena_init(shell->arena, 10000) < 0)
		return (perror("arena fail"), FAILURE);
	disable_echoctl();
	shell->status = 0;
	return (SUCCESS);
}

void	shell_destroy(t_shell *shell)
{
	env_free(shell->env);
	// arena_destroy(&shell->arena);
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
		prompt = make_prompt(shell->arena);
		line = readline(prompt);
		if (!line)
			break ;
		// TODO do what the line specifies
		consume_line(shell, line);
		if (!tokenize_input(line, shell))
		{
			free(line);
			return ;
		}
		free(line);
		arena_reset(shell->arena);
	}
}

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
