/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:52 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/20 13:18:52 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errmsg(const char *msg, const char *arg, bool newline)
{
	write(2, msg, strlen(msg));
	if (arg)
	{
		write(2, ": ", 2);
		write(2, arg, strlen(arg));
	}
	if (newline)
		write(2, "\n", 1);
}

int	ft_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

void	free_environment(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void free_all(t_data *data)
{
    free_environment(data->envp);
    rl_clear_history();
}

void cleanup_iteration(t_data *data)
{
    free_tokens(data->token);
    data->token = NULL;

    free_commands(data->cmd);
    data->cmd = NULL;

    free(data->user_input);
    data->user_input = NULL;
}
