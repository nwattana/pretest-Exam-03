#include <stdarg.h>
#include <unistd.h>

#include <stdio.h>

// cspdiuxX%


int    putchar_fd(int a, int fd)
{
    return (write(fd, &a, 1));
}

int    putstr_fd(const char *str, int fd)
{
    int  i;

    i = 0;
    if (fd < 0)
        return (0);
    while (*(str + i))
        write(fd, str + i++, 1);
    return (i);
}

int putnbr(int a)
{
    int len;
    int sign;

    sign = 1;
    len = 0;
    if (a == -2147483648)
        return (len = putstr_fd("-2147483648", 1));
    if (a < 0)
    {
        len += putstr_fd("-", 1);
        a = -a;
    }
    if (a >= 10)
    {    
        len += putnbr(a / 10);
        len += putchar_fd((a % 10) + '0', 1);
        return (len);
    }
    else
        return (putchar_fd(a % 10 + '0', 1));
}

int put_nbr_h(unsigned long long val, const char *base)
{
    int len;

    len = 0;
    if (val >= 16)
    {
        len += put_nbr_h(val / 16, base);
        return (len += putchar_fd(base[val % 16], 1));
    }
    else
        return (len += putchar_fd(base[val % 16], 1));
}

int put_nbr_p(unsigned long long val, const char *base)
{
    int len;

    if (val == 0)
        return (putstr_fd("(NULL)", 1));
    len = putstr_fd("0x", 1);
    if (val >= 16)
    {
        len += put_nbr_h(val / 16, base);
        return (len += putchar_fd(base[val % 16], 1));
    }
    else
        return (len += putchar_fd(base[val % 16], 1));
}

int do_format(va_list va, char *str)
{
    if (*str == 'd' || *str == 'i')
        return (putnbr(va_arg(va, int)));
    if (*str == 's')
        return (putstr_fd(va_arg(va, char *), 1));
    if (*str == 'c')
        return (putchar_fd(va_arg(va, int), 1));
    if (*str == '%')
        return (putchar_fd('%', 1));
    if (*str == 'x')
        return (put_nbr_h(va_arg(va, unsigned int), "0123456789abcdef"));
    if (*str == 'X')
        return (put_nbr_h(va_arg(va, unsigned int), "0123456789ABCDEF"));
    if (*str == 'p')
        return (put_nbr_p(va_arg(va, unsigned long long), "0123456789abcdef"));
    else
        return (0);
}

int do_print(char *str, va_list va)
{
    int     len;

    len = 0;
    while (*str != '\0')
    {
        if (*str == '%' && str + 1 != NULL && *(str + 1) != '\0')
            len += do_format(va, ++str);
        else
            len += putchar_fd(*str, 1);
        str++;
    }
    return (len);
}

int ft_printf(const char *str, ...)
{
    va_list va;
    char *ftm;
    int len;
    ftm = (char *)str;
    if (ftm == NULL)
        return (-1);
    va_start(va, str);
    len = do_print(ftm, va);
    va_end(va);
}



int main(void)
{
    char    *s;
    char c='*';

    s = &c;
    // printf("test = %d\n",ft_printf("Hello World!\n"));
    // printf("test = %d\n",printf("Hello World!\n"));
    printf("=======\n");
    printf("test = %d\n\n",ft_printf("Hello World! %c |%s %X %d %p\n",42, "test", 2147483647, 10, s));
    printf("test = %d\n\n",printf("Hello World! %c |%s %X %d %p\n",42, "test", 2147483647, 10, s));
    printf("=======\n");
}
