#ifndef EXEC_H
# define EXEC_H

typedef struct s_fd
{
	int	count;
	int	fd[2];
	int	prev_in;
	int	out_fd;
}		t_fd;

int		execute_pipeline(t_pipeline *pl, t_shell *shell);
void	exec_external_or_builtin(const t_cmd *cmd, t_shell *shell);
int		run_pipeline(t_pipeline *pl, t_shell *shell);
char	**env_to_chars(t_env *env);
char	*env_join(const char *s1, const char *s2, const char *s3);
char	*path_search(char *name, t_env *env);

#endif