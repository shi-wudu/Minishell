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

// Decide como tratar o token atual durante o parsing.
// Encaminha WORD e PIPE para handle_word_pipe,
// redirections para parse_redirect_token,
// ou avança o token em casos neutros.

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

// Constrói a lista de comandos a partir da lista de tokens.
// Agrupa argumentos, pipes e redirections num conjunto de t_cmd.
// Retorna a cabeça da lista ou NULL em caso de erro.

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
