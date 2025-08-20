NAME        = minishell
SRCS        = srcs/main.c srcs/signals.c srcs/env.c srcs/prompt.c srcs/utils.c
OBJS        = $(SRCS:.c=.o)
INCLUDES	= includes

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
IFLAGS     = -I$(INCLUDES) -I$(LIBFT_DIR)

RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(LIBFT_DIR)/ft_printf/libftprintf.a

LIBS     = -lreadline -lncurses

all: $(NAME)

$(LIBFT):          ;  @$(MAKE) -C $(LIBFT_DIR)
$(FT_PRINTF):      ;  @$(MAKE) -C $(LIBFT_DIR)/ft_printf

$(NAME): $(OBJS) | $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(FT_PRINTF) $(LIBS)

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
