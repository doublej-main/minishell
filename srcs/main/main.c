/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:44:34 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/06 14:52:56 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_init(t_shell *shell, char **environ)
{
	shell->fd_in = dup(STDIN_FILENO);
	if (shell->fd_in < 0)
		return (FAILURE);
	if (arena_init(shell->arena, 10000) < 0)
		return (ft_putstr_fd("error: arena fail\n", 2), FAILURE);
	shell->env = env_from_environ(shell, environ);
	if (!shell->env)
		return (ft_putstr_fd("error: env fail\n", 2), FAILURE);
	disable_echoctl();
	shell->head = NULL;
	shell->pipe_head = NULL;
	shell->status = 0;
	return (SUCCESS);
}

void	shell_loop(t_shell *shell, t_token *token, t_pl *pipeblock)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		signals_interactive();
		prompt = make_prompt(shell->arena);
		line = readline(prompt);
		if (g_sig == SIGINT)
			shell->status = 130;
		if (!line)
			break ;
		consume_line(shell, line);
		if (!syntax_error_checker(shell, line))
			continue ;
		tokenize_input(line, shell, token);
		free(line);
		if (!pipeline_init(shell, &pipeblock))
			continue ;
		shell->status = execute_pipeline(shell->pipe_head, shell);
		arena_reset(shell, shell->arena);
	}
}

int	main(int argc, char **argv, char **environ)
{
	t_shell		shell;
	t_arena		arena;
	t_token		*token;
	t_pl		*pipeblock;
	extern int	rl_catch_signals;

	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	token = NULL;
	pipeblock = NULL;
	arena = (t_arena){0};
	shell.arena = &arena;
	print_banner();
	if (!shell_init(&shell, environ))
		return (EXIT_FAILURE);
	shell_loop(&shell, token, pipeblock);
	shell_destroy(&shell);
	return (EXIT_SUCCESS);
}
