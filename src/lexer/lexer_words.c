#include "../../include/minishell.h"

int extract_word(t_token **tokens, const char *input, int start)
{
    int i;
    char *str;

    i = start;
    while (input[i] && !ft_is_space(input[i])
        && input[i] != '|' && input[i] != '<' && input[i] != '>')
        i++;

    str = ft_strndup(input + start, i - start);
    if (!str)
        return (i);
    add_token(tokens, str, WORD);
    free(str);
    return (i);
}