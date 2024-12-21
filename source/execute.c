/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:34:39 by yregragu          #+#    #+#             */
/*   Updated: 2024/11/28 18:33:30 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	after_exit(t_cmd *cmd, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (cmd->lexer->fd_in > 0)
			close(cmd->lexer->fd_in);
		if (WTERMSIG(status) == SIGINT)
			g_main.exit_s = 130;
		else if (WTERMSIG(status) == SIGQUIT)
			g_main.exit_s = 131;
	}
	else if (WIFEXITED(status))
	{
		if (cmd->lexer->fd_in > 0)
			close(cmd->lexer->fd_in);
		g_main.exit_s = WEXITSTATUS(status);
	}
}

void	run_it_helper(t_cmd *cmd, char **args, int i, pid_t pid)
{
	char	*command;
	char	**env;

	env = get_env(cmd);
	command = args[0];
	if (i == IN_CHILD)
	{
		handle_signals(IN_CHILD);
		run_it02(cmd, args, command, env);
	}
	else if (i == IN_PARENT)
	{
		handle_signals(IN_PARENT);
		after_exit(cmd, pid);
	}
}

int	run_it(t_cmd *cmd)
{
	pid_t	pid;
	char	**args;

	args = ft_get_args(cmd);
	if (!args)
	{
		g_main.exit_s = 0;
		return (0);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		run_it_helper(cmd, args, IN_CHILD, pid);
	else
		run_it_helper(cmd, args, IN_PARENT, pid);
	return (0);
}

int	ft_heredoc(t_cmd *cmd)
{
	t_cmd	*it;
	t_lexer	*head;

	it = cmd;
	while (it)
	{
		head = it->lexer;
		while (head)
		{
			if (head->type == HEREDOC && herdoc(it, head))
				return (130);
			head = head->next;
		}
		it = it->next;
	}
	return (0);
}

int	exec(t_cmd *cmd)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (ft_heredoc(cmd))
		return (130);
	if (cmd->next)
		ft_pipe(cmd);
	else
	{
		if (is_redirection(cmd))
			return (std_backup(stdin_backup, stdout_backup));
		if (is_built_in(cmd))
			g_main.exit_s = run_buit_int(cmd,
					is_built_in(cmd), stdin_backup, stdout_backup);
		else
		{
			g_main.is_child = 1;
			run_it(cmd);
			g_main.is_child = 0;
		}
	}
	std_backup(stdin_backup, stdout_backup);
	return (g_main.exit_s);
}
