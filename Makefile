##
## EPITECH PROJECT, 2024
## Minishell2
## File description:
## Makefile
##

GREEN          = \033[1;32m
RED            = \033[1;31m
ILC      	   = \033[3m
ORANGE         = \033[38;5;214m
RST            = \033[0m

SRC =	src/main.c 													\
		src/my_strcat_m.c 											\
		src/my_strcat.c 											\
		src/execute_cmd.c 											\
		src/init_struct.c 											\
		src/check_shell_args.c 										\
		src/check_command.c 										\
		src/my_strncmp.c 											\
		src/free_array.c 											\
		src/builtins/my_cd.c 										\
		src/builtins/my_env.c 										\
		src/builtins/my_exit.c 										\
		src/builtins/my_setenv.c 									\
		src/builtins/my_unsetenv.c 									\
		src/separators/errors/check_l_to_r_errors.c 				\
		src/separators/errors/check_r_to_l_errors.c 				\
		src/separators/errors/check_double_l_to_r_errors.c 			\
		src/separators/errors/check_double_r_to_l_errors.c 			\
		src/separators/errors/error_messages.c 						\
		src/separators/double_left_to_right.c 						\
		src/separators/handle_redirections.c 						\
		src/separators/left_to_right.c 								\
		src/separators/setup_left_redirections.c 					\
		src/separators/setup_right_redirections.c 					\
		src/history/history_gest.c 									\
		src/history/print_history.c 								\
		src/history/set_history.c 									\
		src/str_to_warray.c 										\
		src/ret_and_set_status.c 									\
		src/strip_str.c 											\
		src/separators/pipes/exec_pipe.c 							\
		src/separators/pipes/handle_pipe.c 							\
		src/my_getenv.c 											\
		src/globbing.c 												\
		src/arrows/arrows_key.c 									\
		read_input.c 												\
		handle_specific_case_read.c 								\

OBJ = $(SRC:.c=.o)

NAME =	42sh

CFLAGS = -I./include -g

all: $(NAME)

$(NAME): $(OBJ)
	make -C lib/
	gcc -o $(NAME) $(OBJ) -L./lib -lmy $(CFLAGS)
	@printf "$(GREEN)[✅] COMPILED: $(RST) $(ILC)$(NAME)$(RST)\n"

clean:
	make -C lib/ clean
	rm -f $(OBJ)
	@printf "$(RED)[❌] CLEAN:    $(RST) Removed $(ILC)objects$(RST)\n"

fclean: clean
	make -C lib/ fclean
	rm -f $(NAME)
	@printf "$(RED)[❌] FCLEAN:   $(RST) Removed $(ILC)executables$(RST)\n"

re: fclean all

.SILENT:
