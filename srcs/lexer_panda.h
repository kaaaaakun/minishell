/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_panda.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:53:38 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/27 13:19:40 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_MANDA_H
# define LEXER_MANDA_H

# include "minishell.h"

// define flag
# define INITIAL 0x000
# define AT_PIPE 0x001
# define COMMAND 0x002

# define D_QUOTE 0x004
# define S_QUOTE 0x008
# define IN_QUOTE S_QUOTE + D_QUOTE

# define INPUT_REDIRECT 0x010
# define HEREDOC 0x020
# define OUTPUT_REDIRECT 0x040
# define APPENDDOC 0x080
# define NEED_FILE INPUT_REDIRECT + HEREDOC + OUTPUT_REDIRECT + APPENDDOC

# define ERROR 0x200
# define NOFLAG 0x400

// define ft_strjoin_free
# define BOTH_FREE 0
# define FIRST_FREE 1
# define SECOND_FREE 2
# define NEITHER_FREE 3

//make_list
char	*make_tmp_file(t_info *status, int *tmp_fd);
void	ex_heredoc(t_info *status, char *eof_word, int tmp_fd);
char	*check_command_path(t_info *status, char *result);
char	*check_flag(t_info *status, char *result, int *flag);
void	*mini_memcpy(void *dst, const void *src, size_t n);
char	*mini_substr(char const *s, unsigned int start, size_t len);
int		search_dollar(char *line);
char	*make_list(int *flag, char *line, int len, t_list **list);
//redirection_operators
void	check_infile(t_info *status, char *result);
char	*check_heredoc(t_info *status, char *eof_word);
void	check_outfile(t_info *status, char *result);
void	check_appendfile(t_info *status, char *result);
//
char	*search_env(t_info *status, char *str);
t_list	*search_envlist(t_info *status, char *str);
void	lexer_panda_error_check(int *flag, t_info *status);
t_stack	*make_stack(t_info *status, t_stack *pre_data);
char	*check_flag(t_info *status, char *result, int *flag);
char	*mini_substr(char const *s, unsigned int start, size_t len);

// utils
void	free_null(void *ptr);
void	minun_quote(char s, int *flag);
void	plusle_quote(char s, int *flag);
char	*ft_strjoin_free(char const *s1, char const *s2, int free_flag);
char	*ft_strtrim_free(char const *s1, char const *s2, int free_flag);

#endif
