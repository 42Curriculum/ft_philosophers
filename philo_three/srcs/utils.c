#include <limits.h>
#include "philo_three.h"

long long	ft_atol(char *str)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (result);
}

size_t	ft_strlcat(char *dst, char *src, size_t destsize)
{
	size_t len;
	size_t i;
	size_t destl;

	destl = ft_strlen(dst);
	i = 0;
	len = destl;
	if (destsize <= 0)
		return (ft_strlen(src));
	while (src[i] && destl < destsize - 1)
	{
		dst[destl] = src[i];
		i++;
		destl++;
	}
	dst[destl] = '\0';
	if (destsize < len)
		return (destsize + ft_strlen(src));
	return (len + ft_strlen(src));
}

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

unsigned int	ft_intsize(long long nb, int base)
{
	int len;

	len = 1;
	if (nb < 0)
		nb *= -1;
	while (nb >= base)
	{
		nb /= base;
		len += 1;
	}
	return (len);
}

char		*ft_ltoa_base(long long value, int base)
{
	int			len;
	long long	nbr;
	char		*str;
	char		*s_base;

	s_base = "0123456789abcdef";
	len = (int)ft_intsize(value, base);
	nbr = value;
	if (nbr < 0)
	{
		if (base == 10)
			len += 1;
		nbr *= -1;
	}
	str = malloc(len);
	while (len > 0)
	{
		str[--len] = s_base[nbr % base];
		nbr /= base;
	}
	if (value < 0 && base == 10)
		str[0] = '-';
	return (str);
}