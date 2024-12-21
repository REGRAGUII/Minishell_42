/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:34:47 by yregragu          #+#    #+#             */
/*   Updated: 2024/11/29 17:35:32 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	helper(t_cmd *cmd)
{
	int	i;
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	i = 0;
	if (is_redirection(cmd))
		exit(1);
	if (is_built_in(cmd))
	{
		i = is_built_in(cmd);
		run_buit_int(cmd, i, stdin_backup, stdout_backup);
		g_main.exit_s = 0;
		g_main.is_child = 0;
		exit (EXIT_SUCCESS);
	}
	else
	{
		run_it01(cmd);
		g_main.exit_s = 0;
		g_main.is_child = 0;
		exit(EXIT_SUCCESS);
	}
}

void	child(t_cmd *cmd, int *input_fd, int *fd)
{
	handle_signals(IN_CHILD);
 	if (*input_fd != STDIN_FILENO)
	{
		dup2(*input_fd, STDIN_FILENO);
		close(*input_fd);
	}
	if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	close(fd[0]);
	helper(cmd);
}

void	parent(t_cmd *cmd, pid_t pid, int *input_fd, int *fd)
{
	int	status;

	if (cmd && !cmd->next)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				g_main.exit_s = 130;
			else if (WTERMSIG(status) == SIGQUIT)
				g_main.exit_s = 131;
		}
		else if (WIFEXITED(status))
			g_main.exit_s = WEXITSTATUS(status);
	}
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (cmd->next)
		close(fd[1]);
	*input_fd = fd[0];
}

void	ft_pipe(t_cmd *cmd)
{
	pid_t	pid;
	int		fd[2];
	int		input_fd;

	input_fd = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
		{
			perror("pipe");
			g_main.is_child = 0;
			g_main.exit_s = 127;
		}
		pid = fork();
		if (pid == -1)
			(perror("fork"), g_main.is_child = 0);
		if (pid == 0)
			child(cmd, &input_fd, fd);
		else
			parent(cmd, pid, &input_fd, fd);
		cmd = cmd->next;
	}
	while (wait(NULL) >= 0)
		;
	g_main.is_child = 0;
}
