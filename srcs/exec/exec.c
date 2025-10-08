/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:42:29 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/08 17:29:33 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	even_earlier_exit(t_shell *shell, int status)
{
	shell_destroy(shell);
	_exit(status);
}

static void	early_exit(t_shell *shell)
{
	ft_putstr_fd("command not found\n", 2);
	shell_destroy(shell);
	_exit(127);
}

static void	cleanup_child(t_shell *shell, char **envv, char *prog)
{
	if (envv)
		ft_free(envv);
	if (prog)
		free(prog);
	shell_destroy(shell);
	if (errno == EACCES)
		_exit(126);
	else
		_exit(127);
}

void	exec_external_or_builtin(const t_cmd *cmd, t_shell *shell)
{
	char	**envv;
	char	*prog;
	int		status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		even_earlier_exit(shell, 0);
	if (is_any_builtin(cmd->argv[0]))
	{
		status = run_any_builtin(cmd->argv[0], cmd->argv, shell);
		shell_destroy(shell);
		_exit(status);
	}
	prog = NULL;
	if (ft_strchr(cmd->argv[0], '/'))
		prog = ft_strdup(cmd->argv[0]);
	else
		prog = path_search(shell, cmd->argv[0], shell->env);
	if (!prog)
		early_exit(shell);
	envv = env_to_chars(shell->env);
	if (!envv)
		even_earlier_exit(shell, 1);
	close(shell->fd_in);
	execve(prog, cmd->argv, envv);
	cleanup_child(shell, envv, prog);
}

int	execute_pipeline(t_pl *pl, t_shell *shell)
{
	int	status;

	if (heredoc_prepare_all(shell) < 0)
	{
		dup2(shell->fd_in, STDIN_FILENO);
		return (130);
	}
	if (!shell->pipe_head->next)
		status = run_single(shell->pipe_head->cmd, shell);
	else
		status = run_pipeline(shell->pipe_head, shell);
	heredoc_cleanup_all(pl);
	return (status);
}
