/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:25 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/21 21:34:53 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc_line_expanded(int fd, char *line, char **envp,
		int last)
{
	char	*out;

	out = expand_dollar_only(line, envp, last);
	write(fd, out, ft_strlen(out));
	write(fd, "\n", 1);
	free(out);
}

static void	write_heredoc_line_noexp(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

void	write_heredoc_line(int fd, char *line, char **envp, bool expand,
		int last)
{
	if (expand)
		write_heredoc_line_expanded(fd, line, envp, last);
	else
		write_heredoc_line_noexp(fd, line);
}
