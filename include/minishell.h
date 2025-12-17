/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:17:15 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/20 13:17:15 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _POSIX_C_SOURCE
# define _POSIX_C_SOURCE 200809L
#endif
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include <ctype.h>
# include <sys/wait.h>
# include <limits.h>
# include "../libft/libft.h"


/*=============================*/
/*         ENUMS               */
/*=============================*/

typedef enum e_token_type
{
	WORD,
	STRING_DQUOTE,
	STRING_SQUOTE,
	PIPE,
	INPUT,
	TRUNC,
	APPEND,
	HEREDOC,
	END
}	t_token_type;


/*=============================*/
/*         STRUCTS             */
/*=============================*/

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_io
{
	char	*infile;
	char	*outfile;
	bool	append;
	bool	heredoc;
	bool    heredoc_expand;
	char	*heredoc_delimiter;
}	t_io;

typedef struct s_command
{
	char				*command;
	char				**args;
	t_io				io;
	int					exit_status;
	bool				pipe_output;
	struct s_command	*next;
	struct s_command	*prev;
}	t_cmd;

typedef struct s_data
{
	char		*user_input;
	t_token		*token;
	t_cmd		*cmd;
	char		**envp;
	int			last_exit_status;
}	t_data;

typedef struct s_prog
{
	int	exit_status;
	int	heredoc_interrupted;
}	t_prog;

t_prog	*prog_data(void);

/*=============================*/
/*            FILES            */
/*=============================*/

/* debug */
void	execute_commands(t_cmd *cmd, t_data *data);
void	print_tokens(t_token *list);
void	print_commands(t_cmd *cmd);

/* lexer */
bool	lexer(t_data *data);
int		is_redirect(char c);
int		extract_word(t_token **tokens, const char *input, int start);
int		handle_redirects(t_token **tokens, const char *input, int i);
int		skip_spaces(const char *str, int i);
void	add_token(t_token **tokens, const char *value, t_token_type type);
void	free_tokens(t_token *list);
bool	has_syntax_error(t_token *list);
int		handle_quote_case(t_token **tokens, const char *input, int i);

/* expander */
void	expand_tokens(t_token *tokens, t_data *data);
char	*append_char(char *s, char c);
char	*expand_dollar_only(const char *str,char **envp,int last_exit_status);

/* parser */
t_cmd	*parser(t_token *tokens);
void	parse_word(t_cmd *cmd, t_token **tk);
t_cmd	*parse_pipe(t_cmd *cmd, t_token **tk);
void	parse_redirect(t_cmd *cmd, t_token **tk);
void	free_commands(t_cmd *cmd);
void	init_cmd(t_cmd *cmd);
void	free_str_tab(char **tab);
char	*ft_strjoin_free(char *s1, const char *s2);

/* utils */
int		ft_is_space(char c);
void	errmsg(const char *msg, const char *arg, bool newline);
void	cleanup_iteration(t_data *data);
void 	free_all(t_data *data);
void	free_environment(char **env);

/* built ins */
int		is_builtin(char *cmd);
int		exec_builtin(char **argv, char ***env, bool from_shell);
int		builtin_echo(char **argv);
int		builtin_cd(char **argv, char **env);
int		builtin_pwd(void);
int		builtin_export(char **argv, char ***env);
int		builtin_env(char **env);
int     builtin_exit(char **argv, bool from_shell);
int		echo_nnn_handler(char *str);
int		builtin_unset(char **argv, char ***env);
char	**expand_env(char **env, int *count);
int		update_or_add_var(char ***env, char *var, int *count);

/* Environment Util*/
char	*get_env_value(char **env, char *key);
char	**dup_env(char **envp);

/* Executing */
char	*resolve_path(char *cmd, char **envp);
int		apply_redirections(t_cmd *cmd, char **envp, int last_exit_status);
void	free_args(char **args);
void	close_pipes(int *pipefd);
int		create_pipe(int *pipefd);
void	execute_commands_piped(t_cmd *cmd, t_data *data);
void	execute_child(t_cmd *cmd, int in_fd, int out_fd, t_data *data);

/* Piping Utils  */
int	count_cmds(t_cmd *cmd);
t_cmd **collect_cmds(t_cmd *cmd, int n);
void	close_all_pipes(int *pipes, int n);
void	kill_children(pid_t *pids, int count);

/* signals */
void    setup_signals_interactive(void);
void    setup_signals_child(void);
void    setup_signals_heredoc(void);
void	setup_signals_parent_exec(void);

/* heredoc */
char 	*gen_heredoc_filename(void);
char 	*read_heredoc(char *delimiter, bool expand, char **envp, int last_exit_status);
bool 	heredoc_should_stop(char *line, char *delimiter);
void	write_heredoc_line(int fd, char *line, char **envp, bool expand, int last);



#endif
