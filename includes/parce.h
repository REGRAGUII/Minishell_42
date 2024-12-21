/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 00:08:31 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/28 14:43:27 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCE_H
# define PARCE_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# define IN_HEREDOC 54
# define IN_CHILD 55
# define IN_PARENT 56
# define BEFORE_READLINE 57

typedef struct s_main
{
	int		is_child;
	int		exit_s;
	void	*garb;
}	t_main;

extern t_main	g_main;

typedef enum e_type
{
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	STR,
	WHITE_SPACE,
	PIP,
	END_OF_LIST
}	t_type;

typedef struct s_vars
{
	char	*res;
	char	*str;
	int		i;
	int		skip;
	int		founded;
}		t_vars;

typedef struct s_lexer
{
	char			*str;
	int				q_flag;
	int				fd_in;
	t_type			type;
	int				exp_err;
	int				doc_expand;
	struct s_lexer	*next;
}		t_lexer;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;

typedef struct s_garb
{
	void			*address;
	struct s_garb	*next;
}	t_garb;

typedef struct s_exec
{
	// char			**cmd;
	t_lexer			*cmd;
	struct s_exec	*next;
}	t_exec;

typedef struct s_cmd
{
	char			*cmd;
	char			*str;
	char			**env;
	char			**args;
	t_lexer			*lexer;
	t_env			*env_new;
	t_exec			*exec;
	t_garb			*garb;
	char			**path;
	int				docs;
	int				pid;
	int				line;
	int				exit_s;
	struct s_cmd	*main;
	struct s_cmd	*next;
}				t_cmd;
// libft / utils
// char	**ft_split(t_garb *garb, char const *s, char c);
char	**ft_split(t_garb *garb, char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strjoin(t_garb *garb, char *s1, char *s2);
char	*ft_strndup(t_garb *garb, char *s, int i);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_strcmp(char *s1, char *s2);
void	*ft_malloc(t_garb *garb, size_t size);
t_garb	*ft_garb_new(void *content);
void	ft_grab_back(t_garb *lst, t_garb *new);
void	ft_putstr_fd(char *s, int fd);
int		ft_isnum(char c);
int		ft_isspace(char c);
char	*ft_itoa(t_cmd *cmd, int n);
char	**ft_split_char(char *s, char c);
char	*ft_strncpy(char *dest, char *src, size_t n);
// dups
char	*ft_strdup(t_garb *garb, char *s);
char	*ft_str_dup_q(t_garb *garb, char *str, int id);
char	*ft_str_dup_char(t_garb *garb, char *str, char c);
char	*ft_str_dup_space(t_garb *garb, char *str);
//lens
int		ft_strlen_char(char *str, char c);
int		ft_strlen_expend(char *str);
int		ft_strlen_char_q(char *str, char c);
int		ft_strlen_space(char *str);
int		ft_strlen(char *str);

// parcing functions
t_cmd	*parce(char *str, t_cmd *cmd);
int		ft_error(int id);
int		ft_strlen_char(char *str, char c);
int		ft_expend_len(char *str, char c);
void	ft_lexer(t_lexer *lexer, t_cmd *cmd);
int		checker(t_cmd *cmd);
int		ft_expand(t_cmd *cmd);
void	join_str(t_cmd *cmd, t_lexer *lexer);
void	split_pip(t_cmd *cmd, t_cmd *new_cmd);
void	skip_space(t_cmd *cmd, t_lexer *lexer);
int		check_unclosed_quote(char *str);
// char	*ft_replace(char *str, int skip, t_cmd *cmd, t_lexer *head);
char	*ft_replace(t_vars *var, t_cmd *cmd, t_lexer *head);
int		ft_new_index(char *str);
int		herdoc_check(t_cmd *cmd);
int		ft_checker(t_cmd *cmd);
int		ft_is_reder(t_lexer *head);
int		ft_new_index_qq(char *str);
int		ft_new_index_q(char *str);
void	join_space(t_lexer *head, t_lexer *next);
void	join_node(t_cmd *cmd, t_lexer *head, t_lexer *next);
int		ft_endof_expand(char *str);
// export function
int		export(t_cmd	*cmd);
t_env	*ft_lstnew_env(t_cmd *cmd, char *key, char *value);
t_env	*fill_env_list(t_cmd *cmd, char **env);
int		check_expand_args(t_cmd *cmd);
// void	export_add_var(t_cmd *cmd, t_env *env, char *str);
void	ft_change_env(t_cmd *cmd, char *key, char *value);
//linkedlists
void	ft_lstadd_back(t_env *lst, t_env *new, t_cmd *cmd);
t_cmd	*ft_lstnew_cmd(t_cmd *cmd);
t_lexer	*ft_lstnew_lexer(t_cmd *cmd);
t_lexer	*ft_last_not_space(t_lexer *first, t_lexer *lexer);
int		get_path(t_cmd *cmd);
void	handle_signals(int sig);
void	fix_err(t_cmd *cmd);
int		export_add_var(t_cmd *cmd, t_env *env, char *str);
void	ft_free(t_cmd *cmd);
void	add_nodes(t_cmd *cmd);
int		ft_get_var(t_cmd *cmd, t_lexer *head, char *str, t_vars *vars);
char	*half_replace(t_cmd *cmd, t_lexer *head, t_vars *vars);
char	*handle_qoutes(t_env *env, t_cmd *cmd, t_vars *vars);
char	*handle_no_qoutes(t_env *env, t_cmd *cmd, t_vars *vars);
void	not_founded(t_cmd *cmd, t_lexer *head, t_vars *vars);
char	*remove_sign(t_cmd *cmd, char *str);
int		has_dollar(char *str);
void	merge_lexer(t_cmd *cmd, t_lexer *lexer, t_lexer *next, char **str);
int		ft_count_words(char **str);
int		half_cheker(t_cmd *cmd);

#endif