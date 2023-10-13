# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 16:08:51 by tokazaki          #+#    #+#              #
#    Updated: 2023/10/13 20:16:21 by tokazaki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Files & Command +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
SRCS_DIR = srcs
OBJS_DIR = objs
RL_DIR = $(shell brew --prefix readline)

SRCS = \
	   srcs/debug.c \
	srcs/panda_to_builtin.c \
	srcs/pipex_utils2.c \
	srcs/utils.c \
	srcs/utils_find_token.c \
	srcs/add_sigaction.c \
	srcs/utils_dup2_close.c \
	srcs/list.c \
	srcs/builtin/execve.c \
	srcs/builtin/echo.c \
	srcs/builtin/export.c \
	srcs/builtin/execve_error_mssage.c \
	srcs/builtin/pwd.c \
	srcs/builtin/execve_error_check.c \
	srcs/builtin/exit.c \
	srcs/builtin/unset.c \
	srcs/builtin/env.c \
	srcs/builtin/cd.c \
	srcs/builtin/export_utils.c \
	srcs/lexer_panda/ex_heredoc.c \
	srcs/lexer_panda/panda_pre_check.c \
	srcs/lexer_panda/chck_flag_error.c \
	srcs/lexer_panda/make_operation.c \
	srcs/lexer_panda/make_cmdlist.c \
	srcs/lexer_panda/make_env_list.c \
	srcs/lexer_panda/chck_dollar.c \
	srcs/lexer_panda/count_operations.c \
	srcs/lexer_panda/lexer_panda.c \
	srcs/lexer_panda/env_variable.c \
	srcs/lexer_panda/panda_process_operation.c \
	srcs/lexer_panda/make_stack.c \
	srcs/lexer_panda/panda_utils_quote.c \
	srcs/lexer_panda/mini_libft.c \
	srcs/lexer_panda/getpath.c \
	srcs/lexer_panda/redirection_operators.c \
	srcs/lexer_panda/process_input_count.c \
	srcs/lexer_panda/make_list.c \
	srcs/lexer_panda/panda_some_pipes.c \
	srcs/pipex_utils.c \
	srcs/utils_malloc.c \
	srcs/main.c

OBJS = $(SRCS:.c=.o)

CC		= cc
CFLAGS  = -Wall -Wextra -Werror -g
INCLUDE = -I ./libft-puls -I ./includes -I $(RL_DIR)/include
LDFLAGS	= -lreadline -L $(RL_DIR)/lib
RM		= rm -f

# Libft & Debug +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
LIBFT_DIR	=	libft-puls
LIBFT		=	$(LIBFT_DIR)/libft.a

ifdef WITH_DEBUG
	CFLAGS += -g -O0 -fsanitize=address
endif

# Mandatory target ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
.PHONY: all clean fclean re debug

all: $(NAME)

.c.o:
	@ $(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(INCLUDE) $(LDFLAGS) $(CFLAGS) $(LIBFT) -o $@
	@ echo "compiled!"

clean:
	@ make -C $(LIBFT_DIR) clean
	@ $(RM) $(OBJS) #$(B_OBJS)
	@ echo "cleaned!"

fclean: clean
	@ make -C $(LIBFT_DIR) fclean
	@ $(RM) $(NAME)
	@ echo "all cleaned!"

re: fclean all

# Other target ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
$(LIBFT):
	make  -C $(LIBFT_DIR) all

#debug:
debug:
	make fclean
	make debug -C $(LIBFT_DIR)
	make all

malloc:
	make fclean
	make malloc -C $(LIBFT_DIR)
	make all

clash:
	make WITH_DEBUG=1

clang:
	clang --analyze $(SRCS) $(INCLUDE)

del:
	rm -rf .tmp*
	rm -rf out*
	rm -rf *.plist
	find . -name "*.o" -exec rm {} +
	find . -name "*.un~" -exec rm {} +
	find . -name "*.back" -exec rm {} +

leaks:
	while [ 1 ]; do leaks -q minishell; sleep 2; done
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
