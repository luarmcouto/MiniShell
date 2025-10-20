NAME = minishell

#
# Compilation flags (use Homebrew readline/ncurses for macOS ARM64)
CFLAGS = -I/opt/homebrew/opt/readline/include
#
# Linker flags (use Homebrew readline/ncurses for macOS ARM64)
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline -lncurses

# Compilator
CC = cc

# Archiver
AR = ar rcs

# Directories
SRC_DIR = src
MANDATORY_DIR = $(SRC_DIR)/mandatory
BONUS_DIR = $(SRC_DIR)/bonus
UTILS_DIR = utils
LIBS_DIR = libs
LIBFT_DIR = $(LIBS_DIR)/libft
OBJ_DIR = objs
OBJ_MANDATORY_DIR = $(OBJ_DIR)/mandatory
OBJ_BONUS_DIR = $(OBJ_DIR)/bonus

# Library files
LIB_NAME = $(LIBFT_DIR)/libft.a

# Main Source Files
MAIN_SOURCE = $(MANDATORY_DIR)/main.c
MAIN_SOURCE_BONUS = $(BONUS_DIR)/main.c

# Source files
MINISHELL_SRCS = \
	$(MANDATORY_DIR)/ft_minishell.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/ft_msg_start.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/ft_search_file/ft_is_dot_or_dotdot.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/ft_search_file/ft_search_file.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/ft_search_file/ft_search_in_dir.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/ft_search_file/ft_search_in_subdirs.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/ft_search_file/ft_build_path.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/ft_count_args.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/ft_redir_io.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/ft_free_char_array.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/error/ft_handle_error.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/input/ft_read_input.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/input/ft_process_input.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/debug/ft_show_debug.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/prompt/ft_get_directory_path.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/prompt/ft_generate_prompt.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/env/ft_cpyenv.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/env/ft_getenv.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/env/ft_setenv.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/env/ft_setenv_utils.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/redirections/ft_handle_infile.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/redirections/ft_handle_outfile.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/execution/ft_exec_cmd.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/execution/ft_get_cmd_path.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/execution/ft_close_unused_fds.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/execution/ft_finish_execution.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/execution/ft_execute_error_command.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/execution/ft_execute_pipeline.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/execution/ft_handle_heredoc.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/execution/ft_setup_child_io.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/parsing/ft_skip_quotes.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/parsing/ft_check_unclosed_quotes.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/parsing/ft_split_input.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/parsing/ft_split_input_utils.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/parsing/ft_parse_input.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/parsing/ft_parse_input_utils.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/parsing/ft_handle_env_expansion.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/parsing/ft_remove_quotes.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/parsing/ft_syntax_check.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/parsing/ft_handle_env_expansion_utils.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/signals/ft_sigint_handler.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/signals/ft_init_signals.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/builtins/ft_echo.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/builtins/ft_cd.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/builtins/ft_pwd.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/builtins/ft_export.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/builtins/ft_unset.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/builtins/ft_env.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/builtins/ft_exit.c \
	$(MANDATORY_DIR)/$(UTILS_DIR)/builtins/ft_handle_builtins.c \


# Objetos para mandatory y bonus
MAIN_OBJECT = $(MAIN_SOURCE:$(MANDATORY_DIR)/%.c=$(OBJ_MANDATORY_DIR)/%.o)
MINISHELL_OBJS = $(MINISHELL_SRCS:$(MANDATORY_DIR)/%.c=$(OBJ_MANDATORY_DIR)/%.o)
VALGRIND_SUPP	= valgrind_suppression.supp

# Colors
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

all: $(LIB_NAME) $(NAME)
	@echo "\033[35m$(NAME) executable is ready to use!\033[0m"

# Compile the library
$(LIB_NAME):
	@$(MAKE) -C $(LIBFT_DIR)

# Compile the project
$(NAME): $(MINISHELL_OBJS) $(MAIN_OBJECT)
	@$(CC) $(CFLAGS) $(MINISHELL_OBJS) $(MAIN_OBJECT) $(LIB_NAME) $(LDFLAGS) -o $(NAME)
	@if [ $$? -eq 0 ]; then \
		echo "\033[32m✅ Compilation completed successfully!\033[0m"; \
	else \
		echo "\033[31m❌ Error during compilation!\033[0m"; \
	fi

# Compile object files for mandatory
$(OBJ_MANDATORY_DIR)/%.o: $(MANDATORY_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Create valgrind suppression file
$(VALGRIND_SUPP):
	@echo "$(YELLOW)Creating valgrind suppression file...$(RESET)"
	@echo "{" > $(VALGRIND_SUPP)
	@echo "   readline_memory_leak_suppression" >> $(VALGRIND_SUPP)
	@echo "   Memcheck:Leak" >> $(VALGRIND_SUPP)
	@echo "   ..." >> $(VALGRIND_SUPP)
	@echo "   fun:readline" >> $(VALGRIND_SUPP)
	@echo "}" >> $(VALGRIND_SUPP)
	@echo "{" >> $(VALGRIND_SUPP)
	@echo "   readline_add_history_suppression" >> $(VALGRIND_SUPP)
	@echo "   Memcheck:Leak" >> $(VALGRIND_SUPP)
	@echo "   ..." >> $(VALGRIND_SUPP)
	@echo "   fun:add_history" >> $(VALGRIND_SUPP)
	@echo "}" >> $(VALGRIND_SUPP)
	@echo "{" >> $(VALGRIND_SUPP)
	@echo "   readline_internal_suppression" >> $(VALGRIND_SUPP)
	@echo "   Memcheck:Leak" >> $(VALGRIND_SUPP)
	@echo "   ..." >> $(VALGRIND_SUPP)
	@echo "   fun:_rl_*" >> $(VALGRIND_SUPP)
	@echo "}" >> $(VALGRIND_SUPP)
	@echo "{" >> $(VALGRIND_SUPP)
	@echo "   suppress_execve_bin_error" >> $(VALGRIND_SUPP)
	@echo "   Memcheck:Leak" >> $(VALGRIND_SUPP)
	@echo "   ..." >> $(VALGRIND_SUPP)
	@echo "   obj:/usr/bin/*" >> $(VALGRIND_SUPP)
	@echo "}" >> $(VALGRIND_SUPP)
	@echo "$(GREEN)✅ Valgrind suppression file created!$(RESET)"

# Run valgrind with suppression
v: $(LIB_NAME) $(NAME) $(VALGRIND_SUPP)
	@echo "$(YELLOW)Running valgrind with suppression file...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		--suppressions=./$(VALGRIND_SUPP) ./$(NAME)

# Clean up object files
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@if [ $$? -eq 0 ]; then \
		echo "\033[32m🧹 Object files cleaned successfully!\033[0m"; \
	else \
		echo "\033[31m❌ Error cleaning object files!\033[0m"; \
	fi

# Clean up object files and the executable
fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME) $(NAME)_bonus $(VALGRIND_SUPP)
	@if [ $$? -eq 0 ]; then \
		echo "\033[32m🗑️  Libraries, objects and executables cleaned successfully!\033[0m"; \
	else \
		echo "\033[31m❌ Error cleaning libraries, objects and executables!\033[0m"; \
	fi

re: fclean
	@echo "\033[34m🔄 Recompiling everything...\033[0m"
	@$(MAKE) all
	@if [ $$? -eq 0 ]; then \
		echo "\033[38;5;208m🎉 Recompilation completed successfully!\033[0m"; \
	else \
		echo "\033[31m❌ Error during recompilation!\033[0m"; \
	fi

# Phony targets
.PHONY: all clean fclean re v
