/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:58 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/21 22:01:09 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Cria e inicializa um novo comando.
// Define-o como cabeça da lista caso ainda não exista.

t_cmd	*parser(t_token *tokens, t_data *data)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_token	*tk;

	head = NULL;
	cmd = NULL;
	tk = tokens;
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

