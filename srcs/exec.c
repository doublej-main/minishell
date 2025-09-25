#include "minishell.h"

void	exec_external_or_builtin(const t_cmd *cmd, t_shell *shell)
{
	char	**envv;
	char	*prog;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		_exit(0);
	if (is_any_builtin(cmd->argv[0]))
		_exit(run_any_builtin(cmd->argv[0], cmd->argv, shell));
	prog = NULL;
	if (ft_strchr(cmd->argv[0], '/'))
		prog = ft_strdup(cmd->argv[0]);
	else
		prog = path_search(cmd->argv[0], shell->env);
	if (!prog)
		_exit(127);
	envv = env_to_chars(shell->env);
	if (!envv)
		_exit(1);
	execve(prog, cmd->argv, envv);
	ft_free(envv);
	free(prog);
	if (errno == EACCES)
		_exit(126);
	else
		_exit(127);
}

int	execute_pipeline(t_pl *pl, t_shell *shell)
{
	int	status;

	if (heredoc_prepare_all(shell) < 0)
		return (130);
	if (!shell->pipe_head->next)
		status = run_single(shell->pipe_head->cmd, shell);
	else
		status = run_pipeline(shell->pipe_head, shell);
	heredoc_cleanup_all(pl);
	return (status);
}
