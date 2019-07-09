NAME = ../../visu

SRC = 	ft_visu.c \
      	ft_init.c \
      	ft_paste_rooms.c \
      	ft_read_sol.c \
      	../solver/stack.c \
      	../solver/get_solution.c \
      	../reading/ft_arg_is_valid.c \
      	../reading/ft_help_arg_valid.c \
      	../reading/ft_strchr_line.c \
      	../hasht/hasht.c \
      	../list/list.c \
      	ft_mv.c \
      	ft_paste_room_help.c \
      	../reading/helper.c

INC = 	../../inc/
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror -c
CC = gcc
INC_LIB = ../../libft/

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) -o $(NAME) -I $(INC_LIB) -L ../../libft/ -lft -L ../../sdl2/ -l SDL2-2.0.0 $(OBJ)

%.o: src/%.c
	@$(CC) $(FLAGS) -I $(INC) -o $@ -c $<

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean all
