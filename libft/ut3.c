#include "libft.h"

char	*ft_strtok(char *str, char sepa)
{
	static char	*stock = NULL;
	char		*p;
	int			i;

	i = 0;
	p = NULL;
	if (str != NULL)
		stock = ft_strdup(str);
	while (*stock != '\0')
	{
		if (i == 0 && *stock != sepa)
		{
			i = 1;
			p = stock;
		}
		else if (i == 1 && *stock == sepa)
		{
			*stock = '\0';
			stock += 1;
			break ;
		}
		stock++;
	}
	return (p);
}

static char	*ft_str_copy(char *s1, char *result, int start, int end)
{
	int		i;

	i = 0;
	while (s1[start + i] && start + i <= end)
	{
		result[i] = s1[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static int	ft_find_start_index(int i, char *s1, char *set)
{
	int		j;

	while (s1[i])
	{
		j = 0;
		while (set[j] && s1[i] != set[j])
			j++;
		if (set[j] == 0)
			break ;
		i++;
	}
	return (i);
}

static int	ft_find_end_index(int k, char *s1, char *set)
{
	int		j;

	while (s1[k] && k > 0)
	{
		j = 0;
		while (set[j] && s1[k] != set[j])
			j++;
		if (set[j] == 0)
			break ;
		if (k == 0)
			break ;
		k--;
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		start;
	int		end;

	if (s1 == 0)
		return (ft_strdup(""));
	start = ft_find_start_index(0, (char *)s1, (char *)set);
	end = ft_find_end_index(ft_strlen((char *)s1) - 1, (char *)s1, (char *)set);
	if (start == (int)ft_strlen((char *)s1) || end == 0)
		return (ft_strdup(""));
	result = (char *)malloc((end - start + 1 + 1) * sizeof(char));
	if (!result)
		return (ft_strdup(""));
	return (ft_str_copy((char *)s1, result, start, end));
}
