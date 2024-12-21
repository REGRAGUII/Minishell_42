/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:34:21 by yregragu          #+#    #+#             */
/*   Updated: 2024/11/27 18:29:23 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	unset_helper(t_cmd *cmd, t_env *head, t_env *prev, t_lexer *temp)
{
	while (head)
	{
		if (!ft_strncmp(head->key, temp->str, ft_strlen(temp->str))
			&& head->key[ft_strlen(temp->str)] == '\0')
		{
			if (prev == NULL)
				cmd->env_new = head->next;
			else
				prev->next = head->next;
			break ;
		}
		prev = head;
		head = head->next;
	}
}

int	unset(t_cmd *cmd)
{
	t_env	*head;
	t_env	*prev;
	t_lexer	*temp;	

	if (!cmd->lexer)
		return (127);
	temp = cmd->lexer->next;
	while (temp)
	{
		head = cmd->env_new;
		prev = NULL;
		unset_helper(cmd, head, prev, temp);
		temp = temp->next;
	}
	return (0);
}
