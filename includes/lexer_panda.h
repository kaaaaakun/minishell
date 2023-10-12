/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_panda.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:53:38 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/11 18:47:13 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PANDA_H
# define LEXER_PANDA_H

# include "minishell.h"

// define flag
# define INITIAL 0x000
# define AT_PIPE 0x001
# define COMMAND 0x002

# define D_QUOTE 0x004
# define S_QUOTE 0x008
# define IN_QUOTE 0x0C

# define INPUT_REDIRECT 0x010
# define HEREDOC 0x020
# define OUTPUT_REDIRECT 0x040
# define APPENDDOC 0x080
# define NEED_FILE 0xF0

# define ERROR 0x200
# define NOFLAG 0x400

// define pipe
# define PIPE_IN 0
# define PIPE_OUT 1

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
t_stack	*make_stack(t_info *status, t_stack *pre_data);
char	*check_flag(t_info *status, char *result, int *flag);
char	*mini_substr(char const *s, unsigned int start, size_t len);

// utils
int		analysis_char(char c);
pid_t	fork_ee(t_info *status);
void	close_pipe(t_info *status, int *pipefd);
void	dup2_close_pipe(t_info *status, int *pipefd, int flag);

//utils_malloc
void	free_null(void *ptr);
void	malloc_error(void);

//panda_pre_check
void	check_error(t_info *status, char *line, int *e_flag);
t_stack	*make_stack(t_info *status, t_stack *pre_data);

//error_check
void	lexer_panda_error_check(int *flag, t_info *status);

//env_variable
char	*check_dollar(t_info *status, char *line);
void	search_env_variable(char *line, int *i, int *flag);

//process_input_count.c
int		count_other_operation(t_info *status, char *line, int *flag, int value);
void	process_input_operation(t_info *status, char *line, int j, int *flag);

//???
void	minun_quote(char s, int *flag);
void	plusle_quote(char s, int *flag);

int		count_other_operation(t_info *status, char *line, int *flag, int value);
int		process_input_redirect_operation(t_info *status, char *line, int *flag);
int		process_output_redirect_operation(t_info *status, \
			char *line, int *flag);
int		check_pipe_operation(t_info *status, char *line, int *flag);
char	*process_dollar(t_info *status, char *result, int *i, int *flag);
int		count_input_heredoc(char *line, int i, int flag);

//make_operatinos_list
void	make_input_redirect(int *flag, char *line, int j, t_info *status);
void	make_append_list(int *flag, char *line, int j, t_info *status);
void	make_output_redirect(int *flag, char *line, int j, t_info *status);
void	make_heredoc_list(int *flag, char *line, int j, t_info *status);

//make_cmd_list
void	make_command_list(int *flag, char *line, int j, t_info *status);
void	make_other_list(int *flag, char *line, int j, t_info *status);

void	check_command(t_info *status, t_stack *data);
void	plusle_quote(char s, int *flag);
void	minun_quote(char s, int *flag);
char	*ft_strjoin_free(char const *s1, char const *s2, int free_flag);
char	*ft_strtrim_free(char const *s1, char const *set, int free_flag);
void	skip_space(char *post_word, int *i);

int		find_next_token(char *line, int i, int flag);
char	*process_single_dollar_in_d_quote(t_info *status, \
			char *line, int *i, char *result);
char	*process_single_double_dollar(t_info *status, \
			char *line, int *i, char *result);

int		count_pipe(t_info *status, char *line);
char	*search_and_append_env(t_info *status, \
			char *result, char *post_word, int *flag);
char	*append_non_quote_env(char *result, char *post_word);
int		count_input_heredoc(char *line, int i, int flag);
char	*make_first_space_splited_word(char *result, \
			char *post_word, int i, int j);
void	panda(char *line, t_info *status);
void	some_pipes_exec_panda(t_info *status, char *line, int flag, int i);
void	wait_child_process(t_info *status, pid_t pid);
void	exec_panda(char *line, t_info *status, int flag);
char	*mini_ft_strchr(const char *s, int c);
int		check_pipe_operation(t_info *status, char *line, int *flag);
int		process_pipe_operation(t_info *status, char *line, int *flag);
int		process_output_redirect_operation(t_info *status, \
			char *line, int *flag);
int		process_input_redirect_operation(t_info *status, char *line, int *flag);
t_stack	*search_last_stack(t_info *status);
int		process_quotes(char *line, int *value, int *i, int *flag);
int		check_and_count_pipe(t_info *status, char *line);
#endif
