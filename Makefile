NAME        = minishell
SRCS        = srcs/main.c srcs/signals.c srcs/env.c srcs/prompt.c srcs/utils.c srcs/arena.c \
				srcs/arena_utils.c srcs/builtins/dispatch.c srcs/builtins/mini_cd.c \
				srcs/builtins/mini_echo.c srcs/builtins/mini_env.c srcs/builtins/mini_exit.c \
				srcs/builtins/mini_export.c srcs/builtins/mini_pwd.c srcs/builtins/mini_unset.c
OBJS = $(patsubst srcs/%.c, $(O_DIR)/%.o,$(SRCS))
O_DIR = objects
INCLUDES	= includes

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
IFLAGS     = -I$(INCLUDES) -I$(LIBFT_DIR)

RM = rm -f                                                                 

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(LIBFT_DIR)/ft_printf/libftprintf.a

LIBS = -lreadline -lncurses

all: $(NAME)

$(LIBFT):
		@make -C $(LIBFT_DIR)

$(FT_PRINTF):
		@make -C $(LIBFT_DIR)/ft_printf

$(NAME): $(LIBFT) $(FT_PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) $(LIBS) -o $(NAME)

$(O_DIR):
		@mkdir -p $@

$(O_DIR)/%.o: srcs/%.c $(INCLUDES)/*.h | $(O_DIR)
		$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
		@rm -rf $(O_DIR)
		@make fclean -C $(LIBFT_DIR)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re