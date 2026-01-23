/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:42 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/20 13:18:42 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	print_commands(t_cmd *cmd)
{
	int	i;

	i = 1;
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
			ft_printf("  outfile: %s%s\n", cmd->io.outfile,
				cmd->io.append ? " (append)" : "");
		if (cmd->pipe_output)
			ft_printf("  pipes to next command\n");
		cmd = cmd->next;
	}
	ft_printf("\n");
}*/

/*void	print_tokens(t_token *list)
{
	t_token	*tmp = list;

	ft_printf("\n Tokens:\n");
	while (tmp)
	{
		ft_printf("  [%d] \"%s\"\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
	ft_printf("\n");
}*/

/* void execute_commands(t_cmd *cmds, char **envp)
{
	t_cmd	*cmd;
	int		exit_status;

	cmd = cmds;
	while (cmd)
	{
		if (is_builtin(cmd->command))
		{
			exit_status = exec_builtin(cmd->args, envp);
			(void)exit_status;
		}
		else
		{
			ft_printf("%s: command not found\n", cmd->command);
		}
		cmd = cmd->next;
	}
} */

/*static const char *token_type_str(t_token_type type)
{
	if (type == WORD) return ("WORD");
	if (type == PIPE) return ("PIPE");
	if (type == INPUT) return ("INPUT");
	if (type == TRUNC) return ("TRUNC");
	if (type == APPEND) return ("APPEND");
	if (type == HEREDOC) return ("HEREDOC");
	if (type == END) return ("END");
	return ("UNKNOWN");
}

static const char *seg_type_str(t_seg_type type)
{
	if (type == UNQUOTED) return ("UNQUOTED");
	if (type == SINGLE_QUOTED) return ("SINGLE_QUOTED");
	if (type == DOUBLE_QUOTED) return ("DOUBLE_QUOTED");
	return ("UNKNOWN");
}

void	print_tokens_and_segments(t_token *tk)
{
	int ti = 0;

	while (tk)
	{
		printf("Token[%d]: %s\n", ti++, token_type_str(tk->type));
		if (tk->type == WORD)
		{
			t_segment *seg = tk->segments;
			int si = 0;
			while (seg)
			{
				printf("  Segment[%d]: type=%s value=\"%s\"\n",
					si++, seg_type_str(seg->type), seg->value);
				seg = seg->next;
			}
		}
		tk = tk->next;
	}
}*/