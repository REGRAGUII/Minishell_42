/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:12:04 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/27 23:12:09 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parce.h"

int	ft_error(int id)
{
	if (id == -1)
		ft_putstr_fd(" syntax error near unexpected token `newline'\n", 2);
	if (id == PIP)
		ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
	if (id == APPEND)
		ft_putstr_fd(" syntax error near unexpected token `>>'\n", 2);
	if (id == REDIR_IN)
		ft_putstr_fd(" syntax error near unexpected token `<'\n", 2);
	if (id == REDIR_OUT)
		ft_putstr_fd(" syntax error near unexpected token `>'\n", 2);
	if (id == HEREDOC)
		ft_putstr_fd(" syntax error near unexpected token `<<'\n", 2);
	if (id == 9)
		ft_putstr_fd(" syntax error near unexpected token `\"'\n", 2);
	if (id == 10)
		ft_putstr_fd(" syntax error near unexpected token `;'\n", 2);
	if (id == 11)
		ft_putstr_fd(" syntax error near unexpected token `''\n", 2);
	if (id == 12)
		ft_putstr_fd(" syntax error near unexpected token ` \" \n", 2);
	g_main.exit_s = 2;
	return (127);
}
