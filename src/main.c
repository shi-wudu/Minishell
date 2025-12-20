/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:42 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/20 13:18:42 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	init_data(t_data *data, char **envp)
{
	data->token = NULL;
	data->cmd = NULL;
	data->last_exit_status = 0;
	data->parse_error = false;
	data->envp = dup_env(envp);
	if (!data->envp)
	{
		ft_putendl_fd("minishell: failed to duplicate environment", 2);
		return (false);
	}
	return (true);
}

static void	process_input(t_data *data)
{
	int		executed;
	t_cmd	*last;

	if (!lexer(data))
		return ;
	expand_tokens(data->token, data);
	data->parse_error = false;
	data->cmd = parser(data->token, data);
	if (data->parse_error)
		return ;
	executed = execute_commands(data->cmd, data);
	if (executed && data->cmd)
	{
		last = data->cmd;
		while (last->next)
			last = last->next;
		data->last_exit_status = last->exit_status;
	}
}

static void	minishell_loop(t_data *data)
{
	while (1)
	{
		setup_signals_interactive();
		g_signal = 0;
		data->user_input = readline("minishell> ");
		if (!data->user_input)
			return (write(1, "exit\n", 5), (void)0);
		if (*data->user_input)
			add_history(data->user_input);
		process_input(data);
		cleanup_iteration(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	if (!init_data(&data, envp))
		return (1);
	minishell_loop(&data);
	free_all(&data);
	return (0);
}
