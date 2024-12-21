/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:48:44 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/27 22:48:45 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parce.h"

char	*ft_str_dup_space(t_garb *garb, char *str)
{
	int		i;
	int		len;
	char	*res;

	len = ft_strlen_space(str);
	res = ft_malloc(garb, len + 1);
	res[len] = '\0';
	i = 0;
	while (str && str[i] && i < len)
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}

char	*ft_str_dup_char(t_garb *garb, char *str, char c)
{
	int		i;
	int		len;
	char	*res;

	len = ft_strlen_char(str, c);
	res = ft_malloc(garb, len + 1);
	res[len] = '\0';
	i = 0;
	while (str && str[i] && i < len)
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}

int	ft_strlen_q(char *str, int id)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (id == 0)
		{
			if (str[i] == '"')
				break ;
		}
		else
		{
			if (str[i] == 39)
				break ;
		}
		i++;
	}
	return (i);
}

char	*ft_str_dup_q(t_garb *garb, char *str, int id)
{
	int		i;
	int		len;
	char	*res;

	len = ft_strlen_q(str + 1, id);
	res = ft_malloc(garb, len + 1);
	res[len] = '\0';
	i = 0;
	while (str && str[i] && i < len)
	{
		res[i] = str[i + 1];
		i++;
	}
	return (res);
}

char	*ft_strdup(t_garb *garb, char *s)
{
	char	*str;
	size_t	index;
	size_t	lenth;

	lenth = ft_strlen(s);
	index = 0;
	if (!s)
		return (NULL);
	str = (char *)ft_malloc(garb, lenth + 1);
	if (!str)
		return (NULL);
	while (index < lenth)
	{
		str[index] = s[index];
		index++;
	}
	str[index] = '\0';
	return (str);
}
