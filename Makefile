# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhino <hhino@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 16:08:51 by tokazaki          #+#    #+#              #
#    Updated: 2023/09/18 13:21:04 by hhino            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Files & Command +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
SRCS_DIR = srcs
OBJS_DIR = objs
RL_DIR = $(shell brew --prefix readline)

SRCS = $(addprefix $(SRCS_DIR)/, \
		main.c \
		add_sigaction.c \
		list.c \
		utils.c \
		debug.c \
		pipex_utils.c \
		$(addprefix builtin/, \
			cd.c \
			echo.c \
			env.c \
			execve.c \
			exit.c \
			export_utils.c\
			export.c \
			pwd.c \
			unset.c \
			) \
		$(addprefix lexer_panda/, \
			make_env_list.c \
			make_list.c \
			replace_env.c \
			lexer_panda.c \
			make_stack.c \
			chck_flag_error.c \
			getpath.c \
			) \
		)
OBJS = $(SRCS:.c=.o)

CC		= cc
CFLAGS  = -Wall -Wextra -Werror
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
	make clean

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

debug:
	make WITH_DEBUG=1

del:
	rm -rf .tmp*
	rm -rf in*
	rm -rf out*
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
