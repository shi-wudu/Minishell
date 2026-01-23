/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:13 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/20 13:19:13 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(t_cmd **head, t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd(cmd);
	cmd->prev = prev;
	if (prev)
		prev->next = cmd;
	else
		*head = cmd;
	return (cmd);
}

// Trata tokens WORD e PIPE.
// WORD adiciona argumento ao comando atual.
// PIPE termina o comando atual e cria um novo.

bool	handle_word_pipe(t_cmd **cmd, t_cmd **head, t_token **tk)
{
	if ((*tk)->type == WORD)
	{
		if (!add_expanded_args(*cmd, (*tk)->expanded))
			return (false);
		*tk = (*tk)->next;
		return (true);
	}
	else if ((*tk)->type == PIPE)
	{
		(*cmd)->pipe_output = true;
		*cmd = new_cmd(head, *cmd);
		*tk = (*tk)->next;
		return (true);
	}
	return (false);
}
