/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marleand <marleand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:58:19 by marleand          #+#    #+#             */
/*   Updated: 2024/11/29 14:58:19 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counter(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;

	len = ft_counter(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	result = (malloc(sizeof(char) * (len + 1)));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	else if (n == 0)
		result[0] = '0';
	while (n != 0 && len-- > 0)
	{
		result[len] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}
/*#include "stdio.h"
int	main(void)
{
    char *result = ft_itoa(123);
    if (result)
    {
        printf("ft_itoa(123) = %s\n", result);
        free(result);
    }
    return (0);
}*/