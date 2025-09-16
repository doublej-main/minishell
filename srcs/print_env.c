#include "minishell.h"

int	env_count(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

int	env_to_array(t_env *env, t_env **arr, int count)
{
	int	i;

	i = 0;
	while (i < count && env)
	{
		arr[i++] = env;
		env = env->next;
	}
	return (i == count);
}

static void	env_sort_array(t_env **arr, int count)
{
	int	i;
	int	j;
	t_env	*tmp;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(arr[i]->key, arr[j]->key) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	print_sorted_env(t_env *env)
{
	int	count;
	int	i;
	t_env	**arr;

	count = env_count(env);
	arr = malloc(sizeof(*arr) * count);
	if (!arr)
		return (FAILURE);
	if (!env_to_array(env, arr, count))
		return (free(arr), FAILURE);
	env_sort_array(arr, count);
	i = 0;
	while (i < count)
	{
		printf("declare -x %s", arr[i]->key);
		if (arr[i]->val)
			printf("=\"%s\"", arr[i]->val);
		printf("\n");
		i++;
	}
	free(arr);
	return (EXIT_SUCCESS);
}
