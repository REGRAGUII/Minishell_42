/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:21:04 by yregragu          #+#    #+#             */
/*   Updated: 2024/12/20 23:51:50 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"


int	check_path(char *str)
{
	if (!str)
		return (1);
	if ((ft_strlen(str) > 2 && !ft_strncmp("./", str, 2))
		|| (ft_strlen(str) > 3 && (!ft_strncmp("../", str, 3))))
		return (1);
	if (ft_strlen(str) > 1 && !ft_strncmp("/", str, 1))
		return (1);
	return (0);
}

int	perms_check(char *str)
{
	if (!str)
		return (0);
	if (!access(str, F_OK) && access(str, X_OK) == -1)
		return (1);
	return (0);
}

void	run_it02_helper(t_cmd *cmd, char **args, char *command, char **env)
{
	if (cmd->lexer->fd_in > 0)
	{
		dup2(cmd->lexer->fd_in, 0);
		close(cmd->lexer->fd_in);
	}
	if (command || check_path(args[0]))
	{
		if (execve(command, args, env) == -1)
			(ft_putstr_fd(args[0], 2),
				ft_putstr_fd(": command not found\n", 2), exit(127));
	}
	if (!command)
	{
		if (cmd->lexer->fd_in > 0)
			(dup2(cmd->lexer->fd_in, STDIN_FILENO), close(cmd->lexer->fd_in));
		if (access(args[0], X_OK) != -1)
		{
			if (execve(args[0], args, env) == -1)
				(ft_putstr_fd(args[0], 2),
					ft_putstr_fd(": command not found\n", 2), exit(127));
		}
		else
			(ft_putstr_fd(args[0], 2), ft_putstr_fd(": command not found\n", 2),
				exit(127));
	}
}

void	run_it02(t_cmd *cmd, char **args, char *command, char **env)
{
	
	if (!chdir(command) && check_path(command))
	{
		printf("here : %s\n", command);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(" is a directory \n", 2);
		exit (126);
	}
	command = correct_path(cmd, command);
	if (command && check_path(args[0]))
	{
		if (perms_check(args[0]))
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(args[0], 2);
			(ft_putstr_fd(" : Permission denied\n", 2), exit (126));
		}
	}
	if (!command && check_path(args[0]))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		(ft_putstr_fd(": No such file or directory\n", 2), exit(127));
	}
	run_it02_helper(cmd, args, command, env);
}

void	run_it01(t_cmd *cmd)
{
	char	*command;
	char	**args;
	char	**env;

	command = cmd->lexer->str;
	args = ft_get_args(cmd);
	if (!args)
		return ;
	command = args[0];
	if (!args[0])
		exit (0);
	env = get_env(cmd);
	run_it02(cmd, args, command, env);
	exit(EXIT_SUCCESS);
}
