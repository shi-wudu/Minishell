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

#include "../../include/minishell.h"

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

static void	handle_token(t_cmd **current, t_token **tk)
{
	if ((*tk)->type == WORD)
		parse_word(*current, tk);
	else if ((*tk)->type == PIPE)
		*current = parse_pipe(*current, tk);
	else if ((*tk)->type == INPUT || (*tk)->type == TRUNC
		|| (*tk)->type == APPEND || (*tk)->type == HEREDOC)
		parse_redirect(*current, tk);
	else
		*tk = (*tk)->next;
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_token	*tk;

	head = NULL;
	current = NULL;
	tk = tokens;
	while (tk && tk->type != END)
	{
		if (!current)
		{
			current = init_new_cmd(&head);
			if (!current)
				return (NULL);
		}
		handle_token(&current, &tk);
	}
	return (head);
}
