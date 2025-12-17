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
	while (1)
	{
		setup_signals_interactive();
		prog_data()->heredoc_interrupted = 0;
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
            execute_commands(data->cmd, data);
            if (data->cmd)
            {
                t_cmd *last = data->cmd;
                while (last->next)
                    last = last->next;
                data->last_exit_status = last->exit_status;
<<<<<<< Updated upstream
				//printf("EXIT CODE = %d\n", data->last_exit_status); //debug para ver exit ccode se esta certo
			}
=======
                //printf("EXIT CODE = %d\n", data->last_exit_status); //debug para ver exit ccode se esta certo
            }
>>>>>>> Stashed changes
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

t_prog	*prog_data(void)
{
	static t_prog	data;

	return (&data);
}

/*int	main(int argc, char **argv, char **envp) //main da marta
{
	t_data	data;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	data.token = NULL;
	data.envp = envp;
	data.last_exit_status = 0;

	while (1)
	{
		data.user_input = readline("minishell> ");
		if (!data.user_input)
			break ;

		if (data.user_input[0] != '\0')
			add_history(data.user_input);

		if (lexer(&data))
		{
			print_tokens(data.token);
			cmds = parser(data.token);
			print_commands(cmds);
			
			execute_commands(cmds, envp);
			
			free_commands(cmds);
		}

		if (data.token)
		{
			free_tokens(data.token);
			data.token = NULL;
		}
		free(data.user_input);
	}
	ft_printf("Exiting minishell.\n");
	rl_clear_history(); 
	return (0);
}*/