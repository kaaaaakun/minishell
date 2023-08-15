/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:58:06 by tokazaki          #+#    #+#             */
/*   Updated: 2023/06/22 18:26:17 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

static ssize_t	ft_putnbr(size_t c, int fd, char *base, size_t base_len);

//値の処理の流れ
//pointerの場合：ftp_put_pointer -> ftp_putnbr_base ->ft_putnbr
//そのほかの値：ftp_putnbr_base ->ft_putnbr

ssize_t	ftp_put_pointer(uintptr_t c, int fd, char *base)
{
	ssize_t	count;
	ssize_t	tmp;

	count = write(fd, "0x", 2);
	tmp = ft_putnbr(c, fd, base, 16);
	if (tmp == -1 || count == -1)
		return (-1);
	return (count + tmp);
}

ssize_t	ftp_putnbr_base(long long int c, int fd, char *base, int flag)
{
	int		count;
	int		base_len;
	ssize_t	tmp;

	count = 0;
	base_len = ft_strlen(base);
	if (flag == 1)
		c = (unsigned int)c;
	if (c < 0)
	{
		count += write (fd, "-", 1);
		c = c * -1;
	}
	tmp = ft_putnbr(c, fd, base, base_len);
	if (tmp == -1 || count == -1)
		return (-1);
	return (count + tmp);
}
//baseは都度指定
//flag == 1の場合はunsigned
//put_nbrの引数がマイナスにならないように処理

static ssize_t	ft_putnbr(size_t c, int fd, char *base, size_t base_len)
{
	int		count;
	ssize_t	tmp;

	count = 0;
	if (0 <= c && c <= base_len - 1)
		tmp = write(fd, &base[c], 1);
	else
	{
		count = ft_putnbr (c / base_len, fd, base, base_len);
		tmp = write(fd, &base[c % base_len], 1);
	}
	if (tmp == -1 || count == -1)
		return (-1);
	return (count + tmp);
}
