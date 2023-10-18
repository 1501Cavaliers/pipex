NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra -fPIE

LIBFT = libft.a
LIBFT_DIR = libft
LIB = $(addprefix $(LIBFT_DIR)/, $(LIBFT))

MY_SOURCES = main.c \
			utils.c \
			pipex.c \
			end.c

SOURCES_DIR = source
SOURCES = $(addprefix $(SOURCES_DIR)/, $(MY_SOURCES))

MY_OBJECTS = $(MY_SOURCES:.c=.o)
OBJECTS_DIR = object
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(MY_OBJECTS))

MY_BONUS = bonus.c \
			utils.c \
			pipex.c \
			end.c

BONUS_DIR = bonus
BONUS = $(addprefix $(BONUS_DIR)/, $(MY_BONUS))

MY_OBJECTS_BONUS = $(MY_BONUS:.c=.o)
OBJECTS_BONUS_DIR = object_bonus
OBJECTS_BONUS = $(addprefix $(OBJECTS_BONUS_DIR)/, $(MY_OBJECTS_BONUS))

all: $(NAME)

$(NAME) : $(OBJECTS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIB)

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	@mkdir -p $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)/$(LIBFT)

re : fclean all