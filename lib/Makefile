##
## EPITECH PROJECT, 2024
## B-CPE-110-STG-1-1-settingup-adrien.raphanaud
## File description:
## Makefile
##

GREEN          = \033[1;32m
RED            = \033[1;31m
ILC      	   = \033[3m
ORANGE         = \033[38;5;214m
RST            = \033[0m

SRC =	my_putchar.c				\
	my_put_nbr.c					\
	my_getnbr.c						\
	my_strdup.c						\
	my_strcpy.c						\
	my_putchar_ch.c					\
	my_put_nbr_ch.c 				\
	my_putstr.c						\
	my_strcmp.c						\
	my_strlen.c						\
	my_putstr_ch.c 					\
	my_str_to_word_array.c			\
	lenarray.c 						\
	my_strncpy.c 					\
	libprintf/flag_c.c 				\
	libprintf/flag_d.c 				\
	libprintf/flag_e.c 				\
	libprintf/flag_e_up.c 			\
	libprintf/flag_f.c 				\
	libprintf/flag_f_up.c 			\
	libprintf/flag_hd.c 			\
	libprintf/flag_hi.c 			\
	libprintf/flag_ho.c 			\
	libprintf/flag_hu.c 			\
	libprintf/flag_hx.c 			\
	libprintf/flag_hx_up.c 			\
	libprintf/flag_i.c 				\
	libprintf/flag_ld.c 			\
	libprintf/flag_li.c 			\
	libprintf/flag_lld.c 			\
	libprintf/flag_lli.c 			\
	libprintf/flag_llo.c 			\
	libprintf/flag_llu.c 			\
	libprintf/flag_llx.c 			\
	libprintf/flag_llx_up.c 		\
	libprintf/flag_lo.c 			\
	libprintf/flag_lu.c 			\
	libprintf/flag_lx.c 			\
	libprintf/flag_lx_up.c 			\
	libprintf/flag_n.c				\
	libprintf/flag_o.c 				\
	libprintf/flag_p.c 				\
	libprintf/flag_prct.c 			\
	libprintf/flag_s.c 				\
	libprintf/flag_u.c 				\
	libprintf/flag_x.c 				\
	libprintf/flag_x_up.c 			\
	libprintf/my_printf.c 			\
	libprintf/my_putchar.c			\
	libprintf/my_put_nbr_base.c 	\
	libprintf/my_put_nbr.c 			\
	libprintf/my_putstr.c 			\
	libprintf/my_strcmp.c 			\
	libprintf/my_strlen.c 			\
	libprintf/my_strncpy.c			\


OBJ = $(SRC:.c=.o)

NAME =	libmy.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	@printf "$(GREEN)[✅] COMPILED: $(RST) $(ILC)$(NAME)$(RST)\n"

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SILENT:
