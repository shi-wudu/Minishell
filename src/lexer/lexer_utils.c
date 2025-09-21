#include "../../include/minishell.h"

void free_tokens(t_token *list)
{
    t_token *tmp;
    while (list)
    {
        tmp = list;
        list = list->next;
        free(tmp->value);
        free(tmp);
    }
}

int extract_word(t_token **tokens, const char *input, int start)
{
    int     i;
    char    *str;
    
    i = start;
    while (input[i] && !ft_is_space(input[i])
        && input[i] != '|' && input[i] != '<' && input[i] != '>')
        i++;
    str = ft_strndup(input + start, i - start);
    add_token(tokens, str, TOKEN_WORD);
    free(str);
    return i;
}

int extract_quoted(t_token **tokens, const char *input, int start)
{
    int     i;
    char    quote;
    char    *str;

    quote = input[start];
    i = start + 1;
    while (input[i] && input[i] != quote)
        i++;
    if (input[i] != quote)
    {
        write(2, "minishell: unclosed quote\n", 27);
        return -1;
    }
    str = ft_strndup(input + start + 1, i - start - 1);
    add_token(tokens, str, TOKEN_STRING);
    free(str);
    return i + 1;
}


int handle_redirects(t_token **tokens, const char *input, int i)
{
    if (input[i] == '>' && input[i + 1] == '>')
        return (add_token(tokens, ">>", TOKEN_APPEND), i + 2);
    if (input[i] == '>')
        return (add_token(tokens, ">", TOKEN_REDIRECT_OUT), i + 1);
    if (input[i] == '<' && input[i + 1] == '<')
        return (add_token(tokens, "<<", TOKEN_HEREDOC), i + 2);
    if (input[i] == '<')
        return (add_token(tokens, "<", TOKEN_REDIRECT_IN), i + 1);
    return -1;
}

int handle_quotes(t_token **tokens, const char *input, int i)
{
    int next;

    next = extract_quoted(tokens, input, i);
    if (next == -1)
    {
        free_tokens(*tokens);
        return -1;
    }
    return next;
}
