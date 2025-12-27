/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:25 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/21 21:34:53 by seilkiv          ###   ########.fr       */
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
