#include "../../include/minishell.h"

int	is_redirect(char c)
{
	return (c == '<' || c == '>');
}

int	skip_spaces(const char *str, int i)
{
	while (str[i] && ft_is_space(str[i]))
		i++;
	return (i);
}
