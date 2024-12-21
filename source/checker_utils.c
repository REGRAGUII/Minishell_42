/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:11:59 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/27 23:12:00 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parce.h"

int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}

int	ft_new_index(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isspace(str[i]) || str[i] == 34 || str[i] == '>'
			|| str[i] == '|' || str[i] == '<')
			return (i -1);
		if (str[i] == 39)
			return (i - 1);
		i++;
	}
	return (99999);
}

int	herdoc_check(t_cmd *cmd)
{
	if (cmd && cmd->docs > 17)
	{
		ft_putstr_fd("minishell : maximum here-document count exceeded\n", 2);
		ft_free(cmd);
		free(cmd->garb);
		free(cmd);
		exit(2);
	}
	return (0);
}

int	ft_checker(t_cmd *cmd)
{
	t_lexer	*head;

	head = cmd->lexer;
	herdoc_check(cmd);
	while (head)
	{
		if (head->type == PIP)
		{
			ft_error(PIP);
			return (1);
		}
		if (head->type == STR)
			break ;
		head = head->next;
	}
	return (half_cheker(cmd));
}
