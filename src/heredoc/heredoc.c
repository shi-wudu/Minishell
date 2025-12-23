/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:25 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/21 21:34:53 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_heredoc_file(char **tmp_file)
{
	int	fd;

	*tmp_file = gen_heredoc_filename();
	fd = open(*tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		free(*tmp_file);
		return (-1);
	}
	return (fd);
}

static int	heredoc_setup(char **tmp_file, int *saved_stdin)
{
	int	fd;

	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == -1)
		return (-1);
	fd = open_heredoc_file(tmp_file);
	if (fd == -1)
	{
		close(*saved_stdin);
		return (-1);
	}
	setup_signals_heredoc();
	return (fd);
}

static bool	heredoc_loop(int fd, char *delimiter, bool expand, t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT || heredoc_should_stop(line, delimiter))
		{
			free(line);
			return (false);
		}
		write_heredoc_line(fd, line, data, expand);
		free(line);
	}
	return (true);
}

char	*read_heredoc(char *delimiter, bool expand, t_data *data)
{
	int		fd;
	int		saved_stdin;
	char	*tmp_file;

	fd = heredoc_setup(&tmp_file, &saved_stdin);
	if (fd == -1)
		return (NULL);
	heredoc_loop(fd, delimiter, expand, data);
	close(fd);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	setup_signals_interactive();
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		unlink(tmp_file);
		free(tmp_file);
		return (NULL);
	}
	return (tmp_file);
}

/*
** Lê todos os heredocs antes de executar qualquer comando
** Deve ser chamada NO PAI, antes de fork()
*/
int	prepare_heredocs(t_cmd *cmd, t_data *data)
{
	char	*file;

	while (cmd)
	{
		if (cmd->io.heredoc)
		{
			file = read_heredoc(cmd->io.heredoc_delimiter,
					cmd->io.heredoc_expand, data);
			if (!file)
			{
				data->last_exit_status = 130;
				return (130);
			}
			cmd->io.infile = file;
		}
		cmd = cmd->next;
	}
	return (0);
}
