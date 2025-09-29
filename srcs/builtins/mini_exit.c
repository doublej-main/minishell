#include "minishell.h"

static unsigned char	exit_code_from_str(const char *str)
{
	int				sign;
	unsigned char	code;

	sign = 1;
	code = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		code = (code * 10 + (*str - '0')) % 256;
		str++;
	}
	if (sign < 0)
		code = (256 - code) % 256;
	return (code);
}

int	mini_exit(char **argv, t_shell *shell)
{
	(void)shell;
	if (!argv[1])
		exit(0);
	if (!ft_isnum(argv[1]))
	{
		perror("exit: numeric arg required\n");
		exit(2);
	}
	if (argv[2])
	{
		perror("exit: too many args\n");
		return (EXIT_FAILURE);
	}
	exit(exit_code_from_str(argv[1]));
}
