/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:44:34 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/02 17:44:36 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_init(t_shell *shell, char **environ)
{
	shell->fd_in = dup(STDIN_FILENO);
	if (shell->fd_in < 0)
		return (FAILURE);
	if (arena_init(shell->arena, 10000) < 0)
		return (ft_putstr_fd("arena fail", 2), FAILURE);
	shell->env = env_from_environ(shell, environ);
	if (!shell->env)
		return (perror("env fail"), FAILURE);
	disable_echoctl();
	shell->status = 0;
	return (SUCCESS);
}

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
		consume_line(shell, line);
		if (!syntax_error_checker(shell, line))
			continue ;
		shell->head = NULL;
		tokenize_input(line, shell, token);
		shell->pipe_head = NULL;
		pipeline_init(shell, &pipeblock);
		shell->status = execute_pipeline(shell->pipe_head, shell);
		free(line);
		arena_reset(shell->arena);
	}
}

int	main(int argc, char **argv, char **environ)
{
	t_shell		shell;
	t_arena		arena;
	extern int	rl_catch_signals;

	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	arena = (t_arena){0};
	shell.arena = &arena;
	print_banner();
	if (!shell_init(&shell, environ))
		return (EXIT_FAILURE);
	shell_loop(&shell);
	shell_destroy(&shell);
	return (EXIT_SUCCESS);
}
