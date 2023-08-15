/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:12:57 by tokazaki          #+#    #+#             */
/*   Updated: 2023/06/21 20:02:05 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include <unistd.h>
# include <inttypes.h>

int		ft_printf(const char *format, ...);

ssize_t	ftp_putchar_fd(int c, int fd);
ssize_t	ftp_putstr_fd(char *s, int fd);
ssize_t	ftp_putnbr_base(long long int c, int fd, char *base, int flag);
ssize_t	ftp_put_pointer(uintptr_t c, int fd, char *base);

size_t	ft_strlen(const char *src);

#endif
