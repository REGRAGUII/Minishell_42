/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:20:29 by yregragu          #+#    #+#             */
/*   Updated: 2024/11/27 18:20:47 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

int	last_node_isend(t_cmd *cmd)
{
	t_lexer	*head;

	head = cmd->lexer;
	while (head)
	{
		if (head->q_flag == 1)
			return (1);
		if (head->type == END_OF_LIST)
			return (1);
		head = head->next;
	}
	return (0);
}

void	get_args_while(t_lexer *head, char **arg)
{
	int	i;

	i = 0;
	while (head)
	{
		if (head->type == HEREDOC || head->type == REDIR_OUT
			|| head->type == REDIR_IN || head->type == APPEND)
		{
			head = head->next;
			if (head && (!head->next || head->next->type == 7))
			{
				head = NULL;
				break ;
			}
		}
		else if (head && head->type == STR)
		{
			arg[i] = head->str;
			i++;
		}
		else if (!head)
			break ;
		head = head->next;
	}
	arg[i] = NULL;
}

char	**ft_get_args(t_cmd *cmd)
{
	t_lexer	*head;
	char	**arg;
	int		i;

	i = 0;
	head = cmd->lexer;
	while (head)
	{
		i++;
		head = head->next;
	}
	arg = ft_malloc(cmd->garb, (sizeof(char *)) * (i + 1));
	head = cmd->lexer;
	get_args_while(head, arg);
	if (!arg[0] || (!arg[0][0] && !last_node_isend(cmd)))
		return (NULL);
	return (arg);
}

char	**get_env(t_cmd *cmd)
{
	char	**env;
	char	*join;
	t_env	*temp;
	t_env	*head;
	int		size;

	size = 0;
	temp = cmd->env_new;
	head = cmd->env_new;
	while (temp)
	{
		temp = temp->next;
		size++;
	}
	env = ft_malloc(cmd->garb, sizeof(char *) * (size + 1));
	size = 0;
	while (head)
	{
		join = ft_strjoin(cmd->garb, head->key, "=");
		join = ft_strjoin(cmd->garb, join, head->value);
		env[size++] = ft_strdup(cmd->garb, join);
		head = head->next;
	}
	env[size] = NULL;
	return (env);
}

char	*correct_path(t_cmd *cmd, char *command)
{
	char	*str;
	char	**path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_strdup(cmd->garb, command);
	if (check_path(str) && (access(str, F_OK) != -1))
		return (str);
	if (check_path(command) || get_path(cmd))
		return (NULL);
	path = cmd->path;
	while (path && path[i])
		i++;
	while (j <= i)
	{
		str = NULL;
		str = ft_strdup(cmd->garb, path[j]);
		str = ft_strjoin(cmd->garb, str, command);
		if (access(str, F_OK) != -1)
			return (str);
		j++;
	}
	return (NULL);
}
