/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:29:26 by tokazaki          #+#    #+#             */
/*   Updated: 2023/06/13 14:07:39 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4242
# endif

//char	*ft_substr(char const *s, unsigned int start, size_t len);
//char	*ft_strchr(const char *s, int i);
//char	*ft_strdup(const char *s);
//char	*ft_strjoin(char const *s1, char const *s2);
//size_t	ft_strlen(const char *src);

char	*get_next_line(int fd);
#endif
