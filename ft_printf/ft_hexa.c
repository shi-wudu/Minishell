/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marleand <marleand@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/01/04 19:31:22 by marleand          #+#    #+#             */
/*   Updated: 2025/01/04 19:31:22 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa(int flag, unsigned long n, char *base)
{
	char	buffer[16];
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (n == 0 && flag == 1)
		return (ft_putstr("(nil)"));
	if (flag == 1)
		count = ft_putstr("0x");
	if (flag == 0 && n == 0)
		buffer[i++] = base[n % 16];
	while (n > 0)
	{
		buffer[i++] = base[n % 16];
		n /= 16;
	}
	while (--i >= 0)
		count += ft_putchar(buffer[i]);
	return (count);
}
