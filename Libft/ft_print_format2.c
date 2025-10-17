#include "libft.h"

int ft_print_unsigned(unsigned int n)
{
    char digit;
    int count;

    count = 0;
    if (n > 9)
        count += ft_print_unsigned(n / 10); 
    digit = (n % 10) + '0';
    count += write(1, &digit, 1);
    return count;
}

int ft_print_hex(unsigned int num, int uppercase)
{
    char *base;
    char digit;
    int count;

    count = 0;
    if (uppercase == 1)
        base = "0123456789ABCDEF";
    else
        base = "0123456789abcdef";
    if (num > 15)
        count += ft_print_hex(num / 16, uppercase);
    digit = base[num % 16];
    count += write(1, &digit, 1);
    return count;
}