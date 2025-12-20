/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-30 17:33:30 by user              #+#    #+#             */
/*   Updated: 2025-11-30 17:33:30 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*check_direct_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}
 
static char	*search_in_path(char *cmd, char *path_env)
{
	char	**path_dirs;
	char	*full_path;
	char	*tmp;
	int		i;
	char    *dir;

	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		dir = (path_dirs[i][0] == '\0') ? "." : path_dirs[i];
		tmp = ft_strjoin(dir, "/");
		if (!tmp)
			return (free_args(path_dirs), NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (free_args(path_dirs), NULL);
		if (access(full_path, X_OK) == 0)
			return (free_args(path_dirs), full_path);
		free(full_path);
		i++;
	}
	free_args(path_dirs);
	return (NULL);
}

char	*resolve_path(char *cmd, char **envp)
{
	char	*path_env;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (check_direct_path(cmd));
	path_env = get_env_value(envp, "PATH");
	if (!path_env)
		return (NULL);
	return (search_in_path(cmd, path_env));
}
