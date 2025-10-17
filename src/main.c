#include "../include/minishell.h"

//debug
static void print_commands(t_cmd *cmd)
{
    int i = 1;

    while (cmd)
    {
        ft_printf("\nCMD #%d\n", i++);
        ft_printf("  command: %s\n", cmd->command ? cmd->command : "(null)");
        if (cmd->args)
        {
            ft_printf("  args: ");
            for (int j = 0; cmd->args[j]; j++)
                ft_printf("[%s] ", cmd->args[j]);
            ft_printf("\n");
        }
        if (cmd->io.infile)
            ft_printf("  infile: %s\n", cmd->io.infile);
		if (cmd->io.heredoc && cmd->io.heredoc_delimiter)
    		printf("  heredoc: %s\n", cmd->io.heredoc_delimiter);
        if (cmd->io.outfile)
            ft_printf("  outfile: %s%s\n", cmd->io.outfile, cmd->io.append ? " (append)" : "");
        if (cmd->pipe_output)
            ft_printf("  pipes to next command\n");
        cmd = cmd->next;
    }
    ft_printf("\n");
}

static void	print_tokens(t_token *list)
{
	t_token	*tmp = list;

	ft_printf("\n🔹 Tokens:\n");
	while (tmp)
	{
		ft_printf("  [%d] \"%s\"\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	data.env = envp;
	data.token = NULL;

	while (1)
	{
		data.user_input = readline("minishell> ");
		if (!data.user_input)
			break ;
		if (ft_strcmp(data.user_input, "exit") == 0)
		{
			free(data.user_input);
			break ;
		}

		if (parse_user_input(&data))
		{
			print_tokens(data.token);
			cmds = parser(data.token);
			print_commands(cmds);
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
}

