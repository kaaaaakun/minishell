NAME = libft.a

SRCS =	ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memchr.c \
		ft_memmove.c \
		ft_memcmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c\
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		get_next_line_bonus.c \
		ft_printf.c \
		ftp_putnbr_fd.c \
		ftp_putstr_fd.c \
		ft_str_is_num.c
B_SRCS=	ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
	 	ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

OBJS = $(SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)
OBJS += $(B_OBJS)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar rcs

ifdef WITH_DEBUG
	CFLAGS += -D PRINTF_DEBUG=1
endif

ifdef MALLOC_DEBUG
	CFLAGS += -D PRINTF_DEBUG=1 -D MALLOC_DEBUG=1
endif

all: $(NAME)

$(NAME): $(OBJS)
	@ $(AR) $(NAME) $(OBJS)
	@ echo "libft+ compiled!"

.c.o:
	@ $(CC) $(CFLAGS) -c $< -o $@

clean:
	@ $(RM) $(OBJS) $(B_OBJS)

fclean: clean
	@ $(RM) $(NAME)

debug:
	make WITH_DEBUG=1

malloc:
	make MALLOC_DEBUG=1

re: fclean all
