/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:49 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/20 13:19:49 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	has_syntax_error(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->type == PIPE && tmp->next && tmp->next->type == PIPE)
		{
			errmsg("syntax error: double pipe", "|", true);
			return (true);
		}
		else if (tmp->type >= INPUT
			&& tmp->next && (tmp->next->type >= INPUT && tmp->next->type <= HEREDOC))
		{
			errmsg("syntax error: too many redirects", tmp->next->value, true);
			return (true);
		}
		else if (tmp->type == PIPE && tmp->prev == NULL )
		{
			errmsg("syntax error: pipe in the begining", " ", true);
			return(true);
		}
		else if ((tmp->type >= INPUT && tmp->type <= HEREDOC) 
			&& ((tmp->next->type == END || tmp->next->type == PIPE )))
		{
			errmsg("syntax error: redirect needs something", NULL, true);
			return(true);
		}
		tmp = tmp->next;
	}
	return (false);
}
