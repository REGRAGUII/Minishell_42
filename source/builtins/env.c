/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:33:32 by yregragu          #+#    #+#             */
/*   Updated: 2024/11/27 14:38:00 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	ft_change_env(t_cmd *cmd, char *key, char *value)
{
	t_env	*env;

	env = cmd->env_new;
	while (env)
	{
		if (ft_strlen(key) == ft_strlen(env->key))
			if (!ft_strncmp(key, env->key, ft_strlen(key)))
				env->value = ft_strdup(cmd->garb, value);
		env = env->next;
	}
}

int	is_env_command(char *str)
{
	return (ft_strlen(str) == 3 && !ft_strncmp("env", str, 3));
}

int	env(t_cmd *cmd)
{
	t_env	*en;
	t_lexer	*head;	

	en = cmd->env_new;
	head = cmd->lexer;
	while (head)
	{
		if (head->str && !is_env_command(head->str))
		{
			ft_putstr_fd("env : ", 2);
			ft_putstr_fd(head->str, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (127);
		}
		head = head->next;
	}
	while (en)
	{
		if (en->key && en->value && en->value[0])
			printf("%s=%s\n", en->key, en->value);
		en = en->next;
	}
	return (0);
}
