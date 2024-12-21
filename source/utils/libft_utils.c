/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:48:52 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/27 22:49:31 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parce.h"

char	*ft_strndup(t_garb *garb, char *s, int i)
{
	char	*str;
	int		index;

	index = 0;
	if (!s)
		return (NULL);
	str = (char *)ft_malloc(garb, i + 1);
	if (!str)
		return (NULL);
	while (index < i)
	{
		str[index] = s[index];
		index++;
	}
	str[index] = '\0';
	return (str);
}

void	ft_grab_back(t_garb *lst, t_garb *new)
{
	t_garb	*head;

	head = lst;
	if (!head)
	{
		lst = new;
		return ;
	}
	while (head)
	{
		if (head->next)
			head = head->next;
		else
		{
			head->next = new;
			return ;
		}
	}
}

t_garb	*ft_garb_new(void *content)
{
	t_garb	*head;

	head = (t_garb *)malloc(sizeof(t_garb));
	if (!head)
		return (NULL);
	head->address = content;
	head->next = NULL;
	return (head);
}

void	*ft_malloc(t_garb *garb, size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		return (NULL);
	ft_grab_back(garb, ft_garb_new(res));
	return (res);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
