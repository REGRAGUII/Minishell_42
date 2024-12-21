/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:48:46 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/27 22:48:47 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parce.h"

static int	ft_count(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static	char	*ft_isnegative(t_cmd *cmd, long n, int lenth)
{
	char	*str;

	if (n == 0)
	{
		str = ft_malloc(cmd->garb, sizeof(char) * 2);
		if (!str)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	n *= -1;
	str = (char *)ft_malloc(cmd->garb, sizeof(char) * lenth + 1);
	if (!str)
		return (NULL);
	str[0] = '-';
	str[lenth] = '\0';
	lenth--;
	while (n)
	{
		str[lenth] = n % 10 + 48;
		n = n / 10;
		lenth--;
	}
	return (str);
}

char	*ft_itoa(t_cmd *cmd, int n)
{
	int		lenth;
	char	*str;

	lenth = ft_count(n);
	if (n <= 0)
		return (ft_isnegative(cmd, (long)n, lenth));
	str = ft_malloc(cmd->garb, (sizeof(char) * lenth) + 1);
	if (!str)
		return (NULL);
	str[lenth] = '\0';
	lenth--;
	while (n)
	{
		str[lenth] = n % 10 + 48;
		n = n / 10;
		lenth--;
	}
	return (str);
}

char	*ft_strncpy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
