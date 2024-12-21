/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:22:39 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/28 13:36:37 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parce.h"

int	ft_new_index_qq(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '"')
			return (i + 1);
		i++;
	}
	return (99999);
}

int	ft_new_index_q(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == 39)
			return (i + 1);
		i++;
	}
	return (99999);
}

t_cmd	*parce(char *str, t_cmd *cmd)
{
	t_cmd	*new_cmd;

	new_cmd = ft_lstnew_cmd(cmd);
	cmd->cmd = str;
	if (check_unclosed_quote(str))
	{
		ft_error(11);
		return (NULL);
	}
	cmd->docs = 0;
	ft_lexer(cmd->lexer, cmd);
	if (ft_checker(cmd))
		return (NULL);
	if (ft_expand(cmd))
		return (NULL);
	add_nodes(cmd);
	join_str(cmd, cmd->lexer);
	skip_space(cmd, cmd->lexer);
	split_pip(cmd, new_cmd);
	return (new_cmd);
}
