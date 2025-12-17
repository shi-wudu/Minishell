/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:13 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/20 13:19:13 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_outfile(t_cmd *cmd, char *filename, bool append)
{
	cmd->io.outfile = ft_strdup(filename);
	cmd->io.append = append;
}

void	parse_redirect(t_cmd *cmd, t_token **tk)
{
	char	*filename;

	filename = (*tk)->next->value;
	if ((*tk)->type == INPUT)
		cmd->io.infile = ft_strdup(filename);

	else if ((*tk)->type == TRUNC)
		set_outfile(cmd, filename, false);

	else if ((*tk)->type == APPEND)
		set_outfile(cmd, filename, true);
		
	else if ((*tk)->type == HEREDOC)
	{
		if ((*tk)->next->type == STRING_DQUOTE || (*tk)->next->type == STRING_SQUOTE)
			cmd->io.heredoc_expand = false;
		else
			cmd->io.heredoc_expand = true;

		cmd->io.heredoc_delimiter = ft_strdup(filename);
		cmd->io.heredoc = true;
	}
	*tk = (*tk)->next->next;
}

t_cmd	*parse_pipe(t_cmd *cmd, t_token **tk)
{
	t_cmd	*new_cmd;

	cmd->pipe_output = true;
	new_cmd = calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	init_cmd(new_cmd);
	cmd->next = new_cmd;
	new_cmd->prev = cmd;
	*tk = (*tk)->next;
	return (new_cmd);
}