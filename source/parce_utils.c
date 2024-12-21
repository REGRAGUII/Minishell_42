/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:19:13 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/28 14:58:14 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parce.h"

int	ft_is_reder(t_lexer *head)
{
	if (head && head->str)
	{
		if (head->type == REDIR_IN || head->type == REDIR_OUT
			|| head->type == HEREDOC || head->type == APPEND)
			return (head->type);
	}
	return (-1);
}

int	ft_count_char(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}

int	ft_next(char *str)
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

t_lexer	*ft_lstnew_lexer(t_cmd *cmd)
{
	t_lexer	*head;

	head = (t_lexer *)ft_malloc(cmd->garb, sizeof(t_lexer));
	if (!head)
		return (NULL);
	head->str = NULL;
	head->exp_err = 0;
	head->type = 0;
	head->fd_in = -1;
	head->next = NULL;
	return (head);
}

int	ft_next_q(char *str, int id)
{
	int	i;

	i = 1;
	while (str && str[i])
	{
		if (str[i] == '"' && id == 0)
			break ;
		if (str[i] == 39 && id == 1)
			break ;
		i++;
	}
	return (i);
}
