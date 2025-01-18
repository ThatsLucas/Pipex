NAME = pipex
BONUS_NAME = pipex_bonus

CC = cc -g3
CFLAGS = -I ./include/ -I ./libft/

LIBFT = ./libft/libft.a

SRC_DIR = ./src
OBJ_DIR = ./obj
SRC_FILES = $(SRC_DIR)/main.c \
			$(SRC_DIR)/pipex_utils.c \
			$(SRC_DIR)/files_manager.c \
			$(SRC_DIR)/fork_execution.c
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

BONUS_DIR = $(SRC_DIR)/bonus
BONUS_OBJ_DIR = $(OBJ_DIR)/bonus
BONUS_FILES = $(BONUS_DIR)/main_bonus.c \
			  $(BONUS_DIR)/pipex_utils_bonus.c \
			  $(BONUS_DIR)/files_manager_bonus.c \
			  $(BONUS_DIR)/fork_execution_bonus.c
BONUS_OBJ_FILES = $(BONUS_FILES:$(BONUS_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

all: $(NAME)

bonus: $(BONUS_NAME)

$(LIBFT):
	make -C ./libft

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJ_FILES) $(LIBFT) -o $(BONUS_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c $(LIBFT)
	mkdir -p $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BONUS_OBJ_DIR)
	make -C ./libft clean

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	make -C ./libft fclean

re: fclean all

.PHONY: all bonus clean fclean re
