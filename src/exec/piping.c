/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-30 17:50:12 by user              #+#    #+#             */
/*   Updated: 2025-11-30 17:50:12 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

extern volatile sig_atomic_t g_signal;

static void handle_child_process(t_cmd *cmd, int in_fd, int out_fd, t_data *data)
{
    char    *path;

    if (apply_redirections(cmd, data->envp, data->last_exit_status) == -1)
        exit(1);
    
    if (in_fd != STDIN_FILENO)
    {
        if (dup2(in_fd, STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(1);
        }
        close(in_fd);
    }

    if (out_fd != STDOUT_FILENO)
    {
        if (dup2(out_fd, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            exit(1);
        }
        close(out_fd);
    }

    if (is_builtin(cmd->command))
        exit(exec_builtin(cmd->args, &data->envp, false));

    path = resolve_path(cmd->command, data->envp);
    if (!path)
    {
        ft_putstr_fd("minishell: command not found: ", 2);
        ft_putendl_fd(cmd->command, 2);
        exit(127);
    }
    
    if (execve(path, cmd->args, data->envp) == -1)
    {
        perror("execve");
        free(path);
        exit(1);
    }
}
 
void execute_child(t_cmd *cmd, int in_fd, int out_fd, t_data *data)
{
    handle_child_process(cmd, in_fd, out_fd, data);
}

static void	wait_for_children(t_cmd *cmd)
{
    int		status;
    pid_t	pid;
    t_cmd	*current;
    int sig;

    current = cmd;
    while (current)
    {
        if (current->exit_status != 0)
        {
            pid = waitpid(current->exit_status, &status, 0);
            if (pid == -1)
                break;

            if (WIFEXITED(status))
                current->exit_status = WEXITSTATUS(status);

            else if (WIFSIGNALED(status))
            {
                sig = WTERMSIG(status);
                if (sig == SIGINT)
					write(1, "\n", 1); 
                if (sig == SIGQUIT) 
                    write(1, "Quit: 3\n", 8);

                current->exit_status = 128 + sig;
            }
            else
                current->exit_status = 1;
        }
        current = current->next;
    }
}

void execute_commands_piped(t_cmd *cmd, t_data *data)
{
    g_signal = SIG_CHILD;
    t_cmd	*current;
    int		pipefd[2];
    int		in_fd;
    int		out_fd;
    pid_t	pid;

    if (!cmd)
        return ;
    
    current = cmd;
    in_fd = STDIN_FILENO;
    
    while (current)
    {
        out_fd = STDOUT_FILENO;
        if (!current->command || current->command[0] == '\0')
        {
            current->exit_status = 0;
            current = current->next;
            continue;
        }
        if (current->pipe_output)
        {
            if (create_pipe(pipefd) == -1)
                return ;
            out_fd = pipefd[1];
        }
        
        if (is_builtin(current->command) && !current->pipe_output && current->prev == NULL)
        {
            current->exit_status = exec_builtin(current->args, (char ***)&data->envp, true);
            if (in_fd != STDIN_FILENO)
                close(in_fd);
        }
        else
        {
            pid = fork();
            if (pid == -1)
            {
                perror("fork");
                return ;
            }
            
            if (pid == 0)
            {
                setup_signals_child();
                execute_child(current, in_fd, out_fd, data);
            }
            else
                current->exit_status = pid;
                            
            if (in_fd != STDIN_FILENO)
                close(in_fd);
            if (out_fd != STDOUT_FILENO)
                close(out_fd);
            
            if (current->pipe_output)
                in_fd = pipefd[0];
        }
        
        current = current->next;
    }
    
    wait_for_children(cmd);
    g_signal = SIG_IDLE; 
}
