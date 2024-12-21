/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:44:19 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/25 18:08:55 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parce.h"

static int	handle_double_quotes(const char *str, int *i)
{
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == '"')
			return (0);
		(*i)++;
	}
	return (1);
}

static int	handle_single_quotes(const char *str, int *i)
{
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == '\'')
			return (0);
		(*i)++;
	}
	return (2);
}

int	check_unclosed_quote(char *str)
{
	int	i;
	int	ret;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			ret = handle_double_quotes(str, &i);
			if (ret)
				return (ret);
		}
		else if (str[i] == '\'')
		{
			ret = handle_single_quotes(str, &i);
			if (ret)
				return (ret);
		}
		i++;
	}
	return (0);
}
