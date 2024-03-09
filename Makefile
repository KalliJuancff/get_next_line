NAME      := get_next_line.out
SRC_FILES := get_next_line.c
OBJ_FILES := $(patsubst %.c,%.o,$(SRC_FILES))
DEP_FILES := $(patsubst %.c,%.d,$(SRC_FILES))

CARGS     := -Wall -Wextra -Werror
CARGS     += -MMD

ifdef BUFSZ
	CARGS     += -D BUFFER_SIZE=$(BUFSZ)
endif

$(NAME) : $(OBJ_FILES)
	$(CC) $(CARGS) main.c $(OBJ_FILES) -o $(NAME)

%.o : %.c Makefile
	$(CC) $(CARGS) -c $< -o $@

-include $(DEP_FILES)


.PHONY: all clean fclean re norm run info help

all : $(NAME)

clean :
	$(RM) $(OBJ_FILES)
	$(RM) $(DEP_FILES)

fclean : clean
	$(RM) $(NAME)

re : fclean all

norm :
	norminette $(SRC_FILES)

run : fclean all $(NAME)
	@echo "\n"
	@echo EJECUTANDO $(NAME):
	@./$(NAME) $(FILE)

info :
	$(info $(SRC_FILES))
	$(info $(OBJ_FILES))
	$(info $(DEP_FILES))
	$(info $(CARGS))

help :
	@echo 'Variable para especificar el BUFFER_SIZE' : \'BUF_SZ\'
	@echo 'Variable para especificar el fichero    ' : \'FILE\'
