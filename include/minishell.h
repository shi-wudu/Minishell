/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:17:15 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/23 23:32:38 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*#ifndef	_POSIX_C_SOURCE
# define _POSIX_C_SOURCE 200809L
#endif */

# include "../libft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

/*=============================*/
/*         ENUMS               */
/*=============================*/

typedef enum e_token_type
{
	WORD,
	PIPE,
	INPUT,
	TRUNC,
	APPEND,
	HEREDOC,
	END
}								t_token_type;

typedef enum e_seg_type
{
	UNQUOTED,
	SINGLE_QUOTED,
	DOUBLE_QUOTED
}								t_seg_type;

/*=============================*/
/*         STRUCTS             */
/*=============================*/

typedef struct s_segment
{
	char						*value;
	t_seg_type					type;
	struct s_segment			*next;
}								t_segment;

typedef struct s_token
{
	t_token_type				type;
	t_segment					*segments;
	char						**expanded;
	struct s_token				*prev;
	struct s_token				*next;
}								t_token;

typedef struct s_io
{
	char						*infile;
	char						*outfile;
	bool						append;
	bool						heredoc_expand;
	bool						infile_is_heredoc;
}								t_io;

typedef struct s_command
{
	char						*command;
	char						**args;
	t_io						io;
	int							exit_status;
	bool						pipe_output;
	char						**heredoc_delimiters;
	int							heredoc_count;
	struct s_command			*next;
	struct s_command			*prev;
}								t_cmd;

typedef struct s_data			t_data;

typedef struct s_pipe_ctx
{
	t_cmd						**cmds;
	int							*pipes;
	pid_t						*pids;
	int							n;
	t_data						*data;
}								t_pipe_ctx;

typedef struct s_expand_ctx
{
	t_data						*data;
	t_seg_type					prev;
	char						**current;
	char						***result;
}								t_expand_ctx;

typedef struct s_data
{
	char						*user_input;
	t_token						*token;
	t_cmd						*cmd;
	char						**envp;
	int							last_exit_status;
	bool						parse_error;
	t_pipe_ctx					*pipe_ctx;
	bool						is_child;
	bool						in_heredoc;
}								t_data;

/*=============================*/
/*            FILES            */
/*=============================*/

/* global variable */
extern volatile sig_atomic_t	g_signal;

/* lexer */
bool							lexer(t_data *data);
int								ft_is_quote(char c);
void							ft_skip_spaces(char **line);
void							ft_print_quote_err(char c);
bool							is_word_char(char c);
t_token							*ft_new_token(t_token_type type);
void							ft_token_list_add_back(t_token **lst,
									t_token *new);
void							ft_clear_token_list(t_token **lst);
int								ft_handle_separator(char **line,
									t_token **tokens);
int								ft_append_identifier(char **line,
									t_token **tokens);
t_segment						*new_segment(char *value, t_seg_type type);
void							segment_add_back(t_segment **lst,
									t_segment *new);
void							free_segments(t_segment *seg);
int								parse_segment(char *s, size_t *i,
									t_segment **segs);

/* expander */
void							expand_tokens(t_token *tokens, t_data *data);
void							expand_env_var(const char *s, char **res,
									int *i, t_data *data);
char							*expand_vars(const char *s, t_data *data);
char							*append_char(char *s, char c);
void							handle_unquoted(char *expanded, char ***result,
									char **current, t_seg_type prev);
char							*expand_heredoc_line(const char *s,
									t_data *data);

/* parser */
t_cmd							*parser(t_token *tokens, t_data *data);
void							init_cmd(t_cmd *cmd);
void							free_args(char **args);
void							free_commands(t_cmd *cmd);
char							*ft_strjoin_free(char *s1, const char *s2);
char							**append_str_array(char **old, char *value);
bool							parse_redirect_token(t_cmd *cmd, t_token **tk,
									t_data *data);
t_cmd							*new_cmd(t_cmd **head, t_cmd *prev);
bool							handle_word_pipe(t_cmd **cmd, t_cmd **head,
									t_token **tk);
bool							add_expanded_args(t_cmd *cmd, char **expanded);

/* utils */
int								ft_is_space(char c);
void							cleanup_iteration(t_data *data);
void							free_all(t_data *data);
void							free_environment(char **env);
bool							check_syntax(t_token *tokens);
void							syntax_error(char *token);

/* built ins */
int								is_builtin(char *cmd);
int								exec_builtin(char **argv, char ***env,
									bool from_shell);
int								builtin_echo(char **argv);
int								builtin_cd(char **argv, char ***env);
int								builtin_pwd(void);
int								builtin_export(char **argv, char ***env);
int								builtin_env(char **env);
int								builtin_exit(char **argv, bool from_shell);
int								echo_nnn_handler(char *str);
int								builtin_unset(char **argv, char ***env);

/* Environment Util*/
char							*get_env_value(char **env, char *key);
char							**dup_env(char **envp);
int								update_or_add_var(char ***env, char *var,
									int *count);
char							**expand_env(char **env, int *count);
int								env_count(char **env);
void							update_pwd_vars(char ***env, const char *oldpwd,
									const char *newpwd);

/* Executing */
int								execute_commands(t_cmd *cmd, t_data *data);
char							*resolve_path(char *cmd, char **envp);
int								apply_redirections(t_cmd *cmd);
void							free_args(char **args);
void							execute_commands_piped(t_cmd *cmd,
									t_data *data);
void							execute_child(t_cmd *cmd, int in_fd, int out_fd,
									t_data *data);
void							execute_main(t_cmd *cmd, t_data *data);
pid_t							spawn_pipeline_child(t_pipe_ctx *ctx, int idx);
void							cleanup_and_exit_child(t_data *data,
									int status);

/* Piping Utils  */
int								count_cmds(t_cmd *cmd);
t_cmd							**collect_cmds(t_cmd *cmd, int n);
void							close_all_pipes(int *pipes, int n);
void							kill_children(pid_t *pids, int count);
void							ensure_standard_fds_open(void);
void							pipeline_cleanup_and_wait(t_pipe_ctx *ctx,
									int spawned);
void							wait_and_collect(t_pipe_ctx *ctx, int count);

/* signals */
void							setup_signals_interactive(void);
void							setup_signals_child(void);
void							setup_signals_heredoc(void);
void							setup_signals_parent_exec(void);

/* heredoc */
char							*gen_heredoc_filename(void);
char							*read_heredoc(char *delimiter, bool expand,
									t_data *data);
bool							heredoc_should_stop(char *line,
									char *delimiter);
void							write_heredoc_line(int fd, char *line,
									t_data *data, bool expand);
int								prepare_heredocs(t_cmd *cmd, t_data *data);
char							*resolve_heredocs(t_cmd *cmd, t_data *data);

#endif
