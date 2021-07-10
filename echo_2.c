#include "minishell.h"

void	print_exit_status(void)
{
	ft_putstr_fd(ft_itoa(g_global.g_exit_status), 1);
}

void	echo_env(char **cmdline, char **envs, int i)
{
	char	*value;

	if (cmdline[i][0] == '?')
		print_exit_status();
	value = find_value(&(cmdline[i][0]), envs);
	ft_putstr_fd(value, STDIN);
}

void	echenv(char **cmdline, char **envs, int i)
{
	char	*value;

	if (cmdline[i][0] == '$' && cmdline[i][1] == '?')
		print_exit_status();
	value = find_value(&(cmdline[i][1]), envs);
	ft_putstr_fd(value, STDIN);
}

void	echo_init(t_echo *ec, char **cmdline, int i)
{
	ec->j = -1;
	ec->c = 0;
	ec->b = -1;
	ec->k = -1;
	while (cmdline[i][++ec->b])
	{
		if (cmdline[i][ec->b] == ' ')
			ec->c++;
	}
	ec->p = ssplit(ec->c, cmdline[i], ' ', 0);
}

void	echo(t_cmd *cmd, char **cmdline, char **envs, int n)
{
	int	i;

	i = 1;
	if (cmdline[i])
		echo_1(cmdline, &i, &n);
	while (cmdline[i])
	{
		if (cmdline[i][0] == '\'' && !cmd->dquote)
		{
			remove_char(cmdline[i], '\'');
			ft_putstr_fd(cmdline[i], STDOUT);
		}
		else
			echo_2(cmdline, envs, i);
		if (cmdline[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT);
		i++;
	}
	if (n != -1)
		ft_putchar_fd('\n', STDOUT);
}
