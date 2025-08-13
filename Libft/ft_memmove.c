/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marleand <marleand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:59:03 by marleand          #+#    #+#             */
/*   Updated: 2024/11/29 14:59:03 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dest1;
	const char	*src1;

	dest1 = (char *)dest;
	src1 = (const char *)src;
	i = -1;
	if (!dest && !src)
		return (NULL);
	if (dest1 < src1)
	{
		while (++i < n)
			dest1[i] = src1[i];
	}
	else
	{
		i = n;
		while (i--)
			dest1[i] = src1[i];
	}
	return (dest);
}
