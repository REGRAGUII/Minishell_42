/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:35:35 by yregragu          #+#    #+#             */
/*   Updated: 2024/11/29 15:06:12 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

static void	handle_interrupt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_main.exit_s = 130;
}

static void	handle_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
	g_main.exit_s = 130;
	exit(130);
}

void	handle_signals(int sig)
{
	if (sig == IN_HEREDOC)
	{
		signal(SIGINT, handle_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == IN_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (sig == IN_PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == BEFORE_READLINE)
	{
		signal(SIGINT, handle_interrupt);
		signal(SIGQUIT, SIG_IGN);
	}
}
