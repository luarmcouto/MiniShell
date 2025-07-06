FILES = $(wildcard *.c)
OBJS = $(FILES:.c=.o)
CC = @cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
HEADER = libft.h
LIBC = ar -rcs
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@$(LIBC) $(NAME) $(OBJS)
	@echo "\033[90m[\033[32mSuccess\033[90m]\033[32m Successfully compiled Libft.\033[0m"
	@echo "\033[0;33m 𓄇 𓀠  Made by luarodri 𓄇 𓀡"
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[90m[\033[32mOK\033[90m]\033[34m \033[33m.  .  .\033[34m $<\033[0m"

clean:
	@$(RM) $(OBJS)
fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
