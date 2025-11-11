#include "minishell.h"

static char	*expand_var(char *str, int *i, t_data *data)
{
	int		start;
	char	*var_name;
	char	*value;

	(*i)++; // '$'

	/*if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(data->last_exit_status));
	}*/

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (start == *i)
		return (ft_strdup("$"));

	var_name = ft_substr(str, start, *i - start);
	value = get_env_value(data->envp, var_name);
	free(var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*join_and_expand_double(char *result, char *str, int *i, t_data *data)
{
	char	*segment;
	char	*tmp;
	char	*expanded;
	char	*new;

	(*i)++;
	segment = ft_strdup("");
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			expanded = expand_var(str, i, data);
			tmp = ft_strjoin(segment, expanded);
			free(segment);
			free(expanded);
			segment = tmp;
		}
		else
			segment = append_char(segment, str[(*i)++]);
	}
	if (str[*i] == '"')
		(*i)++;
	new = ft_strjoin(result, segment);
	free(result);
	free(segment);
	return (new);
}

char	*join_and_expand_dollar(char *result, char *str, int *i, t_data *data)
{
	char	*expanded;
	char	*new;

	expanded = expand_var(str, i, data);
	new = ft_strjoin(result, expanded);
	free(result);
	free(expanded);
	return (new);
}
