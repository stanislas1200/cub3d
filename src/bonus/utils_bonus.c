/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:25:48 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/11 16:25:48 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	ft_overfloaw(int neg)
{
	if (neg == 1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long		temp;
	long		nb;

	i = 0;
	neg = 1;
	nb = 0;
	temp = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = str[i++] - '0' + nb * 10;
		if (nb < temp)
			return (ft_overfloaw(neg));
		temp = nb;
	}
	return (nb * neg);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	j;

	j = 0;
	if (size != 0)
	{
		while (size - 1 > j && size != 0 && src[j])
		{
			dest[j] = src[j];
			j++;
		}
		dest[j] = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (dest[i] && i < size)
		i++;
	while (src[j])
		j++;
	if (i == size)
		return (j + size);
	while (src[k] && i + k < size - 1)
	{
		dest[i + k] = src[k];
		k++;
	}
	dest[i + k] = '\0';
	return (i + j);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)s1, len1 + 1);
	ft_strlcat(str, (char *)s2, len1 + len2 + 1);
	return (str);
}
