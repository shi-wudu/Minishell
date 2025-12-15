#include "minishell.h"

static void	handle_dollar(const char *str, char **envp, int *i, char **res, int last)
{
	int		start;
	char	*name;
	char	*val;
	char	*num;

	if (str[*i + 1] == '?')
	{
		num = ft_itoa(last);
		*res = ft_strjoin_free(*res, num);
		free(num);
		*i += 2;
		return ;
	}
	start = ++(*i);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (start == *i)
		*res = ft_strjoin_free(*res, "$");
	else
	{
		name = ft_substr(str, start, *i - start);
		val = get_env_value(envp, name);
		*res = ft_strjoin_free(*res, val ? val : "");
		free(name);
	}
}

char	*expand_dollar_only(const char *str, char **envp, int last)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (str && str[i])
	{
		if (str[i] == '$')
			handle_dollar(str, envp, &i, &res, last);
		else
		{
			res = append_char(res, str[i]);
			i++;
		}
	}
	return (res);
}

void expand_tokens(t_token *tokens, t_data *data)
{
    while (tokens)
    {
        if (tokens->type == HEREDOC && tokens->next)
        {
            tokens = tokens->next->next;
            continue;
        }

        if (tokens->type == WORD || tokens->type == STRING_DQUOTE)
        {
            char *expanded = expand_dollar_only(
                tokens->value,
                data->envp,
                data->last_exit_status
            );
            free(tokens->value);
            tokens->value = expanded;
        }
        tokens = tokens->next;
    }
}
