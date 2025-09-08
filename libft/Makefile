# ---------------------------------------------------- #
#                   libft  Makefile                    #
# ---------------------------------------------------- #

# -------- library names ------------------------------
NAME        := libft.a
FT_PRINTF   := ft_printf/libftprintf.a

# -------- source lists -------------------------------
SRCS  := \
	ft_isalpha.c  ft_isdigit.c  ft_isalnum.c  ft_isascii.c ft_isprint.c \
	ft_strlen.c   ft_memset.c  ft_bzero.c    ft_memcpy.c  ft_memmove.c \
	ft_strlcpy.c  ft_strlcat.c ft_toupper.c  ft_tolower.c ft_strchr.c  \
	ft_strrchr.c  ft_strncmp.c ft_memchr.c   ft_memcmp.c  ft_strnstr.c \
	ft_atoi.c     ft_calloc.c  ft_strdup.c   ft_substr.c  ft_strjoin.c \
	ft_strtrim.c  ft_split.c   ft_itoa.c     ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c \
	ft_trimchar.c ft_isnum.c

BSRCS := \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c

OBJS := $(SRCS:.c=.o) $(BSRCS:.c=.o)

CC      := cc
CFLAGS  := -Wall -Wextra -Werror
AR      := ar
ARFLAGS := rcs
RM      := rm -f

all: $(NAME)

$(FT_PRINTF):
	$(MAKE) -C ft_printf

$(NAME): $(OBJS) | $(FT_PRINTF)
	$(AR) $(ARFLAGS) $@ $(OBJS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C ft_printf clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
