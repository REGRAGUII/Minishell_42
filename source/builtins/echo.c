/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:33:53 by yregragu          #+#    #+#             */
/*   Updated: 2024/11/29 14:25:46 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	flag_checker(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	is_flag(char *str)
{
	if (str && ft_strlen(str) > 1
		&& !ft_strncmp("-n", str, 2) && flag_checker(str))
		return (1);
	return (0);
}

int	ft_flag(t_lexer *lexer)
{
	int	flag;

	flag = 0;
	while (lexer && ft_strlen(lexer->str) > 1
		&& !ft_strncmp("-n", lexer->str, 2) && flag_checker(lexer->str))
	{
		flag = 1;
		lexer = lexer->next;
	}
	return (flag);
}

char	**skip_flag(char **args, t_cmd *cmd)
{
	char	**res;
	int		i;
	int		j;

	j = 0;
	i = 1;
	if (!args[1])
		return (args);
	while (args && args[i] && is_flag(args[i]))
		i++;
	while (args && args[j])
		j++;
	res = ft_malloc(cmd->garb, sizeof(char *) * (j - i + 2));
	j = 1;
	res[0] = ft_strdup(cmd->garb, args[0]);
	while (args && args[i])
	{
		res[j] = ft_strdup(cmd->garb, args[i]);
		i++;
		j++;
	}
	res[j] = NULL;
	return (res);
}

int	echo(t_cmd *cmd)
{
	t_lexer	*head;
	int		flag;
	int		i;
	char	**args;	

	args = ft_get_args(cmd);
	args = skip_flag(args, cmd);
	head = cmd->lexer->next;
	flag = ft_flag(head);
	i = 1;
	while (args && args[i])
	{
		printf("%s", args[i]);
		if (args[i] && args[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	head = cmd->lexer;
	return (0);
}
