/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:57:59 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/28 18:32:22 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	open_tmp_helper(t_cmd *cmd, t_lexer *head, int *fd)
{
	char	*str;
	char	*res;

	while (1)
	{
		handle_signals(IN_HEREDOC);
		str = readline("> ");
		split_open(cmd, str, head, fd);
		res = str;
		if (!head->doc_expand && !head->q_flag)
		{
			res = ft_expand_dor(cmd, str);
			ft_putstr_fd(res, *fd);
		}
		else
			ft_putstr_fd(str, *fd);
		ft_putstr_fd("\n", *fd);
		free(str);
		str = NULL;
		res = NULL;
	}
}

static	int	after_tmp(pid_t pid, char *filename, t_cmd *cmd, int *fd)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		close(*fd);
		g_main.exit_s = WEXITSTATUS(status);
		cmd->lexer->fd_in = open(filename, O_RDONLY);
		return (g_main.exit_s);
	}
	else
	{
		close(*fd);
		g_main.exit_s = 130;
		cmd->lexer->fd_in = -1;
		return (130);
	}
	return (0);
}

int	open_tmp(t_cmd *cmd, t_lexer *lexer, char *filename)
{
	int		fd;
	pid_t	pid;

	pid = fork();
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pid == 0)
		open_tmp_helper(cmd, lexer->next, &fd);
	else
	{
		return (after_tmp(pid, filename, cmd, &fd));
	}
	return (0);
}

char	*generate(t_cmd *cmd)
{
	char	*name;
	int		i;
	char	*prefix;
	char	*rm;

	i = 14;
	rm = ft_strdup(cmd->garb, "abcdEFghiFk2MNOPARSRuvwxyz0123456789");
	name = ft_malloc(cmd->garb, sizeof(char) * 30);
	prefix = "/tmp/.heredoc_";
	name = ft_strcpy(name, prefix);
	while (i < 25)
	{
		name[i] = rm[(unsigned long)&name[i] % 30];
		i++;
	}
	name[i] = '\0';
	return (name);
}

int	split_open(t_cmd *cmd, char *str, t_lexer *head, int *fd)
{
	if (!str)
	{
		printf("minishell: warning: here-document at line ");
		printf("%d", cmd->line);
		printf(" delimited by end-of-file (wanted `%s')\n", head->str);
		close(*fd);
		exit(0);
	}
	if (ft_strlen(str) == ft_strlen(head->str)
		&& !ft_strncmp(str, head->str, ft_strlen(str)))
	{
		free(str);
		close(*fd);
		exit(0);
	}
	return (0);
}
