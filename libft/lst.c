#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*p;

	p = (t_list *)malloc(sizeof(t_list));
	if (!p)
		return (NULL);
	p->content = content;
	p->next = NULL;
	return (p);
}

static int	each_len(char const *s, char c, int start)
{
	int		len;

	len = 0;
	while (s[start + len] != '\0' && s[start + len] != c)
		len++;
	return (len);
}

static int	find_start(char const *s, char c, int i)
{
	while (s[i] != '\0' && s[i] == c)
		i++;
	return (i);
}

static int	count_words(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i] == '\0' && s[i - 1] != c)
			count = count + 1;
		if (s[i] == '\0')
			break ;
		count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		start;
	int		i;
	int		j;

	i = 0;
	array = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	start = find_start(s, c, 0);
	while (i < count_words(s, c))
	{
		j = 0;
		array[i] = malloc((each_len(s, c, start) + 1) * sizeof(char));
		while (s[start + j] && s[start + j] != c)
		{
			array[i][j] = s[start + j];
			j++;
		}
		array[i][j] = '\0';
		start = find_start(s, c, start + j);
		i++;
	}
	array[i] = (char *)0;
	return (array);
}
