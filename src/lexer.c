#include "../include/minishell.h"

static t_token *new_token(const char *value, t_token_type type)
{
    t_token *token;
    
    token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = ft_strdup(value);
    token->type = type;
    token->next = NULL;
    return token;
}

void add_token(t_token **tokens, const char *value, t_token_type type)
{
    t_token *new;
    t_token *tmp;

    new = new_token(value, type);
    if (!new)                                       //criar error leaks?
        return;
    if (!*tokens)
    {
        *tokens = new;
        return;
    }
    tmp = *tokens;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void add_or_concat(t_token **tokens, const char *value, t_token_type type)
{
    t_token *last;

    if (!*tokens)
    {
        add_token(tokens, value, type);
        return;
    }
    last = *tokens;
    while (last->next)
        last = last->next;
    if (last->type == TOKEN_WORD || last->type == TOKEN_STRING)
    {
        char *joined = ft_strjoin(last->value, value);
        free(last->value);
        last->value = joined;
    }
    else
        add_token(tokens, value, type);
}

t_token *tokenize(const char *input)
{
    int i;
    t_token *tokens;
    int next;

    i = 0;
    tokens = NULL;
    while (input[i])
    {
        if (ft_is_space(input[i]))
            i++;
        else if (input[i] == '|')
        {
            add_token(&tokens, "|", TOKEN_PIPE);
            i ++;
        }
        else if ((next = handle_redirects(&tokens, input, i)) != -1)
            i = next;
        else if (input[i] == '"' || input[i] == '\'')
        {
            i = handle_quotes(&tokens, input, i);
            if (i == -1)
                return NULL;
        }
        else
            i = extract_word(&tokens, input, i);
    }
    add_token(&tokens, "END", TOKEN_END);
    return tokens;
}
