/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:52 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/20 13:18:52 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// Liberta todos os recursos globais do minishell
// (ambiente e histórico do readline).

void	free_all(t_data *data)
{
	free_environment(data->envp);
	rl_clear_history();
}

// Limpa todos os dados associados a uma iteração do loop:
// tokens, comandos e input do utilizador.

void	cleanup_iteration(t_data *data)
{
	ft_clear_token_list(&data->token);
	data->token = NULL;
	free_commands(data->cmd);
	data->cmd = NULL;
	free(data->user_input);
	data->user_input = NULL;
}
