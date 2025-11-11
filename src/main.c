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
		data->user_input = readline("minishell> ");
		if (!data->user_input)
			break;

		if (*data->user_input)
			add_history(data->user_input);

		if (lexer(data))
		{
			//print_tokens(data->token); // debug
			expand_tokens(data->token, data);
			data->cmd = parser(data->token);
			//print_commands(data->cmd); // debug
			execute_commands(data->cmd, data->envp);
		}

		free_tokens(data->token);
		data->token = NULL;
		free_commands(data->cmd);
		data->cmd = NULL;
		free(data->user_input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.token = NULL; 
	data.cmd = NULL; 
	data.envp = envp;

	minishell_loop(&data);

	ft_printf("Exiting minishell.\n");
	rl_clear_history();
	return (0);
}

/*int	main(int argc, char **argv, char **envp) //main da marta
{
	t_data	data;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	data.token = NULL;
	data.envp = envp;

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