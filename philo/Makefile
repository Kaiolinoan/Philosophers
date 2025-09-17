NAME = philo
CC = cc
CFLAGS = -Werror -Wall -Wextra -g3 -I. -I.. 
SRC_FOLDER = src
OBJ_FOLDER = obj
SRCS_FILES = $(addprefix $(SRC_FOLDER)/, $(addsuffix .c, main start libfunc mutex utils))
OBJS = $(patsubst $(SRC_FOLDER)/%.c, $(OBJ_FOLDER)/%.o, $(SRCS_FILES))

all: $(OBJ_FOLDER) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)
	@echo 'Biblioteca criada'
	@echo 'Codigo compilado!'

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_FOLDER):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ_FOLDER)
	@echo 'Objetos limpos!'

fclean: clean
	@rm -f $(NAME)
	@echo  'Biblioteca limpa!'

re: fclean all