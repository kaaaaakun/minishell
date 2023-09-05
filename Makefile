# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhino <hhino@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 16:08:51 by tokazaki          #+#    #+#              #
#    Updated: 2023/09/05 18:18:51 by tokazaki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Files & Command +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
SRCS_DIR = srcs
OPERARIONS_DIR = operations
OBJS_DIR = objs
BUILTIN_DIR = builtin

SRCS = $(addprefix $(SRCS_DIR)/, \
		main.c \
		add_sigaction.c \
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
		execve.c \
		list.c \
		debug.c \
		pipex_utils.c \
		)

OBJS = $(SRCS:.c=.o)
# OBJS	= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

CC		= cc
CFLAGS  = -I./libft-puls -I./srcs
CFLAGS	+= -Wall -Wextra -Werror
# CFLAGS	+= -g -fsanitaze=address
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
	@ $(CC) $(CFLAGS) -o $@ -c $< -I $(brew --prefix readline)/include

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -lreadline $(CFLAGS) $(LIBFT) -o $@
	@ echo "compiled!"
	make clean

clean:
	@ make -C $(LIBFT_DIR) clean
	@ $(RM) $(OBJS) $(B_OBJS)
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
