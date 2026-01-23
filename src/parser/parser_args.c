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

bool	add_expanded_args(t_cmd *cmd, char **expanded)
{
	int	i;

	if (!expanded)
		return (true);
	i = 0;
	while (expanded[i])
	{
		cmd->args = append_str_array(cmd->args, ft_strdup(expanded[i]));
		if (!cmd->command)
			cmd->command = ft_strdup(expanded[i]);
		i++;
	}
	return (true);
}
