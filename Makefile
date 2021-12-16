NAME = so_long

SRCS = 	so_long.c \
		check_error.c \
		parsing_map.c \
		clear.c \
		draw.c \
		texture.c \
		move.c \
		init.c \
		utils.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

SRCS_BONUS	=	so_long_bonus.c \
				check_error_bonus.c \
				parsing_map_bonus.c \
				clear_bonus.c \
				draw_bonus.c \
				texture_bonus.c \
				move_bonus.c \
				init_bonus.c \
				utils_bonus.c \
				get_next_line/get_next_line.c \

SRCS_DIR = src
SRCS_BONUS_DIR = bonus

OBJS = $(SRCS:.c=.o)
OBJS_DIR = obj
DIRS = obj obj/get_next_line

BONUS_OBJS = $(SRCS_BONUS:.c=.o)
OBJS_BONUS_DIR = obj_bonus
DIRS_BONUS = obj_bonus obj_bonus/get_next_line

_SRCS =  $(addprefix $(SRCS_DIR)/, $(SRCS))
_OBJS = $(addprefix $(OBJS_DIR)/, $(OBJS))

_SRCS_BONUS =  $(addprefix $(SRCS_BONUS_DIR)/, $(SRCS_BONUS))
_OBJS_BONUS = $(addprefix $(OBJS_BONUS_DIR)/, $(BONUS_OBJS))

HEADERS = src
MLX_DIR = mlx
LIBFT = libft.a
LIBFT_DIR = libft

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I $(HEADERS)
LFLAGS = $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -L $(MLX_DIR) #-fsanitize=address -g

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
    LFLAGS = $(CFLAGS) -lmlx -lXext -lX11 -lm -L $(MLX_DIR)
endif

all: $(NAME)

$(_OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(DIRS) $(LIBFT_DIR)/$(LIBFT) mlx
		$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(_OBJS)
		$(CC) $(_OBJS) $(LIBFT_DIR)/$(LIBFT) $(LFLAGS) -o $(NAME)

bonus:	$(_OBJS_BONUS)
		$(CC) $(_OBJS_BONUS) $(LIBFT_DIR)/$(LIBFT) $(LFLAGS) -o $(NAME)_bonus

$(_OBJS_BONUS): $(OBJS_BONUS_DIR)/%.o : $(SRCS_BONUS_DIR)/%.c $(DIRS_BONUS) $(LIBFT_DIR)/$(LIBFT) mlx
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

$(DIRS_BONUS):
			mkdir -p $(DIRS_BONUS)

clean:
			rm -rf $(OBJS_DIR)
			rm -rf $(OBJS_BONUS_DIR)
			$(MAKE) -C $(LIBFT_DIR) clean

fclean:
			rm -rf $(OBJS_DIR) $(NAME)
			rm -rf $(OBJS_BONUS_DIR) $(NAME)_bonus
			$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
.PHONY : all mlx bonus mlx_clean clean fclean re
