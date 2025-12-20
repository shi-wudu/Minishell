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

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_commands(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->io.heredoc && cmd->io.infile)
			unlink(cmd->io.infile);
		free(cmd->command);
		free_args(cmd->args);
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

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*res;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	res = ft_strjoin(s1, s2);
	free(s1);
	if (!res)
		return (NULL);
	return (res);
}
