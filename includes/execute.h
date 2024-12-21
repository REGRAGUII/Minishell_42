/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:24:08 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/28 18:36:00 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include "parce.h"

int		echo(t_cmd *cmd);
int		pwd(void);
int		cd(t_cmd *cmd);
int		env(t_cmd *cmd);
int		unset(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);
int		exec(t_cmd *cmd);
void	ft_pipe(t_cmd *cmd);
void	parent_process(t_cmd *cmd);
void	ft_free(t_cmd *cmd);
int		run_it(t_cmd *cmd);
void	run_it01(t_cmd *cmd);
int		is_built_in(t_cmd *cmd);
int		run_buit_int(t_cmd *cmd, int i, int stdin_backup, int stdout_backup);
int		is_redirection(t_cmd *cmd);
char	**ft_get_args(t_cmd *cmd);
int		herdoc(t_cmd *cmd, t_lexer *lexer);
int		redir_in(t_lexer *les);
int		redir_out(t_lexer *les);
int		redir_append(t_lexer *lex);
t_env	*dup_env(t_env *env, t_cmd *cmd);
int		check_path(char *str);
void	handle_signals(int sig);
void	ft_pipe(t_cmd *cmd);
int		ft_ckeck_out(t_lexer *lexer);
int		ft_ckeck_in(t_lexer *lexer);
int		check_reds(char *file, t_lexer *les, int *fd, int type);
char	**get_env(t_cmd *cmd);
char	*correct_path(t_cmd *cmd, char *command);
void	run_it02(t_cmd *cmd, char **args, char *command, char **env);
int		check_export_param(char *str);
int		check_equal(char *str);
void	print_export(t_env *env);
int		check_is_exist(t_cmd *cmd, t_env *head, t_env *new);
char	*add_value(t_cmd *cmd, char *key, char *value);
int		export_check(char *str);
int		check_export_half(char *str, int *i);
void	open_tmp_helper(t_cmd *cmd, t_lexer *head, int *fd);
int		open_tmp(t_cmd *cmd, t_lexer *lexer, char *filename);
char	*ft_strcpy(char *s1, char *s2);
char	*generate(t_cmd *cmd);
char	*half_replace_doc(char *res, int skip, t_cmd *cmd, char *str);
char	*ft_replace_doc(char *str, int skip, t_cmd *cmd);
int		there_is_dollar(char *str);
char	*ft_expand_dor(t_cmd *cmd, char *res);
int		split_open(t_cmd *cmd, char *str, t_lexer *head, int *fd);
int		herdoc(t_cmd *cmd, t_lexer *lexer);
int		std_backup(int stdin_backup, int stdout_backup);
char	*ft_strcpy(char *s1, char *s2);
#endif
