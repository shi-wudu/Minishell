#include "minishell.h"

char	*expand_string(char *str, t_data *data)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
			result = join_and_skip(result, str, &i, '\'');
		else if (str[i] == '"')
			result = join_and_expand_double(result, str, &i, data);
		else if (str[i] == '$')
			result = join_and_expand_dollar(result, str, &i, data);
		else
			result = append_char(result, str[i++]);
	}
	return (result);
}

void	expand_tokens(t_token *tokens, t_data *data)
{
	while (tokens)
	{
		if (tokens->type == STRING_DQUOTE || tokens->type == WORD)
		{
			char *expanded = expand_string(tokens->value, data);
			free(tokens->value);
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
}
