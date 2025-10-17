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
# include "../libft/libft.h"



/*=============================*/
/*         ENUMS               */
/*=============================*/

typedef enum e_token_type
{
	WORD,
	STRING,
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
	int		fd_in;
	int		fd_out;
	bool	append;
	bool	heredoc;
	char    *heredoc_delimiter;
}	t_io;

typedef struct s_command
{
	char				*command;
	char				**args;
	t_io				io;
	bool				pipe_output;
	struct s_command	*next;
	struct s_command	*prev;
}	t_cmd;

typedef struct s_data
{
	char		**env;
	char		*user_input;
	t_token		*token;
	t_cmd	*cmd;
}	t_data;

/*=============================*/
/*            FILES            */
/*=============================*/

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


/* parser */
bool	parse_user_input(t_data *data);
t_cmd	*parser(t_token *tokens);
void	parse_word(t_cmd *cmd, t_token **tk);
t_cmd	*parse_pipe(t_cmd *cmd, t_token **tk);
void	parse_redirect(t_cmd *cmd, t_token **tk);
t_cmd	*last_cmd(t_cmd *cmd);
void	free_commands(t_cmd *cmd);
void	init_cmd(t_cmd *cmd);


/* utils */
int		ft_is_space(char c);
void	errmsg(const char *msg, const char *arg, bool newline);
void	free_str_tab(char **tab);

#endif
