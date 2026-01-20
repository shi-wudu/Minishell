/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:13 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/20 13:19:13 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Aumenta dinamicamente um array de strings para adicionar um novo valor.

static char	**grow_str_array(char **old, char *value)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	while (old && old[i])
		i++;
	new = ft_calloc(i + 2, sizeof(char *));
	if (!new)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new[j] = old[j];
		j++;
	}
	new[i] = ft_strdup(value);
	return (new);
}

// Adiciona um argumento ao comando.
// Define o nome do comando se ainda não estiver definido.

bool	add_arg(t_cmd *cmd, char *value)
{
	char	**new;

	new = grow_str_array(cmd->args, value);
	if (!new)
		return (false);
	free(cmd->args);
	cmd->args = new;
	if (!cmd->command)
		cmd->command = ft_strdup(value);
	return (true);
}
