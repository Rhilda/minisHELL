#include "minishell.h"

char	**copy_envp(char **envs)
{
	char	**new;
	int		i;

	i = 0;
	while (envs[++i] != NULL)
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!(new))
		return (NULL);
	i = -1;
	while (envs[++i])
		new[i] = ft_strdup(envs[i]);
	new[i] = NULL;
	return (new);
}

char	*find_value(char *key, char **envs)
{
	int	i;

	i = -1;
	while (envs[++i])
	{
		if (!ft_strncmp(envs[i], key, ft_strlen(key)))
			return (envs[i] + ft_strlen(key) + 1);
	}
	return ("");
}

char	*find_path(char *cmdline, char **envs)
{
	int			i;
	char		*temp;
	char		*new_path;
	char		**paths;
	struct stat	s;

	temp = find_value("PATH", envs);
	paths = ft_split(temp, ':');
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin("/", cmdline);
		new_path = ft_strjoin(paths[i], temp);
		free(temp);
		if (stat(new_path, &s) == 0)
			return (new_path);
		free(new_path);
	}
	return (ft_strdup(cmdline));
}

int	check_builtin(char **cmdline)
{
	char	*builtin;

	builtin = cmdline[0];
	if (!ft_strcmp(builtin, "cd") || !ft_strcmp(builtin, "echo")
		|| !ft_strcmp(builtin, "pwd") || !ft_strcmp(builtin, "env")
		|| !ft_strcmp(builtin, "export") || !ft_strcmp(builtin, "export")
		|| !ft_strcmp(builtin, "unset") || !ft_strcmp(builtin, "exit"))
		return (TRUE);
	return (FALSE);
}

int	remove_char(char *str, char c)
{
	int		new;
	int		i;

	new = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			str[new++] = str[i];
		i++;
	}
	str[new] = 0;
	return (TRUE);
}
