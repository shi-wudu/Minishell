/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:29 by seilkiv           #+#    #+#             */
/*   Updated: 2025/12/20 00:47:37 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Cria um novo token com valor e tipo definidos.

t_token	*ft_new_token(t_token_type type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->segments = NULL;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

// Adiciona um token ao fim da lista.

void	ft_token_list_add_back(t_token **lst, t_token *new)
{
	t_token	*cur;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	new->prev = cur;
}

// Liberta toda a lista de tokens.

void	ft_clear_token_list(t_token **lst)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;

		if (tmp->type == WORD)
		{
			free_segments(tmp->segments);
			free_args(tmp->expanded);
		}
		free(tmp);
		tmp = next;
	}
	*lst = NULL;
}
