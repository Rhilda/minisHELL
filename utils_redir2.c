#include "minishell.h"

int	ft_puterror_fd(char *s1, char *s2, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putendl_fd(s2, fd);
	return (127);
}

char	*ft_strjoin_c(char *s, char c)
{
	char	*p;
	int		i;

	i = 0;
	p = ft_calloc(ft_strlen(s) + 2, sizeof(char));
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = c;
	p[i + 1] = '\0';
	if (s)
	{
		free(s);
		s = NULL;
	}
	return (p);
}

char	*change_from_double_to_single_cmdline(char **cmdline)
{
	char	*new_line;
	char	*temp;
	int		i;

	if (!cmdline)
		return (NULL);
	new_line = ft_strdup("");
	i = 0;
	while (cmdline[i])
	{
		temp = ft_strjoin(new_line, cmdline[i]);
		free(new_line);
		new_line = temp;
		if (cmdline[i + 1] != NULL)
			new_line = ft_strjoin_c(new_line, ' ');
		i++;
	}
	new_line[ft_strlen(new_line)] = '\0';
	return (new_line);
}

char	*remove_single_quotes(char *str)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)malloc(sizeof(char) * (strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '\'')
			p[i] = ' ';
		else
			p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (p);
}

void	exec_process(t_list *head)
{
	t_list	*cur_proc;
	t_cmd	*cmd;

	cur_proc = head->next;
	while (cur_proc != NULL)
	{
		cmd = cur_proc->content;
		if (cmd->cmdlines[0])
		{
			if (cmd->has_redir == 1 && cmd->flag == 0)
			{
				exec_redir(cmd, cmd->cmdlines);
				break ;
			}
			if ((check_builtin(cmd->cmdlines) == TRUE) && cmd->flag == 0)
				exec_builtin(cmd, cmd->cmdlines);
			else
			{	
				exec_pipe(cur_proc, cmd, 0);
			}
		}
		cur_proc = cur_proc->next;
	}
	ft_lstclear(&head, free_cmdline);
}
