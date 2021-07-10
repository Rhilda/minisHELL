#include "minishell.h"

void	print_export(char **envs)
{
	int	i;

	i = -1;
	while (envs[++i])
	{
		ft_putstr_fd("declare -x ", STDIN);
		ft_putstr_fd(envs[i], STDIN);
		write(STDOUT, "\n", 1);
	}
}

void	add_export(char *str, char **new, int i)
{
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
}

int	check_export(char *str, char ***envs, int i, int j)
{
	char	**new;

	if (str[0] == '=' || str[0] == '\0' || ft_strlen(str) == 1)
		return (ERROR);
	while ((*envs)[++i] != NULL)
	{
		j = ft_strncmp((*envs)[i], str, ft_strlen(str));
		if (!j)
		{
			(*envs)[i] = ft_strdup(str);
			return (SUCCESS);
		}
	}
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (ERROR);
	i = -1;
	while ((*envs)[++i])
		new[i] = ft_strdup((*envs)[i]);
	add_export(str, new, i);
	*envs = new;
	return (SUCCESS);
}

int	isvalid_export(char *key)
{
	int	i;

	i = -1;
	while (key[++i])
	{
		if (key[i] >= '0' && key[i] <= '9')
			return (FALSE);
	}
	return (TRUE);
}

void	ft_export(t_cmd *cmd, char **cmdline, int i, char **tmp)
{
	int	ret;

	if (cmd->preflag == 1)
		return ;
	ret = 0;
	if (ft_double_strlen(cmdline) == 1)
		print_export(g_global.g_envp);
	else
	{
		remove_char(cmdline[1], '\'');
		while (cmdline[++i])
		{
			if (isvalid_export(ft_strtok(tmp[i], '=')) == FALSE)
			{
				print_identifier_err("export", tmp[i]);
				g_global.g_exit_status = 1;
			}
			remove_char(cmdline[i], '$');
			ret = check_export(cmdline[i], &g_global.g_envp, -1, 0);
		}
	}
	if (ret != SUCCESS)
		g_global.g_exit_status = 1;
}
