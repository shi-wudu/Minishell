/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:14:13 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/21 21:52:49 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	parse_user_input(t_data *data)
{
	if (!data->user_input || ft_strcmp(data->user_input, "") == 0)
		return (false);
	add_history(data->user_input);
	data->token = tokenize(data->user_input);
	if (!data->token)
	{
		data->token = NULL;
		return (false);
	}
	if (has_syntax_error(data->token))
	{
		free_tokens(data->token);
		data->token = NULL;
		return (false);
	}
	return (true);
}
