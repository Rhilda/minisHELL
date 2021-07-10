
NAME = libft.a

SRCS = put.c ut.c utt.c ut2.c ut3.c lst.c ut5.c ssplit.c

OBJS = $(SRCS:%.c=%.o)

CFLAGS = -Wall -Wextra -Werror -I. -c

all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $@ $^

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:		all clean fclean re