/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:38:28 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/08/20 13:34:38 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile  sig_atomic_t	g_sig = 0;

static void	consume_line(t_shell *shell, char *line)
{
	if (line && *line)
		add_history(line);
	if (line && *line)
		shell->status = 0;
}

void	shell_init(t_shell *shell, char **environ)
{
	shell->env = env_from_environ(environ);
	disable_echoctl();
	shell->status  = 0;
}

void	shell_destroy(t_shell *shell)
{
	env_free(shell->env);
}

void	shell_loop(t_shell *shell)
{
	char *line;
	char	*prompt;

	while (1)
	{
		signals_interactive();
		prompt = make_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
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
	shell_init(&shell, environ);
	shell_loop(&shell);
	shell_destroy(&shell);
	return (EXIT_SUCCESS);
}
