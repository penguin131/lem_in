NAME = 	../lem-in
INC = 	../inc/
SRC = 	main.c \
		list/list.c \
		hasht/hasht.c \
		reading/ft_read.c \
		reading/ft_arg_is_valid.c \
		reading/ft_help_arg_valid.c \
		reading/ft_strchr_line.c \
		solver/dijkstra.c \
		solver/dijkstra2.c \
		solver/stack.c \
		solver/get_solution.c \
		solver/print_result.c \
		solver/solver.c \
		reading/helper.c \
		solver/functions.c

OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror -c
CC = gcc
INC_LIB = ../libft/

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) -o $(NAME) -I $(INC_LIB) -L ../libft/ -lft $(OBJ) ../libft/libftprintf.a

%.o: src/%.c
	@$(CC) $(FLAGS) -I $(INC) -o $@ -c $<

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean all
