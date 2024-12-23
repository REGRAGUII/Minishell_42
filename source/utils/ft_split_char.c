/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:04:31 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/28 14:32:52 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parce.h"

static int	char_counter(char *str, char c)
{
	unsigned int	counter;

	counter = 0;
	while (str[counter])
	{
		if (str[counter] == c)
			return (counter);
		counter++;
	}
	return (counter);
}

static char	*str_cut(char *s, unsigned int i)
{
	char			*str;
	unsigned int	counter;

	if (!s)
		return (NULL);
	str = (char *)ft_malloc(g_main.garb, (i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	counter = 0;
	while (s[counter] && counter < i)
	{
		str[counter] = s[counter];
		counter++;
	}
	str[counter] = '\0';
	return (str);
}

static int	words_count(char *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		counter++;
		while (str[i] != c && str[i])
			i++;
		while (str[i] == c && str[i])
			i++;
	}
	return (counter);
}

static void	**my_copying(char **str, char *p, char c, int words_number)
{
	int	i;

	i = 0;
	while (i < words_number)
	{
		while (*p == c && *p)
			p++;
		if (*p != c && *p)
		{
			str[i] = str_cut(p, char_counter(p, c));
			if (!str[i])
			{
				return ((void *)0);
			}
			i++;
		}
		while (*p != c && *p)
			p++;
	}
	return ((void **)str);
}

char	**ft_split_char(char *s, char c)
{
	char	**str;
	char	*ptr;
	int		words_number;

	if (!s)
		return (NULL);
	ptr = ft_strdup(g_main.garb, s);
	if (!ptr)
		return (NULL);
	words_number = words_count(ptr, c);
	str = (char **)ft_malloc(g_main.garb, (words_number + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	my_copying(str, ptr, c, words_number);
	str[words_number] = NULL;
	return (str);
}
