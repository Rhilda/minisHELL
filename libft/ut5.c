#include "libft.h"

int	ft_num_len(int n)
{
	long long	nbr;
	int			cnt;

	nbr = (long long)n;
	cnt = 0;
	if (nbr == 0)
		cnt = 1;
	else if (nbr < 0)
	{
		nbr = -nbr;
		cnt = 1;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		cnt++;
	}
	return (cnt);
}

void	itto(int n, long long *nbr, int *flag)
{
	if (n >= 0)
		*flag = 0;
	else
		*flag = 1;
	if (n >= 0)
		*nbr = (long long)n;
	else
		*nbr = -(long long)n;
}

char	*ft_itoa(int n)
{
	long long	nbr;
	char		*str;
	int			n_len;
	int			flag;

	n_len = ft_num_len(n);
	str = (char *)malloc(sizeof(char) * (n_len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	str[n_len] = '\0';
	itto(n, &nbr, &flag);
	n_len = n_len - 1;
	while (n_len >= flag)
	{
		str[n_len] = nbr % 10 + '0';
		nbr /= 10;
		n_len--;
	}
	return (str);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	i = 0;
	if (dest == 0 && src == 0)
		return (NULL);
	p1 = (unsigned char *)dest;
	p2 = (unsigned char *)src;
	while (p2[i] != (unsigned char)c && i < n)
	{
		p1[i] = p2[i];
		i++;
	}
	if (p2[i] == (unsigned char)c)
	{
		p1[i] = p2[i];
		return ((void *)(dest + i + 1));
	}
	return (NULL);
}
