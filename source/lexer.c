/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:23:07 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/27 18:13:15 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parce.h"

int	handle_space(t_cmd *cmd, int *i, t_lexer *lexer, t_lexer *last)
{
	if (ft_isspace(cmd->str[*i]))
	{
		lexer->str = ft_strdup(cmd->garb, " ");
		lexer->type = WHITE_SPACE;
		return (1);
	}
	else if (cmd->str[*i] == '"')
	{
		if (cmd->str[*i + 1] && cmd->str[*i + 1] == '"')
			last->doc_expand = 1;
		lexer->str = ft_str_dup_q(cmd->garb, cmd->str + *i, 0);
		lexer->q_flag = 1;
		*i += ft_new_index_qq(cmd->str + *i + 1);
		return (lexer->type = STR, 1);
	}
	else if (cmd->str[*i] == 39)
	{
		if (cmd->str[*i + 1] && cmd->str[*i +1] == 39)
			last->doc_expand = 1;
		lexer->str = ft_str_dup_q(cmd->garb, cmd->str + *i, 1);
		lexer->q_flag = 2;
		*i += ft_new_index_q(cmd->str + *i + 1);
		return (lexer->type = STR, 1);
	}
	return (0);
}

int	handle_reds(t_cmd *cmd, t_lexer *lexer, int	*i)
{
	if (cmd->str[*i] == '>' && cmd->str[*i + 1] && cmd->str[*i + 1] == '>')
	{
		lexer->str = ft_strdup(cmd->garb, ">>");
		*i += 1;
		lexer->type = APPEND;
		return (1);
	}
	else if (cmd->str[*i] == '<' && cmd->str[*i + 1] && cmd->str[*i + 1] == '<')
	{
		lexer->str = ft_strdup(cmd->garb, "<<");
		cmd->docs++;
		*i += 1;
		lexer->type = HEREDOC;
		return (1);
	}
	else if (cmd->str[*i] == '<')
	{
		lexer->str = ft_strdup(cmd->garb, "<");
		lexer->type = REDIR_IN;
		return (1);
	}
	return (0);
}

int	handle_str_pip(t_cmd *cmd, t_lexer *lexer, int *i)
{
	if (cmd->str[*i] == '>')
	{
		lexer->str = ft_strdup(cmd->garb, ">");
		lexer->type = REDIR_OUT;
		return (1);
	}
	else if (cmd->str[*i] == '|')
	{
		lexer->str = ft_strdup(cmd->garb, "|");
		lexer->type = PIP;
		return (1);
	}
	else
	{
		lexer->type = STR;
		lexer->str = ft_str_dup_space(cmd->garb, cmd->str + *i);
		*i += ft_new_index(cmd->str + *i);
		return (1);
	}
	return (0);
}

void	lexer_init(int *i, t_cmd *cmd)
{
	*i = 0;
	cmd->str = ft_strdup(cmd->garb, cmd->cmd);
	cmd->lexer = ft_lstnew_lexer(cmd);
	cmd->lexer->type = END_OF_LIST;
}

void	ft_lexer(t_lexer *lexer, t_cmd *cmd)
{
	int		i;
	t_lexer	*last;

	lexer_init(&i, cmd);
	lexer = cmd->lexer;
	last = lexer;
	while (cmd->str && cmd->str[i])
	{
		lexer->doc_expand = 0;
		lexer->q_flag = 0;
		if (handle_space(cmd, &i, lexer, last))
		{
			if (i >= ft_strlen(cmd->str))
				break ;
		}
		else if (handle_reds(cmd, lexer, &i))
			;
		else if (handle_str_pip(cmd, lexer, &i) && i >= ft_strlen(cmd->str))
			break ;
		lexer->next = ft_lstnew_lexer(cmd);
		last = lexer;
		lexer = lexer->next;
		lexer->type = END_OF_LIST;
		i++;
	}
}
