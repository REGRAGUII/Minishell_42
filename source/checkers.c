/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:03:16 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/25 18:25:39 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parce.h"

int	ft_check_type(t_lexer *head)
{
	if (!head ->next || !head->next->str)
	{
		return (1);
	}
	head = head->next;
	while (head)
	{
		if (ft_is_reder(head) != -1)
		{
			return (1);
		}
		if (head->str && head->type != WHITE_SPACE && ft_is_reder(head) == -1)
			return (0);
		head = head->next;
	}
	return (1);
}

static int	ft_check_after_pipe(t_lexer *head)
{
	if (!head || head->type == PIP)
		return (1);
	while (head && head->type == WHITE_SPACE)
		head = head->next;
	if (!head || head->type == END_OF_LIST)
		return (1);
	if (ft_is_reder(head) != -1 || head->type == STR)
		return (0);
	return (1);
}

static int	check_redir_before_pipe(t_lexer *head)
{
	while (head && head->type == WHITE_SPACE)
		head = head->next;
	if (!head || head->type == PIP)
	{
		ft_error(PIP);
		return (PIP);
	}
	if (ft_is_reder(head) != -1)
	{
		ft_error(head->type);
		return (1);
	}
	if (ft_is_reder(head) != -1)
	{
		head = head->next;
		while (head && head->type == WHITE_SPACE)
			head = head->next;
		if (!head || head->type != STR)
		{
			ft_error(STR);
			return (1);
		}
	}
	return (0);
}

int	ft_check_pip(t_lexer *lexer)
{
	t_lexer	*head;
	int		status;

	head = lexer;
	while (head)
	{
		if (head->type == PIP)
		{
			head = head->next;
			status = ft_check_after_pipe(head);
			if (status == 1)
				return (1);
			if (status == 2)
				continue ;
		}
		head = head->next;
	}
	return (0);
}

int	half_cheker(t_cmd *cmd)
{
	t_lexer	*head;

	head = cmd->lexer;
	while (head)
	{
		if (ft_is_reder(head) != -1)
		{
			if (check_redir_before_pipe(head->next))
				return (1);
			if (ft_check_type(head))
			{
				ft_error(head->type);
				return (1);
			}
		}
		if (head->type == PIP && ft_check_pip(head))
		{
			ft_error(PIP);
			return (1);
		}
		head = head->next;
	}
	return (0);
}
