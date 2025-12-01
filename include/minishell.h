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

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
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

/*=============================*/
/*            FILES            */
/*=============================*/

/* debug */
void	execute_commands(t_cmd *cmds, char **envp);
void	print_tokens(t_token *list);
void	print_commands(t_cmd *cmd);

/* lexer */
t_token	*tokenize(const char *input);
int		is_redirect(char c);
int		extract_word(t_token **tokens, const char *input, int start);
int		extract_quoted(t_token **tokens, const char *input, int start);
int		handle_redirects(t_token **tokens, const char *input, int i);
int		skip_spaces(const char *str, int i);
void	add_token(t_token **tokens, const char *value, t_token_type type);
t_token	*new_token(const char *value, t_token_type type);
void	free_tokens(t_token *list);
bool	has_syntax_error(t_token *list);
int		handle_quote_case(t_token **tokens, const char *input, int i);

/* expander */
char	*join_and_expand_double(char *result, char *str, int *i, t_data *data);
char	*join_and_expand_dollar(char *result, char *str, int *i, t_data *data);
char	*expand_string(char *str, t_data *data);
void	expand_tokens(t_token *tokens, t_data *data);
char	*append_char(char *s, char c);
char	*join_and_skip(char *result, char *str, int *i, char quote);

/* parser */
bool	lexer(t_data *data);
t_cmd	*parser(t_token *tokens);
void	parse_word(t_cmd *cmd, t_token **tk);
t_cmd	*parse_pipe(t_cmd *cmd, t_token **tk);
void	parse_redirect(t_cmd *cmd, t_token **tk);
void	free_commands(t_cmd *cmd);
void	init_cmd(t_cmd *cmd);
void	free_str_tab(char **tab);
/* utils */
int		ft_is_space(char c);
void	errmsg(const char *msg, const char *arg, bool newline);

/* built ins */
int		is_builtin(char *cmd);
int		exec_builtin(char **argv, char ***env);
int		builtin_echo(char **argv);
int		builtin_cd(char **argv, char **env);
int		builtin_pwd(void);
int		builtin_export(char **argv, char ***env);
int		builtin_env(char **env);
int		builtin_exit(char **argv);
int		echo_nnn_handler(char *str);
int		builtin_unset(char **argv, char ***env);
char	**expand_env(char **env, int *count);
int		update_or_add_var(char ***env, char *var, int *count);

/* Environment Util*/
char	*get_env_value(char **env, char *key);

/* Executing */
char	*resolve_path(char *cmd, char **envp);
int		apply_redirections(t_cmd *cmd);
void	free_args(char **args);
void	close_pipes(int *pipefd);
void	close_all_fds(int *pipefd, int in_fd, int out_fd);
int		create_pipe(int *pipefd);

#endif
