# COLORS
GREEN = \033[32m
BLUE = \033[34m
YELLOW = \033[33m
RED = \033[31m
RESET = \033[0m
BOLD = \033[1m

# SOURCE FILES - Separados por pasta
MAIN_FILES = ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isdigit.c ft_isprint.c \
 ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_strlcpy.c ft_strlcat.c \
 ft_memmove.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
 ft_memchr.c ft_memcmp.c ft_count_words.c ft_strnstr.c ft_atoi.c ft_calloc.c \
 ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c \
 ft_strdup.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c \
 ft_lst_add_back.c ft_lst_add_front.c ft_lstclear.c ft_lstdellone.c ft_lstiter.c \
 ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_split.c ft_putstr.c ft_isspace.c \
 ft_skip_whitespace.c ft_strcpy.c ft_countargs.c

FILES_SUBDIR = files/ft_close_file.c files/ft_fprintf.c files/ft_open_file_read.c \
 files/ft_open_file_write.c files/ft_print_file.c get_next_line/get_next_line.c \
 files/ft_putchar_fd.c

# Combinar todos os arquivos
FILES = $(MAIN_FILES) $(FILES_SUBDIR)

OBJS = $(FILES:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
HEADER = libft.h
LIBC = ar -rcs
NAME = libft.a

# Progress variables
TOTAL_FILES = $(words $(FILES))
COMPILED = 0

all: $(NAME)

$(NAME): $(OBJS)
	@$(LIBC) $(NAME) $(OBJS)

# Progress bar function
define progress_bar
$(eval COMPILED := $(shell echo $$(($(COMPILED) + 1))))
$(eval PERCENT := $(shell echo $$(($(COMPILED) * 100 / $(TOTAL_FILES)))))
$(eval BARS := $(shell echo $$(($(PERCENT) / 2))))
$(eval SPACES := $(shell echo $$((50 - $(BARS)))))
	@printf "\r$(BLUE)$(BOLD)[%3d%%]$(RESET) $(GREEN)%s$(RESET) $(YELLOW)%s$(RESET)" \
		$(PERCENT) \
		"$$(printf '%*s' $(BARS) | tr ' ' '█')" \
		"$(basename $<)"
	@if [ $(COMPILED) -eq $(TOTAL_FILES) ]; then printf "\n"; fi
endef

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(progress_bar)

clean:
	@printf "$(YELLOW)Cleaning object files...$(RESET)\n"
	@$(RM) $(OBJS)
	@printf "$(GREEN)✓ Clean completed.$(RESET)\n"

fclean: clean
	@printf "$(YELLOW)Removing library...$(RESET)\n"
	@$(RM) $(NAME)
	@printf "$(GREEN)✓ Full clean completed.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re