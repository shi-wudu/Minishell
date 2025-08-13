/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marleand <marleand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:58:57 by marleand          #+#    #+#             */
/*   Updated: 2024/11/29 14:58:57 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest1;
	const char	*src1;

	dest1 = dest;
	src1 = src;
	if (!dest && !src)
		return (NULL);
	while (n--)
	{
		*dest1 = *src1;
		dest1++;
		src1++;
	}
	return (dest);
}
