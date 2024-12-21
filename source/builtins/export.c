/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:14:41 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/28 14:14:41 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

char	*get_key(int index, char *str, t_cmd *cmd)
{
	char	*key;

	index = check_equal(str);
	if (index > 0)
		key = ft_strndup(cmd->garb, str, index);
	else if (index == 0)
		key = ft_strdup(cmd->garb, str);
	else if (index < 0)
	{
		index *= -1;
		key = ft_strndup(cmd->garb, str, index - 1);
	}
	return (key);
}

char	*get_value(int index, char *str, t_cmd *cmd, char *key)
{
	char	*value;

	index = check_equal(str);
	if (index > 0)
	{
		value = ft_strdup(cmd->garb, str + index + 1);
	}
	else if (index == 0)
	{
		value = NULL;
	}
	else if (index < 0)
	{
		index *= -1;
		value = add_value(cmd, key, str + index + 1);
	}
	return (value);
}

int	export_add_var(t_cmd *cmd, t_env *env, char *str)
{
	t_env	*new;
	t_env	*tmp;
	char	*key;
	char	*value;
	int		index;

	tmp = env;
	index = check_equal(str);
	key = get_key(index, str, cmd);
	value = get_value(index, str, cmd, key);
	new = ft_lstnew_env(cmd, key, value);
	index = check_is_exist(cmd, tmp, new);
	if (index)
		return (0);
	else
		ft_lstadd_back(tmp, new, cmd);
	return (0);
}

char	*get_second_arg(t_lexer *lexer)
{
	t_lexer	*head;

	head = lexer;
	if (head && head->next)
		head = head->next;
	while (head)
	{
		if (head->type == STR)
			return (head->str);
		else if (head->type != WHITE_SPACE)
			return (NULL);
		head = head->next;
	}
	return (NULL);
}

int	export(t_cmd	*cmd)
{
	int		flag;
	t_lexer	*head;
	int		ret;

	flag = 0;
	flag = check_expand_args(cmd);
	if (flag == 0)
		print_export(cmd->env_new);
	if (flag == 1)
	{
		head = cmd->lexer->next;
		while (head && head->type == STR)
		{
			ret = export_check(head->str);
			if (!ret)
				export_add_var(cmd, cmd->env_new, head->str);
			else
				return (ret);
			head = head->next;
		}
	}
	return (0);
}
