/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:54:32 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/27 22:44:17 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parce.h"

char	*ft_replace(t_vars *v, t_cmd *cmd, t_lexer *head)
{
	char	*res;

	res = ft_strndup(cmd->garb, v->str, v->skip);
	if (v->str[v->skip + 1] && v->str[v->skip + 1] == '?')
	{
		res = ft_strjoin(cmd->garb, res, ft_itoa(cmd, g_main.exit_s));
		v->skip++;
		if (!v->str[v->skip + 1])
			return (res);
		else
			res = ft_strjoin(cmd->garb, res, v->str + v->skip + 1);
		return (res);
	}
	v->res = ft_strdup(cmd->garb, res);
	res = half_replace(cmd, head, v);
	if (v->str[ft_endof_expand(v->str + v->skip +1) + 1])
		res = ft_strjoin(cmd->garb, res,
				v->str + v->skip + ft_endof_expand(v->str + v->skip + 1) + 1);
	return (res);
}

int	ft_get_var(t_cmd *cmd, t_lexer *head, char *str, t_vars *vars)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			if ((str[i + 1] && str[i + 1] == '$')
				|| (str[i] == '$' && !str[i + 1]) || (str[i] == '$'
					&& (ft_isspace(str[i + 1])
						|| !ft_isalpha(str[i + 1])) && str[i + 1] != '?'))
				i++;
			else
			{
				vars->skip = i;
				vars->founded = 0;
				vars->str = ft_strdup(cmd->garb, str);
				head->str = ft_replace(vars, cmd, head);
				str = head->str;
			}
			continue ;
		}
		i++;
	}
	return (0);
}

t_lexer	*ft_last_not_space(t_lexer *first, t_lexer *lexer)
{
	t_lexer	*head;
	t_lexer	*last_not_space;

	if (!first || first == lexer)
		return (NULL);
	head = first;
	last_not_space = NULL;
	while (head && head != lexer)
	{
		if (head->type != WHITE_SPACE)
			last_not_space = head;
		head = head->next;
	}
	return (last_not_space);
}

int	ft_check_dollar(t_lexer *head)
{
	char	*str;
	int		i;

	i = 0;
	if (!head || !head->str)
		return (1);
	str = head->str;
	while (str && str[i])
	{
		if (str[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

int	ft_expand(t_cmd *cmd)
{
	t_lexer	*head;
	t_lexer	*last;
	t_vars	*vars;
	int		j;

	vars = ft_malloc(cmd->garb, sizeof(t_vars));
	j = 0;
	head = cmd->lexer;
	last = head;
	while (head)
	{
		if (head && head->type == STR && last && last->type != HEREDOC)
		{
			if (head->q_flag != 2 && !ft_check_dollar(head))
				ft_get_var(cmd, head, head->str, vars);
		}
		head = head->next;
		last = ft_last_not_space(cmd->lexer, head);
		j++;
	}
	return (0);
}
