/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:26:19 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/27 14:42:22 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parce.h"

int	need_split(t_cmd *cmd, t_lexer *lexer)
{
	t_lexer	*head;
	char	**res;

	head = lexer;
	if (head->type == STR && head->q_flag == 0)
	{
		res = ft_split(cmd->garb, head->str);
		if (res && res[0] && res[1])
			return (1);
	}
	return (0);
}

static t_lexer	*create_str_node(t_cmd *cmd, char *str)
{
	t_lexer	*node;

	node = ft_lstnew_lexer(cmd);
	node->str = str;
	node->q_flag = 1;
	node->type = STR;
	return (node);
}

static t_lexer	*create_space_node(t_cmd *cmd)
{
	t_lexer	*node;

	node = ft_lstnew_lexer(cmd);
	node->str = ft_strdup(cmd->garb, " ");
	node->type = WHITE_SPACE;
	node->q_flag = 0;
	return (node);
}

static void	handle_split(t_cmd *cmd, t_lexer **current, t_lexer **prev)
{
	t_lexer	*new_node;
	t_lexer	*space_node;
	char	**res;
	int		i;

	res = ft_split(cmd->garb, (*current)->str);
	if (!res)
		return ;
	new_node = create_str_node(cmd, res[0]);
	if (*prev)
		(*prev)->next = new_node;
	else
		cmd->lexer = new_node;
	i = 1;
	while (res && res[i])
	{
		space_node = create_space_node(cmd);
		new_node->next = space_node;
		space_node->next = create_str_node(cmd, res[i++]);
		new_node = space_node->next;
	}
	new_node->next = (*current)->next;
	*current = new_node;
}

void	add_nodes(t_cmd *cmd)
{
	t_lexer	*current;
	t_lexer	*prev;

	if (!cmd->lexer)
		return ;
	current = cmd->lexer;
	prev = NULL;
	while (current)
	{
		if (need_split(cmd, current))
		{
			handle_split(cmd, &current, &prev);
			current->exp_err = 1;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
