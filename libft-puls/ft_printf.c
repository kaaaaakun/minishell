/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:16:19 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/12 19:22:10 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#ifndef PRINTF_DEBUG
# define PRINTF_DEBUG 0
#endif

static ssize_t	check_format(int fd, const char *fmt, va_list ap);
static ssize_t	d_check_format(int fd, const char *fmt, va_list ap);

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	ssize_t	count;
	ssize_t	count_tmp;
	int		fd;

	fd = STDOUT_FILENO;
	count = 0;
	va_start (ap, format);
	if (!format)
		return (-1);
	while (*format != '\0')
	{
		if (*format == '%')
			count_tmp = check_format(fd, ++format, ap);
		else
			count_tmp = write (fd, format, 1);
		if (count_tmp < 0 || INT_MAX < count + count_tmp)
			break ;
		count += count_tmp;
		format++;
	}
	va_end (ap);
	if (count_tmp < 0 || INT_MAX < count + count_tmp)
		return (-1);
	return (count);
}
//writeを失敗した場合には必ず-1が戻り値になり、即座に処理が終了
//%の後ろに適切な記号がなければ、-1を返して、即座に処理が終了
//返り値がINT_MAXを超えたら即座に-1を返して、即座に処理が終了
//fdを変更できるような実装に変更
//進数に関しては必要箇所でそれぞれ定義

//error出力用
int	error_printf(const char *format, ...)
{
	va_list	ap;
	ssize_t	count;
	ssize_t	count_tmp;
	int		fd;

	fd = 2;
	count = 0;
	va_start (ap, format);
	if (!format)
		return (-1);
	while (*format != '\0')
	{
		if (*format == '%')
			count_tmp = check_format(fd, ++format, ap);
		else
			count_tmp = write (fd, format, 1);
		if (count_tmp < 0 || INT_MAX < count + count_tmp)
			break ;
		count += count_tmp;
		format++;
	}
	va_end (ap);
	if (count_tmp < 0 || INT_MAX < count + count_tmp)
		return (-1);
	return (count);
}

//debug用
int	d_printf(const char *format, ...)
{
	va_list	ap;
	ssize_t	count;
	ssize_t	count_tmp;

	if (PRINTF_DEBUG == 0)
		return (0);
	error_printf("\x1b[38;5;229m");
	count = 0;
	va_start (ap, format);
	if (!format)
		return (-1);
	while (*format != '\0')
	{
		if (*format == '%')
			count_tmp = d_check_format(2, ++format, ap);
		else
			count_tmp = write (2, format, 1);
		if (count_tmp < 0 || INT_MAX < count + count_tmp)
			break ;
		count += count_tmp;
		format++;
	}
	va_end (ap);
	error_printf("\x1b[0m");
	return (count);
}

static ssize_t	d_check_format(int fd, const char *fmt, va_list ap)
{
	if (*fmt == '%')
		return (write(fd, "%", 1));
	else if (*fmt == 'c')
		return (ftp_putchar_fd (va_arg(ap, int), fd));
	else if (*fmt == 'p')
		return (ftp_put_pointer(va_arg(ap, uintptr_t), fd, "0123456789abcdef"));
	else if (*fmt == 's')
		return (ftp_putstr_fd (va_arg(ap, char *), fd));
	else if (*fmt == 'd' || *fmt == 'i')
		return (ftp_putnbr_base(va_arg(ap, int), fd, "0123456789", 0));
	else if (*fmt == 'u')
		return (ftp_putnbr_base(va_arg(ap, unsigned int), fd, "0123456789", 1));
	else if (*fmt == 'x')
		return (ftp_putnbr_base(va_arg(ap, unsigned int) \
					, fd, "0123456789abcdef", 1));
	else if (*fmt == 'X')
		return (ftp_putnbr_base(va_arg(ap, unsigned int) \
					, fd, "0123456789ABCDEF", 1));
	else
		return (-1);
}

static ssize_t	check_format(int fd, const char *fmt, va_list ap)
{
	if (*fmt == '%')
		return (write(fd, "%", 1));
	else if (*fmt == 'c')
		return (ftp_putchar_fd (va_arg(ap, int), fd));
	else if (*fmt == 's')
		return (ftp_putstr_fd (va_arg(ap, char *), fd));
	else if (*fmt == 'b')
		return (ftp_put_pointer(va_arg(ap, uintptr_t), fd, "01"));
	else if (*fmt == 'p')
		return (ftp_put_pointer(va_arg(ap, uintptr_t), fd, "0123456789abcdef"));
	else if (*fmt == 'd' || *fmt == 'i')
		return (ftp_putnbr_base(va_arg(ap, int), fd, "0123456789", 0));
	else if (*fmt == 'u')
		return (ftp_putnbr_base(va_arg(ap, unsigned int), fd, "0123456789", 1));
	else if (*fmt == 'x')
		return (ftp_putnbr_base(va_arg(ap, unsigned int) \
					, fd, "0123456789abcdef", 1));
	else if (*fmt == 'X')
		return (ftp_putnbr_base(va_arg(ap, unsigned int) \
					, fd, "0123456789ABCDEF", 1));
	else
		return (-1);
}
