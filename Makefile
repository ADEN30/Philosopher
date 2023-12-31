GCC = gcc -pthread -Wall -Wextra -Werror
SRC = main.c\
	  init.c\
	  death.c\
	  parse.c\
	  threads.c\
	  utils.c
OBJ = $(SRC:.c=.o)
HEADER = -I./include -I./usr/include/linux/types.h
NAME = philo

%.o : %.c
	$(GCC) $(HEADER) -c $< -o $@

all : $(NAME)
	@if [ -e "$(NAME)" ] ; then \
		echo "\033[1;32mPHILOSOPHER is build!\033[0m" ; \
	else \
		@echo -e "\031[1;31mPHILOSOPHER is not build!\033[0m" ; \
	fi

$(NAME) : $(OBJ)
	@$(GCC) -o  $(NAME) $(OBJ) #-fsanitize=thread

clean :
	@rm -f $(OBJ)
	@echo "\033[1;32mClean Philosopher!\033[0m"

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "\033[1;32mFclean Philosopher !\033[0m"

re : fclean all

.PHONY: all clean fclean re
