#include "minishell.h"

void	exec_child_process2(t_cmd *next_cmd)
{
	dup2(next_cmd->fds[1], STDOUT);
	close(next_cmd->fds[1]);
}

void	exec_child_process(t_cmd *cmd, t_cmd *next_cmd, int i)
{
	int		ret;
	char	*path;

	ret = EXIT_SUCCESS;
	path = find_path(cmd->cmdlines[0], g_global.g_envp);
	if (cmd->flag == 1)
	{
		exec_child_process2(next_cmd);
	}
	if (cmd->fds[0] != 0)
	{
		dup2(cmd->fds[0], STDIN);
		close(cmd->fds[0]);
	}
	if (check_builtin(cmd->cmdlines) == TRUE)
		exec_builtin(cmd, cmd->cmdlines);
	else
	{
		while (cmd->cmdlines[++i])
			remove_char(cmd->cmdlines[i], '\'');
		ret = execve(path, cmd->cmdlines, g_global.g_envp);
	}
	if (ret == -1)
		print_execute_err_1(cmd->cmdlines[0], "command not found");
	exit(ret);
}

int	exec_pipe(t_list *cur_proc, t_cmd *cmd, int ret)
{
	pid_t	pid;
	int		status;
	t_cmd	*next_cmd;

	ret = EXIT_SUCCESS;
	next_cmd = cur_proc->content;
	if (cmd->flag == 1)
	{
		next_cmd = cur_proc->next->content;
		next_cmd->preflag = 1;
		pipe(next_cmd->fds);
	}
	pid = fork();
	if (pid == 0)
		exec_child_process(cmd, next_cmd, 0);
	waitpid(pid, &status, 0);
	if WEXITSTATUS(status)
		g_global.g_exit_status = 1;
	else
		g_global.g_exit_status = 0;
	if (cmd->flag == 1)
		close(next_cmd->fds[1]);
	if (cmd->fds[0] != 0)
		close(cmd->fds[0]);
	return (ret);
}

int	exec_builtin(t_cmd *cmd, char **cmdline)
{
	char	*builtin;
	char	**tmp;

	builtin = cmd->cmdlines[0];
	if (!ft_strcmp(builtin, "cd"))
		cd(cmdline, g_global.g_envp, 0, 0);
	else if (!ft_strcmp(builtin, "echo"))
		echo(cmd, cmdline, g_global.g_envp, 0);
	else if (!ft_strcmp(builtin, "pwd"))
		pwd();
	else if (!ft_strcmp(builtin, "env"))
		env(g_global.g_envp);
	else if (!ft_strcmp(builtin, "export"))
	{
		tmp = cmdline;
		ft_export(cmd, cmdline, 0, tmp);
	}
	else if (!ft_strcmp(builtin, "unset"))
		unset(cmd, cmdline);
	else if (!ft_strcmp(builtin, "exit"))
		ft_exit(cmd, cmdline, 0);
	else
		return (0);
	return (1);
}
