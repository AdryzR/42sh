##
## EPITECH PROJECT, 2024
## Minishell2
## File description:
## Makefile
##

SRC =	src/main.c \
		lib/lenarray.c \
		lib/my_getnbr.c \
		lib/my_put_nbr_ch.c \
		lib/my_put_nbr.c \
		lib/my_putchar_ch.c \
		lib/my_putchar.c \
		lib/my_putstr_ch.c \
		lib/my_putstr.c \
		lib/my_str_to_warray.c \
		lib/my_str_to_word_array.c \
		lib/my_strcmp.c \
		lib/my_strcpy.c \
		lib/my_strdup.c \
		lib/my_strlen.c \
		lib/my_strncpy.c \
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
		src/parsing/lexer.c \
		src/parsing/utilities.c \
		src/builtins/my_exit.c

OBJ = $(SRC:.c=.o)

NAME =	42sh

CFLAGS = -I./include

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) -L./lib $(CFLAGS)

debug: CFLAGS+=-g
# debug: CFLAGS+=-g -Wextra -Wall
debug: re

sanitize: CFLAGS += -g -static-libasan -fsanitize=address
sanitize: re

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
