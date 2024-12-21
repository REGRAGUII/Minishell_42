/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:50:30 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/27 22:50:45 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parce.h"

int	ft_expend_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c || !ft_isalnum(str[i]))
			break ;
		i++;
	}
	return (i + 1);
}

int	ft_strlen_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i + 1);
}

int	ft_strlen_expend(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isspace(str[i]) || str[i] == '$')
			break ;
		i++;
	}
	return (i);
}

int	ft_strlen_char_q(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c || str[i] == '"')
			break ;
		i++;
	}
	return (i + 1);
}

int	ft_strlen_space(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isspace(str[i]) || str[i] == '<' || str[i] == '>'
			|| str[i] == '|' || str[i] == '"' || str[i] == 39)
			break ;
		i++;
	}
	return (i);
}
