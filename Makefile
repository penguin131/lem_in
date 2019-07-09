
all : do_it

do_it :
	@make -C libft/
	@make clean -C libft/
	@make -C src
	@make -C src/visu

clean :
	@make clean -C src
	@make clean -C src/visu

fclean : clean
	@make fclean -C src
	@make fclean -C src/visu

re : fclean all
