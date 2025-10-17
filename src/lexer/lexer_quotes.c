#include "../../include/minishell.h"

int extract_quoted(t_token **tokens, const char *input, int start)
{
    char quote;
    int i;
    char *str;

    quote = input[start];
    i = start + 1;

    while (input[i] && input[i] != quote)
        i++;
    if (!input[i])
    {
        errmsg("minishell", "unclosed quote", true);
        return (-1);
    }
    str = ft_strndup(input + start + 1, i - start - 1);
    if (!str)
        return (-1); 															// gerir erro
    add_token(tokens, str, STRING);
    free(str);
    return (i + 1);
}

