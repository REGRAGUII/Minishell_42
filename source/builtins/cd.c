/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:33:58 by yregragu          #+#    #+#             */
/*   Updated: 2024/11/30 14:41:08 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	cd(t_cmd *cmd)
{
	char	*home;
	char	cwd[1024];

	if (cmd->lexer && cmd->lexer->next && cmd->lexer->next->next
		&& cmd->lexer->next->next->type != 7)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (!cmd->lexer->next || !cmd->lexer->next->str)
	{
		home = getenv("HOME");
		ft_change_env(cmd, "OLDPWD", getcwd(cwd, sizeof(cwd)));
		if (!home)
			return (perror("Path environment not found"), 127);
		if (chdir(home) == -1)
			return (perror("chdir error"), 127);
		ft_change_env(cmd, "PWD", home);
	}
	else
	{
		ft_change_env(cmd, "OLDPWD", getcwd(cwd, sizeof(cwd)));
		if (cmd->lexer->next->str && chdir(cmd->lexer->next->str) == -1)
			return (perror("cd argument error"), 127);
		ft_change_env(cmd, "PWD", getcwd(cwd, sizeof(cwd)));
	}
	return (0);
}
