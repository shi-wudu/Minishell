#include "../../include/minishell.h"

t_token	*tokenize(const char *input)
{
	int			i;
	t_token		*tokens;
	int			next;

	i = 0;
	tokens = NULL;

	while (input[i])
	{
		i = skip_spaces(input, i);
		if (input[i] == '\0')
			break;

		if (input[i] == '\'' || input[i] == '"')
		{
			next = extract_quoted(&tokens, input, i);
			if (next == -1)
			{
				free_tokens(tokens);
				return (NULL);
			}
			i = next;
			continue;
		}

		if (is_redirect(input[i]))
			i = handle_redirects(&tokens, input, i);
		else if (input[i] == '|')
			add_token(&tokens, "|", PIPE), i++;
		else
			i = extract_word(&tokens, input, i);
	}

	add_token(&tokens, "END", END);
	return (tokens);
}
