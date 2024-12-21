/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:01:36 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/25 17:33:16 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parce.h"

int	check_pip(t_lexer *lexer)
{
	t_lexer	*head;

	head = lexer;
	while (head)
	{
		if (head->type == PIP)
		{
			head = head->next;
			if (!head || head->type == PIP)
				return (1);
			else if (head->type != WHITE_SPACE)
				continue ;
			while (head)
			{
				if (head->type != WHITE_SPACE && head->type != END_OF_LIST)
					break ;
				head = head->next;
			}
			if (!head)
				return (1);
		}
		head = head->next;
	}
	return (0);
}

void	join_node(t_cmd *cmd, t_lexer *head, t_lexer *next)
{
	char	*tmp;

	tmp = ft_strjoin(cmd->garb, head->str, next->str);
	next = next->next;
	head->str = NULL;
	head->str = tmp;
	head->next = NULL;
	head->next = next;
}

void	remove_space(t_lexer *head, t_lexer *removed)
{
	head->next = removed->next;
	removed = NULL;
}

void	join_space(t_lexer *head, t_lexer *next)
{
	next = next->next;
	head->next = NULL;
	head->next = next;
}

void	skip_space(t_cmd *cmd, t_lexer *lexer)
{
	t_lexer	*head;

	head = cmd->lexer;
	while (cmd->lexer->type == WHITE_SPACE)
		cmd->lexer = cmd->lexer->next;
	while (head)
	{
		if (head->type == WHITE_SPACE && head->next
			&& head->next->type == WHITE_SPACE)
		{
			join_space(head, head->next);
			continue ;
		}
		head = head->next;
	}
	head = lexer;
	while (head)
	{
		if (head->next && head->next->type == WHITE_SPACE && head->next->next)
		{
			remove_space(head, head->next);
		}
		head = head->next;
	}
}
