/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:18:14 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/28 13:46:16 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key && ft_strlen(tmp->key) == 1
			&& !ft_strncmp("_", tmp->key, 1));
		else
		{
			if (tmp->key)
			{
				printf("declare -x ");
				printf("%s", tmp->key);
			}
			if (tmp->value)
				printf("=\"%s\"", tmp->value);
			printf("\n");
		}
		tmp = tmp->next;
	}
}

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
		{
			if (str[i - 1] == '+')
				return (-i);
			return (i);
		}
		i++;
	}
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '=' || c == '_' || c == '\t')
	{
		return (1);
	}
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	check_export_param(char *str)
{
	int	i;

	i = 0;
	if (check_export_half(str, &i))
	{
		i = 0;
		return (check_export_half(str, &i));
	}
	while (str && str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_'
			&& !ft_isspace(str[i]) && !ft_isnum(str[i]))
		{
			if (str[i] == '=')
				break ;
			if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
				;
			else
				return (1);
		}
		i++;
	}
	return (0);
}
