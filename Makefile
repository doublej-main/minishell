NAME        = minishell
SRCS        = srcs/main.c srcs/signals.c srcs/env.c srcs/prompt.c
OBJS        = $(SRCS:.c=.o)
INCLUDES	= includes

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
IFLAGS     = -I$(INCLUDES) -I$(LIBFT_DIR)

RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

LIBS     = -lreadline -lncurses

all: $(NAME)

$(LIBFT):          ;  @$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) | $(LIBFT)
	$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBS)

%.o: %.c $(INCLUDES)/*.h
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)     clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR)     fclean

re: fclean all

.PHONY: all clean fclean re
