/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:57:28 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/27 22:23:06 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parce.h"

char	*remove_sign(t_cmd *cmd, char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = ft_malloc(cmd->garb, ft_strlen(str));
	while (str && str[i])
	{
		if (str[i] != '$')
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

void	not_founded(t_cmd *cmd, t_lexer *head, t_vars *vars)
{
	if (!vars->founded)
	{
		if (head == cmd->lexer)
		{
			if (cmd->lexer->next)
				cmd->lexer = cmd->lexer->next;
		}
		head->str = NULL;
		head->exp_err = 1;
	}
}

char	*handle_no_qoutes(t_env *env, t_cmd *cmd, t_vars *vars)
{
	if (ft_endof_expand(vars->str + vars->skip + 1) == ft_strlen(env->key))
	{
		if (!ft_strncmp(vars->str + vars->skip + 1,
				env->key, ft_strlen(env->key)))
		{
			if (has_dollar(env->value))
			{
				vars->res = ft_strjoin(cmd->garb, vars->res,
						remove_sign(cmd, env->value));
			}
			else
				vars->res = ft_strjoin(cmd->garb, vars->res, env->value);
			vars->founded = 1;
		}
	}
	return (vars->res);
}

char	*handle_qoutes(t_env *env, t_cmd *cmd, t_vars *vars)
{
	if (ft_endof_expand(vars->str + vars->skip + 1) == ft_strlen(env->key))
	{
		if (!ft_strncmp(vars->str + vars->skip + 1,
				env->key, ft_strlen(env->key)))
		{
			vars->res = ft_strjoin(cmd->garb, vars->res, env->value);
			vars->founded = 1;
		}
	}
	return (vars->res);
}

char	*half_replace(t_cmd *cmd, t_lexer *head, t_vars *vars)
{
	t_env	*env;

	env = cmd->env_new;
	while (env)
	{
		if (!head->q_flag)
			vars->res = handle_no_qoutes(env, cmd, vars);
		else if (head->q_flag == 1)
			vars->res = handle_qoutes(env, cmd, vars);
		env = env->next;
	}
	not_founded(cmd, head, vars);
	return (vars->res);
}
