NAME	=	minishell
NAME_BONUS	=	minishell_bonus
SRCS	= 	mini.c envv.c errors.c exe.c \
			echo.c\
			env.c \
			cd.c \
			export.c \
			unset.c \
			pars.c \
			util1.c \
			util2.c \
			cmd_redir.c \
			exec_redir.c \
		utils_redir.c \
		utils_redir2.c \
		echo_2.c

BONUS	= 	mini.c envv.c errors.c exe.c \
			echo.c\
			env.c \
			cd.c \
			export.c \
			unset.c \
			pars.c \
			util1.c \
			util2.c \
			cmd_redir.c \
			exec_redir.c \
		utils_redir.c \
		utils_redir2.c \
		echo_2.c

BONUS_OBJS = $(BONUS:.c=.o)

LIBFT	=	libft.a

LIBS	=	-L./libft -lft -I./

FLAG	= 	-Wall -Wextra -Werror

DEBUG	=	-g -fsanitize=address

all		: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

OBJS = $(SRCS:c=o)

$(NAME)	:  $(OBJS)
	$(MAKE) -C ./libft
	gcc $(SRCS) $(LIBS)  $(FLAG) $(DEBUG) -o $(NAME)  -lreadline -L/Users/rhilda/.brew/Cellar/readline/8.1/lib/ -I/Users/rhilda/.brew/Cellar/readline/8.1/include -ltermcap

clean	:
	$(MAKE) -C ./Libft clean
	rm -rf $(OBJS)
	rm -rf $(BONUS_OBJS)

fclean	: clean
	$(MAKE) -C ./Libft fclean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

re		: fclean all

bonus: $(BONUS_OBJS)
	$(MAKE) -C ./libft
	gcc $(SRCS) $(LIBS)  $(FLAG) $(DEBUG) -o $(NAME_BONUS)  -lreadline -L/Users/ichariss/.brew/Cellar/readline/8.1/lib/ -I/Users/ichariss/.brew/Cellar/readline/8.1/include -ltermcap

.PHONY:		all clean fclean re