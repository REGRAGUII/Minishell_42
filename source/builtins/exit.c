/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:34:08 by yregragu          #+#    #+#             */
/*   Updated: 2024/11/29 13:25:14 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	ft_atoi(const char *nptr)
{
	int	sg;
	int	rs;

	sg = 1;
	rs = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		sg = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr)
	{
		if (*nptr >= '0' && *nptr <= '9')
			rs = rs * 10 + *nptr - '0';
		else
			break ;
		nptr++;
	}
	return (sg * rs);
}

int	ft_isalpha0(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit_helper(t_cmd *cmd, t_cmd *main, t_garb *tmp0, int i)
{
	t_lexer	*tmp;

	tmp = cmd->lexer;
	if (ft_isalpha0(tmp->next->str))
	{
		ft_putstr_fd("exit : ", 2);
		ft_putstr_fd(tmp->next->str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_free(cmd);
		free(tmp0);
		(free(main), exit(2));
	}
	else if (i <= 255)
	{
		ft_free(cmd);
		free(tmp0);
		(free(main), exit(i));
	}
	else if (i > 255)
	{
		ft_free(cmd);
		free(tmp0);
		(free (main), exit(i % 256));
	}
}

void	ft_exit(t_cmd *cmd)
{
	t_lexer	*tmp;
	t_cmd	*main;
	t_garb	*tmp0;

	tmp0 = cmd->garb;
	main = cmd->main;
	tmp = cmd->lexer;
	if (tmp && tmp->next && tmp->next->next && tmp->next->next->type != 7)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_main.exit_s = 1;
		return ;
	}
	if (tmp->next)
		ft_exit_helper(cmd, main, tmp0, ft_atoi(tmp->next->str));
	else
	{
		ft_free(cmd);
		free(tmp0);
		free (main);
		exit(0);
	}
}
