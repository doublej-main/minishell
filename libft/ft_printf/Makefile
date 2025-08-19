NAME = libftprintf.a

SRCS = conv_char.c conv_int.c conv_ptr.c conv_str.c conv_uint.c \
		ft_hextoa.c ft_numlen.c ft_printf.c ft_putchar.c ft_putnbr.c \
		ft_putstr.c ft_strlen.c conv_hexlow.c conv_hexup.c ft_uintlen.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
		ar rcs $(NAME) $(OBJECTS)

clean:
		rm -f $(OBJECTS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean bonus