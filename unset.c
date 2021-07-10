#include "minishell.h"

int	isvalid_env(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
	{
		if (ft_isalnum(name[i]) || name[i] == '_')
			;
		else
			return (FALSE);
	}
	if (!i)
		return (FALSE);
	return (TRUE);
}

int	check_key_value(char *str, char *envs)
{
	int	i;

	i = 0;
	while (str[i] && envs[i] && (str[i] == envs[i]) && (envs[i] != '='))
		i++;
	if ((str[i] == '\0') && (envs[i] == '='))
		return (TRUE);
	return (FALSE);
}

int	unset_env(char *str, char ***envs)
{
	int	i;
	int	last;
	int	j;

	last = 0;
	while (((*envs)[last]) != NULL)
		last++;
	if (last < 1)
		return (ERROR);
	i = -1;
	while ((*envs)[++i] != NULL)
	{
		j = check_key_value(str, (*envs)[i]);
		if (j)
		{
			free((*envs)[i]);
			(*envs)[i] = ft_strdup((*envs)[last - 1]);
			free((*envs)[last - 1]);
			(*envs)[last - 1] = NULL;
			return (SUCCESS);
		}
	}
	return (SUCCESS);
}

void	unset(t_cmd *cmd, char **cmdline)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	if (cmd->preflag == 1)
		return ;
	while (cmdline[++i])
	{
		remove_char(cmdline[i], '\'');
		ret = isvalid_env(cmdline[i])
			& unset_env(cmdline[i], &g_global.g_envp);
	}
	if (ret != 1)
		g_global.g_exit_status = 1;
}
