#include "../../include/minishell.h"

t_cmd *parse_tokens(t_token *tokens)
{
    t_cmd *head = cmd_new();
    t_cmd *current = head;

    while (tokens && tokens->type != TOKEN_END)
    {
        if (tokens->type == TOKEN_WORD || tokens->type == TOKEN_STRING)
            cmd_add_arg(current, tokens->value);

        else if (tokens->type == TOKEN_REDIRECT_IN && tokens->next)
        {
            current->infile = ft_strdup(tokens->next->value);
            tokens = tokens->next;
        }

        else if (tokens->type == TOKEN_REDIRECT_OUT && tokens->next)
        {
            current->outfile = ft_strdup(tokens->next->value);
            tokens = tokens->next;
        }

        else if (tokens->type == TOKEN_APPEND && tokens->next)
        {
            current->outfile = ft_strdup(tokens->next->value);
            tokens = tokens->next;
        }

        else if (tokens->type == TOKEN_HEREDOC && tokens->next)
        {
            current->infile = ft_strdup(tokens->next->value);
            tokens = tokens->next;
        }

        else if (tokens->type == TOKEN_PIPE)
        {
            current->next = cmd_new();
            current = current->next;
        }

        tokens = tokens->next;
    }
    return head;
}

