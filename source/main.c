/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:13:11 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/29 15:07:35 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

t_main	g_main = {0, 0, 0};

void	main_init(t_cmd *cmd, char **envp)
{
	cmd->garb = malloc(sizeof(t_garb));
	cmd->garb->next = NULL;
	cmd->env = envp;
	cmd->env_new = fill_env_list(cmd, cmd->env);
	cmd->line = 0;
	g_main.garb = cmd->garb;
}

void	free_main(t_cmd *cmd)
{
	t_garb	*save;

	save = cmd->garb;
	printf("exit\n");
	ft_free(cmd);
	free(save);
	free(cmd);
	exit(0);
}

void	ac_av(int ac, char **av)
{
	if (ac != 1)
		exit (0);
	(void)av;
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	t_cmd	*new;
	char	*promt;

	ac_av(ac, av);
	cmd = malloc(sizeof(t_cmd));
	main_init(cmd, envp);
	while (1)
	{
		handle_signals(BEFORE_READLINE);
		promt = readline("Minishell-> ");
		handle_signals(IN_PARENT);
		if (promt == NULL)
			free_main(cmd);
		add_history(promt);
		new = parce(promt, cmd);
		cmd->line++;
		if (new && new->lexer && new->lexer->type != END_OF_LIST)
		{
			g_main.exit_s = exec(new);
			cmd->env_new = new->env_new;
		}
		free(promt);
		promt = NULL;
	}
}
