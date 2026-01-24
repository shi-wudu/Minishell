/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:25 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/20 21:39:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Gera um nome único para o ficheiro temporário do heredoc.

char	*gen_heredoc_filename(void)
{
	static int	i = 0;
	char		*nbr;
	char		*name;

	nbr = ft_itoa(i++);
	name = ft_strjoin("/tmp/minishell_heredoc_", nbr);
	free(nbr);
	return (name);
}

// Verifica se a leitura do heredoc deve terminar.

bool	heredoc_should_stop(char *line, char *delimiter)
{
	if (!line)
		return (true);
	if (ft_strcmp(line, delimiter) == 0)
		return (true);
	return (false);
}

// Resolve todos os heredocs de um comando.
// Lê cada heredoc, mantendo apenas o último.
// Remove ficheiros temporários antigos se necessário.

char	*resolve_heredocs(t_cmd *cmd, t_data *data)
{
	int		i;
	char	*file;
	char	*last;

	i = 0;
	last = NULL;
	while (i < cmd->heredoc_count)
	{
		file = read_heredoc(cmd->heredoc_delimiters[i],
				cmd->io.heredoc_expand, data);
		if (!file)
			return (free(last), NULL);
		if (last)
			unlink(last);
		free(last);
		last = file;
		i++;
	}
	return (last);
}
