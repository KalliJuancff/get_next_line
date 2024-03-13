.PHONY : all comp ejec leaks norm clean

all : comp ejec leaks norm

comp :
	@cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c assertions.c tests.c

ejec :
	./a.out
	@echo
	@echo

leaks:
	leaks -atExit -- ./a.out
	@echo

norm :
	norminette get_next_line.c

clean :
	$(RM) a.out
