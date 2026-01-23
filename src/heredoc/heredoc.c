/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:25 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/20 21:39:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Cria e abre um ficheiro temporário para o heredoc.
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

// Prepara o ambiente para leitura de heredoc:
// duplica stdin, cria ficheiro temporário e configura sinais.

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

// Loop principal de leitura do heredoc até encontrar o delimitador

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

// Lê um heredoc completo e devolve o nome do ficheiro temporário.

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

// Processa todos os heredocs antes da execução.
// Deve ser chamada no processo pai.

int	prepare_heredocs(t_cmd *cmd, t_data *data)
{
	char	*last;
	data->in_heredoc = true;
	while (cmd)
	{
		last = resolve_heredocs(cmd, data);
		if (cmd->heredoc_count && !last)
			return (data->last_exit_status = 130, 130);
		if (last)
		{
			if (cmd->io.infile && cmd->io.infile_is_heredoc)
			{
				unlink(cmd->io.infile);
				free(cmd->io.infile);
			}
			cmd->io.infile = last;
			cmd->io.infile_is_heredoc = true;
		}
		cmd = cmd->next;
	}
	data->in_heredoc = false;
	return (0);
}
