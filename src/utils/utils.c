/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:52 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/20 13:18:52 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errmsg(const char *msg, const char *arg, bool newline)
{
	write(2, msg, strlen(msg));
	if (arg)
	{
		write(2, ": ", 2);
		write(2, arg, strlen(arg));
	}
	if (newline)
		write(2, "\n", 1);
}

int	ft_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
