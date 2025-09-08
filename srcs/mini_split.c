
#include "minishell.h"

static int  is_in_charset(const char *del, char c)
{
	size_t  i;

	i = 0;
	while (del[i])
	{
		if (del[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	int	ft_countwords(char const *str, const char *del)
{
	int	i;
	int	trigger;
	int	count;

	i = 0;
	trigger = 0;
	count = 0;
	while (str[i])
	{
		if (!is_in_charset(del, str[i]) && trigger == 0)
		{
			count++;
			trigger = 1;
		}
		else if (is_in_charset(del, str[i]))
		{
			trigger = 0;
		}
		i++;
	}
	return (count);
}

static char	**ft_free(char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(arr[i++]);
	}
	free(arr);
	return (0);
}

static char	**ft_array(char **array, char const *s, int start, const char *del)
{
	size_t	j;
	size_t	i;
	size_t	len;

	j = 0;
	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (!is_in_charset(del, s[i]) && start < 0)
			start = i;
		else if ((is_in_charset(del, s[i]) && start != -1)
			|| (i == len && start >= 0))
		{
			array[j] = ft_substr(s, start, i - start);
			if (!array[j])
				return (ft_free(array, j));
			j++;
			start = -1;
		}
		i++;
	}
	array[j] = 0;
	return (array);
}

char	**mini_split(char const *s, const char *del)
{
	int		start;
	char	**array;

	if (!s)
		return (NULL);
	start = -1;
	array = malloc((ft_countwords(s, del) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array = ft_array(array, s, start, del);
	return (array);
}
