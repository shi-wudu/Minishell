#include "../../include/minishell.h"

int	handle_redirects(t_token **tokens, const char *input, int i)
{
	if (input[i] == '>' && input[i + 1] == '>')
		return (add_token(tokens, ">>", APPEND), i + 2);
	if (input[i] == '>')
		return (add_token(tokens, ">", TRUNC), i + 1);
	if (input[i] == '<' && input[i + 1] == '<')
		return (add_token(tokens, "<<", HEREDOC), i + 2);
	if (input[i] == '<')
		return (add_token(tokens, "<", INPUT), i + 1);
	return (i + 1);
}
