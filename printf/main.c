#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>


int		tn_puthex(unsigned long nb, const char *base);
int	tn_putchar(int c);
int	tn_putstr(char *str);
int		ft_printf(const char *str, ...);
int		tn_putnbr(int	nbr);
int		tn_putp(unsigned long long p);

int	main(void)
{
	printf("%d\n", ft_printf("%s |%c |%d |%i |%x |%p\n", "Hello", 'c', 2147483647, -2147483648, 10, &main));
	printf("%d\n", printf("%s |%c |%d |%i |%x |%p\n", "Hello", 'c', 2147483647, -2147483648, 10, &main));
}
int	tn_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	tn_putstr(char *str)
{
	int		i;

	i = 0;
	while (*str)
	{
		write(1, str++, 1);
		i++;
	}
	return (i);
}

int		put_format(char s, va_list va)
{
	int	len;

	len = 0;
	if (s == 'c')
	{
		len += tn_putchar(va_arg(va, int));
	}
	else if (s == 's')
	{
		len += tn_putstr(va_arg(va, char *));
	}
	else if (s == 'd' || s == 'i')
		len += tn_putnbr(va_arg(va, int));
	else if (s == 'x')
		len += tn_puthex(va_arg(va, unsigned long), "0123456789abcdef");
	else if (s == 'X')
		len += tn_puthex(va_arg(va, unsigned long), "0123456789ABCDEF");
	else if (s == 'p')
		len += tn_putp(va_arg(va, unsigned long));

	return (len);
}

int		tn_putp(unsigned long long p)
{
	int	len;

	len = 0;
	if (p == 0)
	{
		len = tn_putstr("(null)");
	}
	else
	{
		len = tn_putstr("0x");
		len += tn_puthex(p, "0123456789abcdef");
	}
	return (len);
}

int		tn_puthex(unsigned long nb, const char *base)
{
	int		len;

	len = 0;
	if (nb >= 16)
	{
		len += tn_puthex(nb / 16, base);
		len += tn_putchar(base[nb % 16]);
	}
	else
	{
		len += tn_putchar(base[nb % 16]);
	}
}

int		tn_putnbr(int	nbr)
{
	int	len;
	int	sign;

	sign = 1;
	len = 0;
	if (nbr == -2147483648)
	{
		return (tn_putstr("-2147483648"));
	}
	if (nbr < 1)
	{
		nbr = -nbr;
		tn_putchar('-');
		len = 1;
	}
	if (nbr >= 10)
	{
		len += tn_putnbr(nbr / 10);
		len += tn_putchar(nbr % 10 + '0');
	}
	else
	{
		len += tn_putchar(nbr % 10 + '0');
	}
	return (len);
}

int		ft_printf(const char *str, ...)
{
	int		len;
	int		i;
	va_list va;

	if (!str)
		return (0);
	len  = 0;
	i = 0;
	va_start(va, str);
	while(str[i])
	{
		if (str[i] == '%')
		{
			len += put_format(*(str + i + 1), va);
			i++;
		}
		else
		{
			len += tn_putchar(*(str + i));
		}
		i++;
	}
	return (len);
}
