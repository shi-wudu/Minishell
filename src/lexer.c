#include "../include/minishell.h"

static t_token *new_token(const char *value, t_token_type type)
{
    t_token *token;
    
    token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = strdup(value); //substituir libft
    token->type = type;
    token->next = NULL;
    return token;
}

static void add_token(t_token **head, const char *value, t_token_type type)
{
    t_token *new;
    t_token *tmp;

    new = new_token(value, type);
    if (!new)
        return;
    if (!*head)
    {
        *head = new;
        return;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

static int extract_word(const char *input, int start, t_token **tokens)
{
    int     i;
    char    *str;
    
    i = start;
    while (input[i] && !ft_is_space((unsigned char)input[i])
        && input[i] != '|' && input[i] != '<' && input[i] != '>')
        i++;
    str = strndup(input + start, i - start); //substituir libft
    add_token(tokens, str, TOKEN_WORD);
    free(str);
    return i;
}

t_token *tokenize(const char *input)
{
    int i;
    t_token *tokens;

    tokens = NULL;
    i = 0;
    while (input[i])
    {
        if (ft_is_space((unsigned char)input[i]))
            i++;
        else if (input[i] == '|')
        {
            add_token(&tokens, "|", TOKEN_PIPE);
            i++;
        }
        else if (input[i] == '>' && input[i + 1] == '>')
        {
            add_token(&tokens, ">>", TOKEN_APPEND);
            i += 2;
        }
        else if (input[i] == '>')
        {
            add_token(&tokens, ">", TOKEN_REDIRECT_OUT);
            i++;
        }
        else if (input[i] == '<' && input[i + 1] == '<')
        {
            add_token(&tokens, "<<", TOKEN_HEREDOC);
            i += 2;
        }
        else if (input[i] == '<')
        {
            add_token(&tokens, "<", TOKEN_REDIRECT_IN);
            i++;
        }
        //else if (input[i] == '"' || input[i] == '\'')   //    <---------  
        else
            i = extract_word(input, i, &tokens);
    }
    add_token(&tokens, "END", TOKEN_END);
    return tokens;
}

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