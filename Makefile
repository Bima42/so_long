NAME = so_long

SRCS = 	so_long.c \
		check_error.c \
		parsing_map.c \
		clear.c \
		manage_window.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

SRCS_DIR = src

OBJS = $(SRCS:.c=.o)
OBJS_DIR = obj
DIRS = obj obj/get_next_line

_SRCS= $(addprefix $(SRCS_DIR)/, $(SRCS))
_OBJS = $(addprefix $(OBJS_DIR)/, $(OBJS))

HEADERS = src
MLX_DIR = mlx
LIBFT = libft.a
LIBFT_DIR = libft

CC = clang
CFLAGS = -Wall -Wextra -Werror -g -I $(HEADERS)
LFLAGS = $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -L $(MLX_DIR) #-fsanitize=address -g

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
    LFLAGS = $(CFLAGS) -lmlx -lXext -lX11 -lm -L $(MLX_DIR)
endif

all: $(NAME)

$(NAME): $(_OBJS)
	$(CC) $(_OBJS) $(LIBFT_DIR)/$(LIBFT) $(LFLAGS) -o $(NAME)

$(_OBJS): $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c $(DIRS) $(LIBFT_DIR)/$(LIBFT) mlx
	$(CC) -c $(CFLAGS) $< -o $@

$(LIBFT_DIR)/$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR) all
			$(MAKE) -C $(LIBFT_DIR) bonus
			cp $(LIBFT_DIR)/libft.h $(HEADERS)/libft.h

mlx:
			@echo "=========== Compiling MinilibX ==========="
			$(MAKE) -C $(MLX_DIR)
			cp $(MLX_DIR)/mlx.h $(HEADERS)/mlx.h
			@echo "========= End Compiling MinilibX ========="

mlx_clean:
			@echo "=========== Compiling MinilibX ==========="
			$(MAKE) -C $(MLX_DIR) clean
			rm $(HEADERS)/mlx.h
			@echo "========= End Compiling MinilibX ========="

$(DIRS):
			mkdir -p $(DIRS)

clean:
			rm -rf $(OBJS_DIR)
			$(MAKE) -C $(LIBFT_DIR) clean

fclean:
			rm -rf $(OBJS_DIR) $(NAME)
			$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
.PHONY : all mlx mlx_clean clean fclean re
