/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-30 17:53:14 by user              #+#    #+#             */
/*   Updated: 2025-11-30 17:53:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args)
{
    char	**temp;

    temp = args;
    if (!args)
        return ;
    while (*temp)
    {
        free(*temp);
        temp++;
    }
    free(args);
}
 
