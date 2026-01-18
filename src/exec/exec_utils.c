#include "minishell.h"

void	cleanup_and_exit_child(t_data *data, int status)
{
	if (data)
	{
		free_commands(data->cmd);
		data->cmd = NULL;
		free_environment(data->envp);
		data->envp = NULL;
		rl_clear_history();
	}
	exit(status);
}
