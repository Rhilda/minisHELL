#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <term.h>

# define MAXSIZE		1024

# define FALSE			0
# define TRUE			1

# define ERROR			-1
# define SUCCESS 		1

# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2

# define SYNTAX_ERROR	"Syntax error: near unexpected token!"
# define QUOTE_ERROR 	"The number of Quotes is odd!"
# define MALLOC_ERROR 	"Memory malloc fail!"
# define PIPE_ERROR 	"Pipe function is failed!"
# define FORK_ERROR 	"Fork function is failed!"

# define BREDIR			60
# define REDIR			62
# define DREDIR			6

struct s_global
{
	char		**g_envp;
	int			g_exit_status;
	int			g_parse_error;
};

struct s_global	g_global;

typedef struct s_redir
{
	int			argc;
	char		**argv;
	char		**cmds;
	char		*types;
}				t_redir;

typedef struct s_cmd
{
	char		**cmdlines;
	int			flag;
	int			preflag;
	char		quote;
	int			dquote;
	int			fds[2];
	int			has_redir;
}				t_cmd;

typedef struct s_data
{
	t_list		*lstlast;
	t_cmd		*cmd;
	char		*buff;
	int			i;
	int			j;
	int			k;
}				t_data;

typedef struct s_echo
{
	char		**p;
	char		**s;
	int			j;
	int			k;
	int			b;
	int			c;
	int			d;
}				t_echo;

void			init_redir(char *command, t_redir *re);
int				parse_redir_final(t_redir *r, int j);
int				parse_redir(char *command, t_redir *r);
void			open_unnecessary_files(t_redir *r);
void			exec_redir(t_cmd *cmd, char **cmdline);
char			*ft_strjoin_c(char *s, char c);
char			*change_from_double_to_single_cmdline(char **cmdline);
char			*remove_single_quotes(char *str);
void			cmd_redir(t_cmd *cmd, t_redir *r);
int				is_single_redir(char *command, int i);
int				find_redir_type(char *command, int i);
int				has_redir_syntax_error(char *str);
int				ft_puterror_fd(char *s1, char *s2, int fd);
char			*substr_and_trim(char *command, int start, int num, \
					char *charset);
void			ree_double_arr(char **arr);
void			*parse(char *input_temp);
void			parse_all_char(char *input, t_data *data, t_list *head);
int				add_node(t_data *data, t_list *head, char *input, int symbol);
void			put_buff_into_cmdline(t_data *data);
void			*initialize(char *input, t_data *data, t_list **head);
int				count_token(char *input);
int				check_white_space(char *input);
void			*parse_error(t_data *ptr1, t_list *ptr2, char *comment);
void			free_cmdline(void *content);
void			free_double_str(char **ptr);
char			**copy_envp(char **envs);
void			show_prompt(void);
void			set_signal(void);
void			handle_signal(int signo);
char			*find_value(char *key, char **envs);
void			free_double_arr(char **arr);
char			*find_path(char *cmdline, char **envs);
void			echo_init(t_echo *ec, char **cmdline, int i);
void			echo_env(char **cmdline, char **envs, int i);
void			echo_env(char **cmdline, char **envs, int i);
void			echenv(char **cmdline, char **envs, int i);
void			echo_2(char **cmdline, char **envs, int i);
void			echo_1(char **cmdline, int *i, int *n);
void			print_exit_status(void);
int				check_builtin(char **cmdline);
int				remove_char(char *str, char c);
int				check_export(char *str, char ***envs, int i, int j);

void			exec_process(t_list *proc);
int				exec_builtin(t_cmd *cmd, char **cmdline);
int				exec_pipe(t_list *cur_proc, t_cmd *cmd, int ret);
void			exec_child_process(t_cmd *cmd, t_cmd *next_cmd, int i);

void			env(char **envs);
void			pwd(void);
void			cd(char **cmdline, char **envsm, char *path, int ret);
void			echo(t_cmd *cmd, char **cmdline, char **g_envp, int n);
void			ft_exit(t_cmd *cmd, char **cmdline, int i);
void			ft_export(t_cmd *cmd, char **cmdline, int i, char **tmp);
void			unset(t_cmd *cmd, char **cmdline);

void			print_errno_err(char *err_msg);
int				print_execute_err_1(char *token, char *err_msg);
int				print_execute_err_2(char *token1, char *token2, char *err_msg);
void			print_identifier_err(char *token1, char *token2);
void			rl_replace_line (const char *text, int clear_undo);

#endif
