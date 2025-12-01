/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:09 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/21 22:00:37 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd->command = NULL;
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->pipe_output = false;
	cmd->io.infile = NULL;
	cmd->io.outfile = NULL;
	cmd->io.heredoc_delimiter = NULL;
	cmd->io.append = false;
	cmd->io.heredoc = false;
}

void	free_str_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_commands(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free(cmd->command);
		free_str_tab(cmd->args);

		if (cmd->io.infile)
			free(cmd->io.infile);
		if (cmd->io.outfile)
			free(cmd->io.outfile);
		if (cmd->io.heredoc_delimiter)
			free(cmd->io.heredoc_delimiter);

		free(cmd);
		cmd = tmp;
	}
}
