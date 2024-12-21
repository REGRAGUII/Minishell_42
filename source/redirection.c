/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:35:26 by yregragu          #+#    #+#             */
/*   Updated: 2024/11/27 23:42:27 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

int	redir_in(t_lexer *head)
{
	t_lexer	*les;
	int		fd;
	char	*file;

	les = head;
	while (les)
	{
		if (les->type == REDIR_IN && ft_ckeck_in(les->next))
			return (1);
		if (les->type == REDIR_IN && les->next)
		{
			file = les->next->str;
			if (check_reds(file, les, &fd, 1))
				return (1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		les = les->next;
	}
	return (0);
}

int	redir_out(t_lexer *les)
{
	char	*file;
	int		fd;

	while (les)
	{
		if (les->type == REDIR_OUT && les->next)
		{
			file = les->next->str;
			if (check_reds(file, les, &fd, 2) == 1)
				return (1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (!les->next || !les->next->str || les->next->type == END_OF_LIST)
		{
			if (g_main.is_child == 1)
			{
				g_main.exit_s = 1;
				g_main.is_child = 0;
			}
		}
		les = les->next;
	}
	return (0);
}

int	redir_append(t_lexer *lex)
{
	char	*file;	
	int		fd;

	while (lex)
	{
		if (lex->type == APPEND && lex->next)
		{
			file = lex->next->str;
			if (check_reds(file, lex, &fd, 3))
				return (1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		lex = lex->next;
	}
	return (0);
}

int	is_redirection(t_cmd *cmd)
{
	t_lexer	*head;

	head = cmd->lexer;
	fix_err(cmd);
	while (head)
	{
		if (head->type == REDIR_IN && redir_in(cmd->lexer))
			return (1);
		if (head->type == REDIR_OUT && redir_out(cmd->lexer))
			return (1);
		else if (head->type == APPEND && redir_append(cmd->lexer))
			return (1);
		head = head->next;
	}
	return (0);
}
