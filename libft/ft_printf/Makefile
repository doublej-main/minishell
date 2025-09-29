# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/08 11:31:56 by vahdekiv          #+#    #+#              #
#    Updated: 2025/05/08 11:53:33 by vahdekiv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
COMPILER = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_printf.c printf_hex.c printf_utils.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "removing objects"

fclean: clean
	@rm -f $(NAME)
	@echo "removing executable file"

re: fclean all

.PHONY: all clean fclean re
