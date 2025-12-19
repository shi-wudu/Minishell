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

static void minishell_loop(t_data *data)
{	
	int executed;
	while (1)
	{
		setup_signals_interactive();
		g_signal = 0;
		data->user_input = readline("minishell> ");
		if (!data->user_input)
		{
    		write(1, "exit\n", 5);
    		break;
		}

		if (*data->user_input)
			add_history(data->user_input);

		if (lexer(data))
		{
			//print_tokens(data->token); // debug
			expand_tokens(data->token, data);
			data->cmd = parser(data->token);
			//print_commands(data->cmd); // debug
            executed = execute_commands(data->cmd, data);
            if (executed == 1 && data->cmd)
            {
                t_cmd *last = data->cmd;
                while (last->next)
                    last = last->next;
                data->last_exit_status = last->exit_status;
				//printf("EXIT CODE = %d\n", data->last_exit_status); //debug para ver exit ccode se esta certo
			}
		}
		cleanup_iteration(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.token = NULL; 
	data.cmd = NULL; 
	data.envp = dup_env(envp);
	if (!data.envp)
	{
    	ft_putendl_fd("minishell: failed to duplicate environment", 2);
    	return (1);
	}
	data.last_exit_status = 0;
	minishell_loop(&data);
	free_all(&data);
	return (0);
}
