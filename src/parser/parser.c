/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:58 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/16 16:10:28 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	parser_handle_token(t_cmd **cmd, t_cmd **head,
			t_token **tk, t_data *data)
{
	if ((*tk)->type == WORD || (*tk)->type == PIPE)
		return (handle_word_pipe(cmd, head, tk));
	if ((*tk)->type == INPUT || (*tk)->type == TRUNC
		|| (*tk)->type == APPEND || (*tk)->type == HEREDOC)
		return (parse_redirect_token(*cmd, tk, data));
	*tk = (*tk)->next;
	return (true);
}

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
		if (!parser_handle_token(&cmd, &head, &tk, data))
			return (NULL);
	}
	return (head);
}
