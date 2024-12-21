/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:49:56 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/28 14:57:51 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parce.h"

char	**new_env(t_cmd *cmd)
{
	char	**res;
	char	cwd[1024];

	res = (char **)ft_malloc(cmd->garb, 4 * sizeof(char *));
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		res[0] = ft_strdup(cmd->garb,
				ft_strjoin(cmd->garb, ft_strdup(cmd->garb, "PWD="), cwd));
	}
	else
		return (NULL);
	res[1] = ft_strdup(cmd->garb, "SHLVL=1");
	res[2] = ft_strdup(cmd->garb, "_=/usr/bin/env");
	res[3] = NULL;
	return (res);
}

t_env	*fill_env_list(t_cmd *cmd, char **env)
{
	int		i;
	t_env	*new;
	t_env	*tmp;

	new = cmd->env_new;
	if (!env || ! env[0])
		env = new_env(cmd);
	i = 0;
	new = ft_lstnew_env(cmd, ft_strndup(cmd->garb, env[i],
				ft_strlen_char(env[i], '=')),
			ft_strdup(cmd->garb, env[i] + ft_strlen_char(env[i], '=')));
	while (env && env[i] && env[i][0])
	{
		if (i == 1)
			tmp = new;
		ft_lstadd_back(new, ft_lstnew_env(cmd, ft_strndup(cmd->garb, env[i],
					ft_strlen_char(env[i], '=') - 1),
				ft_strdup(cmd->garb, env[i] + ft_strlen_char(env[i], '='))),
			cmd);
		new = new->next;
		i++;
	}
	return (tmp);
}

void	ft_lstadd_back(t_env *lst, t_env *new, t_cmd *cmd)
{
	t_env	*head;

	head = lst;
	if (!head)
	{
		cmd->env_new = new;
		lst = new;
		return ;
	}
	while (head)
	{
		if (head->next)
			head = head->next;
		else
		{
			head->next = new;
			return ;
		}
	}
}

t_cmd	*ft_lstnew_cmd(t_cmd *cmd)
{
	t_cmd	*head;

	head = (t_cmd *)ft_malloc(cmd->garb, sizeof(t_cmd));
	if (!head)
		return (NULL);
	head->lexer = NULL;
	head->garb = cmd->garb;
	head ->env_new = cmd->env_new;
	head->line = cmd->line;
	head->next = NULL;
	head->main = cmd;
	return (head);
}

t_env	*ft_lstnew_env(t_cmd *cmd, char *key, char *value)
{
	t_env	*head;

	head = (t_env *)ft_malloc(cmd->garb, sizeof(t_env));
	if (!head)
		return (NULL);
	head->key = key;
	head->value = value;
	head->next = NULL;
	return (head);
}
