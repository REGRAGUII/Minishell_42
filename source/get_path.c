/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:55:53 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/27 23:11:26 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

char	**ft_fill_path(t_cmd *cmd)
{
	char	**res;
	t_env	*env;

	env = cmd->env_new;
	while (env)
	{
		if (ft_strlen(env->key) == 4 && !ft_strncmp("PATH", env->key, 4))
		{
			if (!env->value)
				return (NULL);
			res = ft_split_char(env->value, ':');
			return (res);
		}
		env = env->next;
	}
	return (NULL);
}

int	get_path(t_cmd *cmd)
{
	char	**paths;
	int		i;

	i = 0;
	paths = ft_fill_path(cmd);
	if (!paths)
		return (1);
	while (paths && paths[i])
	{
		paths[i] = ft_strjoin(cmd->garb, paths[i], "/");
		i++;
	}
	paths[i] = NULL;
	cmd->path = paths;
	return (0);
}
