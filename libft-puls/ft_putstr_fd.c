/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:52:24 by tokazaki          #+#    #+#             */
/*   Updated: 2023/06/21 11:33:34 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ftp_putstr_fd(char *s, int fd)
{
	if (!s)
		return (write (fd, "(null)", 6));
	return (write (fd, s, ft_strlen(s)));
}

ssize_t	ftp_putchar_fd(int c, int fd)
{
	char	chr;

	chr = (char)c;
	return (write (fd, &chr, 1));
}
