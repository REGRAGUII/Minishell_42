/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:55:56 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/27 18:56:50 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parce.h"

void	fix_err(t_cmd *cmd)
{
	t_lexer	*head;

	head = cmd->lexer;
	while (head)
	{
		if (head->next && head->next->exp_err == 1)
			head->exp_err = 1;
		else
			head->exp_err = 0;
		head = head->next;
	}
}

int	check_expand_args(t_cmd *cmd)
{
	t_lexer	*head;

	head = cmd->lexer;
	if (head && head->next && head->next->type != END_OF_LIST
		&& head->next->type != WHITE_SPACE)
		head = head->next;
	else
		return (0);
	while (head)
	{
		if (head->type != STR && head->type != WHITE_SPACE)
			return (0);
		if (head->type == STR)
			return (1);
		head = head->next;
	}
	return (0);
}

int	ft_endof_expand(char *str)
{
	int	i;

	i = 0;
	if (str[0] && !ft_isalpha(str[0]))
	{
		return (0);
	}
	while (str && str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isnum(str[i]))
			return (i);
		i++;
	}
	return (i);
}

int	has_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_words(char **str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i][0])
		i++;
	return (i);
}
