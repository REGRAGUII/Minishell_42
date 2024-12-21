/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:59:31 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/28 14:40:38 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parce.h"

void	split_pip(t_cmd *cmd, t_cmd *new_cmd)
{
	t_lexer	*head;
	t_lexer	*last;
	t_cmd	*new_cmd_tmp;

	head = cmd->lexer;
	new_cmd->lexer = head;
	new_cmd_tmp = ft_lstnew_cmd(cmd);
	while (head)
	{
		if (head->type == PIP)
		{
			head = head->next;
			last->next = head;
			last->next = NULL;
			new_cmd->next = new_cmd_tmp;
			new_cmd = new_cmd->next;
			new_cmd->lexer = head;
			new_cmd_tmp = ft_lstnew_cmd(cmd);
		}
		last = head;
		head = head->next;
	}
}

int	add_cmp(void *p1, void *p2)
{
	if (p1 == p2)
		return (1);
	return (0);
}

void	ft_free(t_cmd *cmd)
{
	t_garb	*garb;
	t_garb	*last;

	garb = cmd->garb;
	garb = garb->next;
	while (garb)
	{
		if (garb->address)
			free(garb->address);
		last = garb;
		garb = garb->next;
		if (last == garb)
			break ;
		free(last);
		last = NULL;
	}
}

void	join_str(t_cmd *cmd, t_lexer *lexer)
{
	t_lexer	*head;

	head = lexer;
	while (head)
	{
		if (head->type == STR && head->next && head->next->type == STR)
		{
			join_node(cmd, head, head->next);
			continue ;
		}
		head = head->next;
	}
}
