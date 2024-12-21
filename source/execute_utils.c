/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:34:30 by yregragu          #+#    #+#             */
/*   Updated: 2024/11/28 15:22:59 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

int	half_built(t_cmd *cmd)
{
	if (ft_strlen(cmd->lexer->str) == 4
		&& !ft_strncmp("echo", cmd->lexer->str, 4))
		return (2);
	else if (ft_strlen(cmd->lexer->str) == 2
		&& !ft_strncmp("cd", cmd->lexer->str, 2))
		return (3);
	else if (ft_strlen(cmd->lexer->str) == 3
		&& !ft_strncmp("pwd", cmd->lexer->str, 3))
		return (4);
	return (0);
}

int	is_built_in(t_cmd *cmd)
{
	int	i;

	i = half_built(cmd);
	if (i)
		return (i);
	else if (ft_strlen(cmd->lexer->str) == 6
		&& !ft_strncmp("export", cmd->lexer->str, 6))
		return (5);
	else if (ft_strlen(cmd->lexer->str) == 5
		&& !ft_strncmp("unset", cmd->lexer->str, 5))
		return (6);
	else if (ft_strlen(cmd->lexer->str) == 3
		&& !ft_strncmp("env", cmd->lexer->str, 3))
		return (7);
	else if (ft_strlen(cmd->lexer->str) == 4
		&& !ft_strncmp("exit", cmd->lexer->str, 4))
		return (8);
	return (0);
}

int	run_half_built(t_cmd *cmd, int i)
{
	if (i == 2)
		return (echo(cmd));
	else if (i == 3)
		return (cd(cmd));
	else if (i == 4)
		return (pwd());
	return (127);
}

int	run_buit_int(t_cmd *cmd, int i, int stdin_backup, int stdout_backup)
{
	if (!run_half_built(cmd, i))
		return (0);
	if (i == 5)
		return (export(cmd));
	else if (i == 6)
		return (unset(cmd));
	else if (i == 7)
		return (env(cmd));
	else if (i == 8)
	{
		close(stdin_backup);
		close(stdout_backup);
		ft_exit(cmd);
	}
	return (1);
}
