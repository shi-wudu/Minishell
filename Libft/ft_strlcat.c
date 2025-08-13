/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marleand <marleand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:00:09 by marleand          #+#    #+#             */
/*   Updated: 2024/11/29 15:00:09 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	sizeofdstfinal;
	size_t	sizeofsrc;
	size_t	sizeofdst;

	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	sizeofdst = ft_strlen(dst);
	sizeofsrc = ft_strlen(src);
	sizeofdstfinal = sizeofdst;
	if (dstsize <= sizeofdst)
		return (dstsize + sizeofsrc);
	while (sizeofdst < dstsize - 1 && *src)
		dst[sizeofdst++] = *src++;
	dst[sizeofdst] = '\0';
	return (sizeofdstfinal + sizeofsrc);
}

/*size_t	fstrlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	a;

	a = 0;
    printf("dst = %s\nsrc = %s\n", dst, src);
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstsize <= dstlen)
		return (dstsize + srclen);
	while (dst[a] != '\0')
		a++;
	while (a < dstsize - 1 && *src)
	{
		dst[a] = *src;
		src++;
		a++;
	}
	dst[a] = '\0';
	return (dstlen + srclen);
}

int	main(void)
{
    char str[12] = "ola";
    char str1[12] = "bom dia";
    char str2[12] = "ola";
    char str3[12] = "bom dia";
    size_t returne = 0;
    size_t return1 = 0;

    returne = ft_strlcat(str, str1, 12);
    printf("my String: %s\nmy Return:%ld\n", str, returne);
    return1 = fstrlcat(str2, str3, 12);
    printf("String: %s\n Return:%ld\n", str2, return1);
    return (0);
}*/