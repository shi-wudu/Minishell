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

void	parse_redirect(t_cmd *cmd, t_token **tk)
{
	char	*filename;

	if (!cmd || !*tk || !(*tk)->next)
		return ;
	filename = (*tk)->next->value;
	if ((*tk)->type == INPUT)
		cmd->io.infile = ft_strdup(filename);
	else if ((*tk)->type == TRUNC)
	{
		cmd->io.outfile = ft_strdup(filename);
		cmd->io.append = false;
	}
	else if ((*tk)->type == APPEND)
	{
		cmd->io.outfile = ft_strdup(filename);
		cmd->io.append = true;
	}
	else if ((*tk)->type == HEREDOC)
	{
		cmd->io.heredoc_delimiter = ft_strdup(filename);
		cmd->io.heredoc = true;
	}
	*tk = (*tk)->next->next;
}
