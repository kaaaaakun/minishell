# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhino <hhino@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 16:08:51 by tokazaki          #+#    #+#              #
#    Updated: 2023/09/07 20:09:41 by tokazaki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Files & Command +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
SRCS_DIR = srcs
OBJS_DIR = objs
OPERARIONS_DIR = operations
BUILTIN_DIR = builtin
INCLUDES =  -I./libft-puls -I./srcs -I $(RL_DIR)/include

RL_DIR = $(shell brew --prefix readline)

SRCS = $(addprefix $(SRCS_DIR)/, \
		main.c \
		add_sigaction.c \
		execve.c \
		list.c \
		utils.c \
		debug.c \
		pipex_utils.c \
		$(addprefix builtin/, \
			exit.c \
			echo.c \
			cd.c \
			pwd.c \
			env.c \
			export.c \
			unset.c \
			) \
		$(addprefix lexar_panda/, \
			make_env_list.c \
			replace_env.c \
			lexar_panda.c \
			heredoc.c \
			make_list.c \
			make_stack.c \
			chck_flag_error.c \
			getpath.c \
			) \
		)

OBJS = $(SRCS:.c=.o)

CC		= cc
OFLAGS  = -Wall -Wextra -Werror $(INCLUDES)
CFLAGS  = -Wall -Wextra -Werror $(INCLUDES)
RM		= rm -f

# Libft & Debug +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
LIBFT_DIR	=	libft-puls
LIBFT		=	$(LIBFT_DIR)/libft.a

DEBUG			= debug

ifdef WITH_DEBUG
	CFLAGS += -g -O0 -fsanitize=address
endif

# Mandatory target ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
.PHONY: all clean fclean re

all: $(NAME)

.c.o:
	@ $(CC) $(OFLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -lreadline $(CFLAGS) $(LIBFT) -o $@ -L $(RL_DIR)/lib 
	@ echo "compiled!"
#	make clean

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
$(DEBUG):
	make WITH_DEBUG=1

$(LIBFT):
	make bonus -C $(LIBFT_DIR) all -lreadline

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
