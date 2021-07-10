#include "minishell.h"

int	count_token(char *input)
{
	int		count_token;
	char	*p;

	count_token = 1;
	p = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!(p))
		return (0);
	ft_strcpy(p, input);
	if (ft_strtok(p, ' ') != NULL)
	{
		while (ft_strtok(NULL, ' ') != NULL)
			count_token++;
	}
	free(p);
	return (count_token);
}

void	*initialize(char *input, t_data *data, t_list **head)
{
	*head = ft_lstnew(NULL);
	data->lstlast = *head;
	data->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!(data->cmd))
		return (parse_error(data, NULL, MALLOC_ERROR));
	data->cmd->cmdlines = ft_calloc(count_token(input) + 1,
			sizeof(char *));
	if (!(data->cmd->cmdlines))
		return (parse_error(data, NULL, MALLOC_ERROR));
	data->cmd->flag = 0;
	data->cmd->quote = 0;
	data->cmd->dquote = 0;
	data->cmd->has_redir = 0;
	data->buff = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!(data->buff))
		return (parse_error(data, NULL, MALLOC_ERROR));
	data->i = -1;
	data->j = 0;
	data->k = 0;
	return (NULL);
}

void	exec_redir(t_cmd *cmd, char **cmdline)
{
	int		ret;
	t_redir	r;
	char	*line;

	line = change_from_double_to_single_cmdline(cmdline);
	line = remove_single_quotes(line);
	init_redir(line, &r);
	ret = parse_redir(line, &r);
	if ((ret) <= 0)
	{
		if (ret < 0)
			ft_putendl_fd("syntax error near unexpected token `newline'", 1);
		return ;
	}
	open_unnecessary_files(&r);
	cmd_redir(cmd, &r);
}
