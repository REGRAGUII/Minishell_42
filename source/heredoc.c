/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:35:07 by yregragu          #+#    #+#             */
/*   Updated: 2024/11/28 13:28:39 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

char	*half_replace_doc(char *res, int skip, t_cmd *cmd, char *str)
{
	t_env	*env;

	env = cmd->env_new;
	while (env)
	{
		if (ft_endof_expand(str + skip + 1) == ft_strlen(env->key))
		{
			if (!ft_strncmp(str + skip + 1, env->key, ft_strlen(env->key)))
			{
				res = ft_strjoin(cmd->garb, res, env->value);
				break ;
			}
		}
		env = env->next;
	}
	return (res);
}

char	*ft_replace_doc(char *str, int skip, t_cmd *cmd)
{
	char	*res;

	res = ft_strndup(cmd->garb, str, skip);
	if (str[skip + 1] && str[skip + 1] == '?')
	{
		res = ft_strjoin(cmd->garb, res, ft_itoa(cmd, g_main.exit_s));
		skip++;
		if (!str[skip + 1])
			return (res);
	}
	res = half_replace_doc(res, skip, cmd, str);
	if (str[ft_endof_expand(str + skip +1) + 1])
		res = ft_strjoin(cmd->garb, res,
				str + skip + ft_endof_expand(str + skip + 1) + 1);
	return (res);
}

int	there_is_dollar(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_expand_dor(t_cmd *cmd, char *res)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup(cmd->garb, res);
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			if ((str[i + 1] && str[i + 1] == '$')
				|| (str[i] == '$' && !str[i + 1]))
				i++;
			else if (there_is_dollar(str + i))
			{
				str = ft_replace_doc(str, i, cmd);
			}
			continue ;
		}
		i++;
	}
	return (str);
}

int	herdoc(t_cmd *cmd, t_lexer *lexer)
{
	t_lexer	*head;
	char	*filename;

	filename = generate(cmd);
	head = lexer;
	if (head->next)
	{
		return (open_tmp(cmd, head, filename));
	}
	return (0);
}
