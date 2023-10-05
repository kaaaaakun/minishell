# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhino <hhino@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 16:08:51 by tokazaki          #+#    #+#              #
#    Updated: 2023/10/05 15:48:58 by tokazaki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Files & Command +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
SRCS_DIR = srcs
OBJS_DIR = objs
RL_DIR = $(shell brew --prefix readline)

SRCS = $(addprefix $(SRCS_DIR)/, \
		main.c \
		panda_to_builtin.c \
		add_sigaction.c \
		list.c \
		utils.c \
		debug.c \
		pipex_utils.c \
		pipex_utils2.c \
		$(addprefix builtin/, \
			exit.c \
			echo.c \
			execve.c \
			cd.c \
			pwd.c \
			env.c \
			export.c \
			export_utils.c \
			unset.c \
			) \
		$(addprefix lexer_panda/, \
			make_env_list.c \
			make_list.c \
			lexer_panda.c \
			make_stack.c \
			chck_flag_error.c \
			getpath.c \
			panda_utils.c \
			redirection_operators.c \
			mini_libft.c \
			) \
		)
OBJS = $(SRCS:.c=.o)

CC		= cc
CFLAGS  = -Wall -Wextra -Werror -g
INCLUDE = -I ./libft-puls -I ./srcs -I $(RL_DIR)/include
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
	make bonus -C $(LIBFT_DIR) all

#debug:
debug:
	make WITH_DEBUG=1

del:
	rm -rf .tmp*
	rm -rf out*
	find . -name "*.o" -exec rm {} +
	find . -name "*.un~" -exec rm {} +
	find . -name "*.back" -exec rm {} +

leaks:
	while [ 1 ]; do leaks -q minishell; sleep 2; done
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
