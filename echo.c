#include "minishell.h"

void	echo_envv(char **cmdline, char **envs, int i)
{
	char	*value;

	if (cmdline[i][0] == '$' && cmdline[i][1] == '?')
		print_exit_status();
	value = find_value(&(cmdline[i][1]), envs);
	ft_putstr_fd(value, STDIN);
}

int	check_option_n(char *token)
{
	int	i;

	if (!token)
		return (FALSE);
	if (ft_strncmp(token, "-n", 2) != 0)
		return (FALSE);
	i = 2;
	while (token[i])
	{
		if (token[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	echo2(char **envs, t_echo ec)
{
	ft_putchar_fd('\'', STDOUT);
	remove_char(ec.p[ec.j], '\'');
	echenv(ec.p, envs, ec.j);
	ft_putchar_fd('\'', STDOUT);
}

void	echo_2(char **cmdline, char **envs, int i)
{	
	t_echo	ec;
	char	*a;

	echo_init(&ec, cmdline, i);
	while (ec.p[++ec.j])
	{
		ec.d = -1;
		a = ft_strchr(&ec.p[ec.j][1], '$');
		if (ec.p[ec.j][0] == '$' && a)
		{
			ec.s = ft_split(ec.p[ec.j], '$');
			while (ec.s[++ec.d])
				echo_env(ec.s, envs, ec.d);
			free_double_str(ec.s);
		}
		else if (ec.p[ec.j][0] == '$')
			echo_envv(ec.p, envs, ec.j);
		else if (ec.p[ec.j][0] == '\'' && ec.p[ec.j][1] == '$')
			echo2(envs, ec);
		else
			ft_putstr_fd(ec.p[ec.j], STDOUT);
	}
	free_double_str(ec.p);
}

void	echo_1(char **cmdline, int *i, int *n)
{
	int	check;

	check = check_option_n(cmdline[*i]);
	while (check)
	{
		*n = -1;
		*i = *i + 1;
		check = check_option_n(cmdline[*i]);
	}
}
