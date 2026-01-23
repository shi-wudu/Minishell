/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:58 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/20 21:40:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Constrói a lista de comandos a partir da lista de tokens.
// Agrupa argumentos, pipes e redirections num conjunto de t_cmd.
// Retorna a cabeça da lista ou NULL em caso de erro.

t_cmd *parser(t_token *tokens, t_data *data)
{
    t_cmd   *head = NULL;
    t_cmd   *cmd = NULL;
    t_token *tk = tokens;

    while (tk && tk->type != END && !data->parse_error)
    {
        if (!cmd)
            cmd = new_cmd(&head, NULL);

        if (tk->type == WORD || tk->type == PIPE)
        {
            if (!handle_word_pipe(&cmd, &head, &tk))
                return (NULL);
        }
        else if (tk->type == INPUT || tk->type == TRUNC
              || tk->type == APPEND || tk->type == HEREDOC)
        {
            if (!parse_redirect_token(cmd, &tk, data))
                return (NULL);
        }
        else
            tk = tk->next;
    }
    return (head);
}
