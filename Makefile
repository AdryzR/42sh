##
## EPITECH PROJECT, 2024
## Minishell2
## File description:
## Makefile
##

SRC =	src/main.c \
		src/my_strcat_m.c \
		src/my_strcat.c \
		src/execute_cmd.c \
		src/init_struct.c \
		src/check_shell_args.c \
		src/check_command.c \
		src/my_strncmp.c \
		src/free_array.c \
		src/builtins/my_cd.c \
		src/builtins/my_setenv.c \
		src/builtins/my_unsetenv.c \
		src/separators/handle_redirections.c \
		src/separators/left_to_right.c \
		src/separators/double_left_to_right.c \
		src/separators/errors/check_double_l_to_r_errors.c \
		src/separators/errors/check_double_r_to_l_errors.c \
		src/separators/errors/error_messages.c \
		src/separators/errors/check_l_to_r_errors.c \
		src/separators/errors/check_r_to_l_errors.c \
		src/separators/setup_left_redirections.c \
		src/separators/setup_right_redirections.c \
		src/builtins/my_env.c \
		src/str_to_warray.c \
		src/ret_and_set_status.c \
		src/strip_str.c \
		src/separators/pipes/exec_pipe.c \
		src/separators/pipes/handle_pipe.c \
		src/my_getenv.c 					\
		src/globbing.c
		src/builtins/my_exit.c

OBJ = $(SRC:.c=.o)

NAME =	42sh

CFLAGS = -I./include

all: $(NAME)

$(NAME): $(OBJ)
	make -C lib/
	gcc -o $(NAME) $(OBJ) -L./lib -lmy $(CFLAGS)

debug: CFLAGS+=-g
# debug: CFLAGS+=-g -Wextra -Wall
debug: re

sanitize: CFLAGS += -g -static-libasan -fsanitize=address
sanitize: re

clean:
	make -C lib/ clean
	rm -f $(OBJ)

fclean: clean
	make -C lib/ fclean
	rm -f $(NAME)

re: fclean all
