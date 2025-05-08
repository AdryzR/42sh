##
## EPITECH PROJECT, 2024
## Minishell2
## File description:
## Makefile
##

SRC =	src/main.c \
		src/main_loop.c \
		lib/lenarray.c \
		lib/my_getnbr.c \
		lib/my_put_nbr_ch.c \
		lib/my_put_nbr.c \
		lib/my_putchar_ch.c \
		lib/my_putchar.c \
		lib/my_putstr_ch.c \
		lib/my_putstr.c \
		lib/my_getcwd.c \
		lib/my_str_to_warray.c \
		lib/my_str_to_word_array.c \
		lib/my_strcmp.c \
		lib/my_strcpy.c \
		lib/my_strdup.c \
		lib/my_strlen.c \
		lib/my_strncpy.c \
		lib/my_strcat_m.c \
		lib/my_strcat.c \
		lib/join_words.c \
		src/utilities/init_struct.c \
		src/utilities/ret_and_set_status.c \
		src/utilities/print_prompt.c \
		src/commands/execute_cmd.c \
		src/commands/check_shell_args.c \
		src/commands/check_command.c \
		lib/my_strncmp.c \
		lib/free_array.c \
		src/builtins/my_cd.c \
		src/builtins/my_setenv.c \
		src/builtins/my_unsetenv.c \
		src/builtins/my_env.c \
		src/my_getenv.c \
		src/globbing.c \
		lib/str_to_warray.c \
		lib/strip_str.c \
		src/parsing/lexer.c \
		src/parsing/lexer_utilities.c \
		src/parsing/parser.c \
		src/parsing/parse_command.c \
		src/parsing/parse_binary_operation.c \
		src/parsing/parse_expression.c \
		src/parsing/parse_parentheses.c \
		src/parsing/parse_pipeline.c \
		src/parsing/parse_program.c \
		src/parsing/parse_statement.c \
		src/parsing/parse_redirect.c \
		src/parsing/parser_utilities.c \
		src/parsing/create_ast.c \
		src/interpret_ast/print_ast.c \
		src/interpret_ast/free_ast.c \
		src/interpret_ast/interpreter.c \
		src/interpret_ast/interpret_pipe.c \
		src/interpret_ast/interpret_command.c \
		src/interpret_ast/interpret_paren.c \
		src/interpret_ast/interpret_and.c \
		src/interpret_ast/interpret_or.c \
		src/interpret_ast/interpret_error.c \
		src/interpret_ast/interpret_argument.c \
		src/interpret_ast/interpret_program.c \
		src/interpret_ast/interpret_redirect.c \
		src/redirections/redirect_heredoc.c \
		src/redirections/redirect_in.c \
		src/redirections/redirect_out.c \
		src/builtins/my_exit.c	\
		src/replace_aliases.c	\
		src/builtins.c	\
		src/aliases/aliases.c	\
		src/aliases/add.c	\
		src/aliases/print.c \

OBJ = $(SRC:.c=.o)

NAME =	42sh

CFLAGS = -I./include -g

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
