#include "minishell.h"

char	*append_char(char *s, char c)
{
	char	tmp[2];
	char	*new;

	tmp[0] = c;
	tmp[1] = '\0';
	new = ft_strjoin(s, tmp);
	free(s);
	return (new);
}

char	*join_and_skip(char *result, char *str, int *i, char quote)
{
	int		start;
	char	*segment;
	char	*new;

	start = ++(*i);
	while (str[*i] && str[*i] != quote)
		(*i)++;
	segment = ft_substr(str, start, *i - start);
	new = ft_strjoin(result, segment);
	free(result);
	free(segment);
	if (str[*i] == quote)
		(*i)++;
	return (new);
}
