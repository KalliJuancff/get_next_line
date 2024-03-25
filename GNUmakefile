.PHONY : all comp ejec leaks norm clean

all : comp ejec leaks norm

comp :
	@cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c assertions.c tests.c -o a.out

comp_bonus:
	@cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c assertions.c tests_bonus.c -o a_bonus.out

ejec : comp
	./a.out
	@echo
	@echo

ejec_bonus : comp_bonus
	./a_bonus.out
	@echo
	@echo

leaks : comp
	leaks -atExit -- ./a.out
	@echo

leaks_bonus : comp_bonus
	leaks -atExit -- ./a_bonus.out

norm :
	norminette get_next_line.c get_next_line_bonus.c get_next_line.h get_next_line_bonus.h get_next_line_utils.c get_next_line_utils_bonus.c

clean :
	$(RM) -f a.out
	$(RM) -rf a.out.dSYM
	$(RM) -f a_bonus.out
	$(RM) -f *.gch
