# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luamonteiro <luamonteiro@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 15:11:08 by luamonteiro       #+#    #+#              #
#    Updated: 2025/05/22 15:12:46 by luamonteiro      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		= minishell

# Directories
SRC_DIR		= src
INC_DIR		= includes
LIBFT_DIR	= libft
OBJ_DIR		= obj

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR)
LIBS		= -L$(LIBFT_DIR) -lft -lreadline

# Source files
SRCS		= $(SRC_DIR)/main.c

# Object files
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libft
LIBFT		= $(LIBFT_DIR)/libft.a

# Colors for output
GREEN		= \033[0;32m
RED			= \033[0;31m
BLUE		= \033[0;34m
YELLOW		= \033[1;33m
NC			= \033[0m # No Color

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(BLUE)Compiling libft...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

clean:
	@echo "$(RED)Cleaning objects...$(NC)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(NC)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

re: fclean all

# Test compilation
test: $(NAME)
	@echo "$(GREEN)Running basic test...$(NC)"
	@./$(NAME)

# Debug version
debug: CFLAGS += -g -fsanitize=address
debug: re

# Bonus rule (for later)
bonus: all

.PHONY: all clean fclean re test debug bonus