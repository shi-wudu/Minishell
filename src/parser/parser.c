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

static t_cmd	*init_new_cmd(t_cmd **head)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	init_cmd(new);
	if (!*head)
		*head = new;
	return (new);
}

// Analisa o token atual e delega para a função apropriada
// (palavra, pipe ou redireção).

static void	handle_token(t_cmd **current, t_token **tk, t_data *data)
{
	if ((*tk)->type == WORD)
		parse_word(*current, tk);
	else if ((*tk)->type == PIPE)
		*current = parse_pipe(*current, tk);
	else if ((*tk)->type == INPUT || (*tk)->type == TRUNC
		|| (*tk)->type == APPEND || (*tk)->type == HEREDOC)
		parse_redirect(*current, tk, data);
	else
		*tk = (*tk)->next;
}

// Converte a lista de tokens numa lista ligada de comandos.
// Interrompe em caso de erro de parsing.

t_cmd	*parser(t_token *tokens, t_data *data)
{
	t_cmd	*head;
	t_cmd	*current;
	t_token	*tk;

	head = NULL;
	current = NULL;
	tk = tokens;
	while (tk && tk->type != END && !data->parse_error)
	{
		if (!current)
		{
			current = init_new_cmd(&head);
			if (!current)
				return (NULL);
		}
		handle_token(&current, &tk, data);
	}
	return (head);
}
