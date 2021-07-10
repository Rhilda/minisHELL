#include "minishell.h"

void	env(char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
	{
		write(STDOUT, envs[i], ft_strlen(envs[i]));
		write(STDOUT, "\n", 1);
		i++;
	}
	g_global.g_exit_status = 0;
}

void	pwd(void)
{
	char	*pwd;
	int		ret;

	ret = EXIT_SUCCESS;
	pwd = getcwd(0, MAXSIZE);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	g_global.g_exit_status = 0;
}

void	exit_errcode(void)
{
	ft_putstr_fd("exit\n", STDERR);
	exit(g_global.g_exit_status);
}

void	ft_exit(t_cmd *cmd, char **cmdline, int	argc)
{
	if (cmd->preflag == 1)
		return ;
	if (cmdline[1])
		remove_char(cmdline[1], '\'');
	while (cmdline[argc] != NULL)
		argc++;
	if (argc == 1)
		exit_errcode();
	else if (argc == 2 && ft_isdigit_str(cmdline[1]))
		g_global.g_exit_status = ft_atoi(cmdline[1]);
	else if (argc > 2 && ft_isdigit_str(cmdline[1]))
	{
		ft_putstr_fd("exit\n", STDERR);
		print_execute_err_1("exit", "too many arguments");
		g_global.g_exit_status = 1;
		return ;
	}
	else
	{
		print_execute_err_2("exit", cmdline[1], "numeric argument required");
		g_global.g_exit_status = 255;
		exit(g_global.g_exit_status & 255);
	}
	exit_errcode();
}
