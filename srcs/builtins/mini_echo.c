#include "minishell.h"

int	mini_echo(char **argv, int i, t_shell *shell)
{
	int	j;
	int	nflag;

	nflag = 0;
	while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		j = 2;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0')
			break ;
		nflag = 1;
		i++;
	}
	while (argv[i])
	{
		argv[i] = strip_quotes(shell->arena, argv[i]);
		ft_putstr(argv[i++]);
		if (argv[i])
			ft_putchar(' ');
	}
	if (!nflag)
		ft_putchar('\n');
	return (EXIT_SUCCESS);
}
