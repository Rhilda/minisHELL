#include "minishell.h"

void	setup_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	handle_signal(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	setup_term();
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_global.g_exit_status = 1;
		}
		else
			ft_putstr_fd("^C\n", STDOUT);
	}
	else if (signo == SIGQUIT)
	{
		if (pid == -1)
			rl_on_new_line();
		else
			ft_putstr_fd("^\\Quit: 3\n", STDOUT);
	}
}

void	set_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	int		ret;

	(void)argv;
	g_global.g_exit_status = 0;
	g_global.g_envp = NULL;
	g_global.g_envp = copy_envp(envp);
	ret = argc;
	set_signal();
	while (ret)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("           ");
			printf("\033[Aexit\n");
			exit(0);
		}
		 if (ft_strlen(input) && !strnstr(input, "<<", ft_strlen(input)))
			 add_history(input);
		if (!check_white_space(input))
			parse(input);
		free(input);
	}
	return (g_global.g_exit_status & 255);
}
