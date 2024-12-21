/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:14:12 by yregragu          #+#    #+#             */
/*   Updated: 2024/11/28 00:07:07 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

int	check_reds(char *file, t_lexer *les, int *fd, int type)
{
	if (!chdir(file))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file, 2);
		return (ft_putstr_fd(" is a directory \n", 2), 1);
	}
	if ((!les->next || !les->next->str
			|| !les->next->str[0]) && les->exp_err == 1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file, 2);
		return (ft_putstr_fd(" ambiguous redirect\n", 2), 1);
	}
	if (type == 1)
		*fd = open(file, O_RDONLY);
	else if (type == 2)
		*fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == 3)
		*fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		(ft_putstr_fd("minishell :", 2), perror(file));
		return (1);
	}
	return (0);
}

int	ft_ckeck_in(t_lexer *lexer)
{
	if (!lexer)
		return (1);
	if (!lexer->str || access(lexer->str, F_OK) == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		perror(lexer->str);
		return (1);
	}
	if (!lexer->str || access(lexer->str, R_OK) == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(lexer->str, 2);
		ft_putstr_fd(" : Permission denied\n", 2);
		return (1);
	}
	return (0);
}

int	ft_ckeck_out(t_lexer *lexer)
{
	if (!lexer)
		return (1);
	if (lexer->str && access(lexer->str, F_OK) == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(lexer->str, 2);
		perror(lexer->str);
		return (1);
	}
	if (lexer->str && access(lexer->str, W_OK) == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(lexer->str, 2);
		ft_putstr_fd(" : Permission denied\n", 2);
		return (1);
	}
	return (0);
}
