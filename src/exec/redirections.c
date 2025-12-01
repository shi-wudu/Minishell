/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-30 17:37:28 by user              #+#    #+#             */
/*   Updated: 2025-11-30 17:37:28 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	redirect_input(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(infile, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putendl_fd("minishell: dup2 failed", 2);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	redirect_output(char *outfile, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(outfile, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(outfile, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_putendl_fd("minishell: dup2 failed", 2);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_redirections(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->io.infile)
	{
		if (redirect_input(cmd->io.infile) == -1)
			return (-1);
	}
	if (cmd->io.outfile)
	{
		if (redirect_output(cmd->io.outfile, cmd->io.append) == -1)
			return (-1);
	}
	return (0);
}