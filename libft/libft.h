#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef FD_NUMBER
#  define FD_NUMBER 256
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void			itto(int n, long long *nbr, int *flag);
int				ft_isalnum(int c);
size_t			ft_strlcpy(char *dest, const char *src, size_t dstsize);
char			**ssplit(int cc, char const *s, char c, unsigned int i);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
int				get_next_line(int fd, char **line);
char			*ft_strtok(char *str, char sepa);
char			*ft_strcpy(char *dest, char *src);
int				ft_strcmp(char *s1, char *s2);
int				ft_double_strlen(char **str);
int				ft_isdigit_str(char *str);
#endif
