/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:58:14 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/27 22:48:11 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parce.h"

void	merge_lexer(t_cmd *cmd, t_lexer *lexer, t_lexer *next, char **str)
{
	int		words;
	int		i;
	t_lexer	*new;
	t_lexer	*tmp;

	i = 1;
	words = ft_count_words(str);
	new = ft_lstnew_lexer(cmd);
	lexer->str = str[0];
	lexer->next = new;
	while (i < words)
	{
		new->str = str[i];
		new->type = STR;
		tmp = ft_lstnew_lexer(cmd);
		new->next = tmp;
		new = new->next;
		if (i + 2 == words)
			new->next = next;
		i++;
	}
}

int	has_dollar(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
