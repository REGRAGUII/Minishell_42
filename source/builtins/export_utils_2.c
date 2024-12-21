/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:32:16 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/27 23:42:14 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	check_is_exist(t_cmd *cmd, t_env *head, t_env *new)
{
	t_env	*index;

	index = head;
	while (index)
	{
		if (ft_strlen(index->key) == ft_strlen(new->key)
			&& !ft_strncmp(index->key, new->key, ft_strlen(index->key)))
		{
			if (!index->value)
			{
				index->value = ft_strdup(cmd->garb, new->value);
				return (2);
			}
			else if (!new->value)
				return (1);
			else
			{
				index->value = ft_strdup(cmd->garb, new->value);
				return (2);
			}
		}
		index = index->next;
	}
	return (0);
}

char	*add_value(t_cmd *cmd, char *key, char *value)
{
	t_env	*env;

	env = cmd->env_new;
	while (env)
	{
		if (ft_strlen(env->key) == ft_strlen(key))
		{
			if (!ft_strncmp(env->key, key, ft_strlen(env->key)))
			{
				if (!env->value)
					return (ft_strdup(cmd->garb, value));
				else
					return (ft_strjoin(cmd->garb, env->value, value));
			}
		}
		env = env->next;
	}
	return (ft_strdup(cmd->garb, value));
}

int	export_check(char *str)
{
	if (check_export_param(str) == 1)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_main.exit_s = 1;
		return (1);
	}
	else if (check_export_param(str) == 2)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": invalid option\n", 2);
		g_main.exit_s = 2;
		return (2);
	}
	return (0);
}

int	check_export_half(char *str, int *i)
{
	if (!str || !str[0])
		return (1);
	while (str[*i] && ft_isspace(str[*i]))
		i += 1;
	if (!ft_isalpha(str[*i]) && str[*i] != '_' && !ft_isspace(str[*i]))
	{
		if (str[*i] == '-')
			return (2);
		if (str[*i] == '+' && str[*i + 1] && str[*i + 1] == '=')
			;
		else
			return (1);
	}
	*i += 1;
	return (0);
}
