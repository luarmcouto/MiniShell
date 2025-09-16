# COLORS
RED    = \033[31m
GREEN  = \033[32m
WHITE  = \033[37m
YELLOW = \033[33m
RESET  = \033[0m
BLUE   = \033[34m
PURPLE = \033[35m
TITLE  = \033[32;40m
BOLD   = \033[1m

LIBFTDIR = libft
NAME     = minishell
FLAGS    = -Wall -Wextra -Werror -g -Iincludes
IFLAGS   = -Iincludes/ -I${LIBFTDIR}
CC       = cc
SRCS     = $(wildcard srcs/*.c) $(wildcard srcs/*/*.c)
OBJS     = ${SRCS:.c=.o}
INCLUDE  = -L${LIBFTDIR} -lft -lreadline
VALGRIND = valgrind  --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=readline.supp
ENV      = env -i ${VALGRIND}

# Progress variables
TOTAL_FILES = $(words $(SRCS))
COMPILED = 0

# Set readline for MacOs and Linux
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
    INCLUDE = -L${LIBFTDIR} -lft -lreadline -lhistory
    READLINE =
else ifeq ($(UNAME), Darwin)
    INCLUDE = -L${LIBFTDIR} -lft -L/opt/homebrew/opt/readline/lib -lreadline
    READLINE = -I/opt/homebrew/opt/readline/include
endif

all: ${NAME}

# Libft como dependência separada
${LIBFTDIR}/libft.a:
	@printf "$(YELLOW)$(BOLD)🔧 Checking libft...$(RESET)\n"
	@if [ ! -d "${LIBFTDIR}" ]; then \
		printf "$(YELLOW)📦 Libft not found. Cloning...$(RESET)\n"; \
		git clone https://github.com/luarmcouto/libft.git ${LIBFTDIR}; \
	fi
	@printf "$(YELLOW)🔨 Building libft...$(RESET)\n"
	@make -C ${LIBFTDIR}
	@printf "$(GREEN)✓ Libft ready!$(RESET)\n"

# Progress bar function for minishell
define progress_bar
	$(eval COMPILED := $(shell echo $$(($(COMPILED) + 1))))
	$(eval PERCENT := $(shell echo $$(($(COMPILED) * 100 / $(TOTAL_FILES)))))
	$(eval BARS := $(shell echo $$(($(PERCENT) / 2))))
	$(eval SPACES := $(shell echo $$((50 - $(BARS)))))
	$(eval FILENAME := $(shell basename $< .c))
	@printf "\r$(BLUE)$(BOLD)[%3d%%]$(RESET) $(GREEN)%s$(RESET) $(YELLOW)%s$(RESET)" \
		$(PERCENT) \
		"$$(printf '%*s' $(BARS) | tr ' ' '█')" \
		"$(FILENAME)"
	@if [ $(COMPILED) -eq $(TOTAL_FILES) ]; then printf "\n"; fi
endef

# Regra principal - apenas compila se necessário
${NAME}: ${LIBFTDIR}/libft.a ${OBJS}
	@printf "$(YELLOW)$(BOLD)🔗 Linking ${NAME}...$(RESET)\n"
	@${CC} ${FLAGS} ${READLINE} ${OBJS} ${INCLUDE} -o ${NAME}
	@printf "\n"
	@printf "$(TITLE)╔══════════════════════════════════════════════════════════════════════════════╗$(RESET)\n"
	@printf "$(TITLE)║                                                                              ║$(RESET)\n"
	@printf "$(CYAN)║      ███╗   ███╗██╗███╗   ██╗██╗$(BLUE)███████╗██╗  ██╗███████╗██╗     ██╗     $(RESET)\n"
	@printf "$(CYAN)║      ████╗ ████║██║████╗  ██║██║$(BLUE)██╔════╝██║  ██║██╔════╝██║     ██║     $(RESET)\n"
	@printf "$(CYAN)║      ██╔████╔██║██║██╔██╗ ██║██║$(BLUE)███████╗███████║█████╗  ██║     ██║     $(RESET)\n"
	@printf "$(CYAN)║      ██║╚██╔╝██║██║██║╚██╗██║██║$(BLUE)╚════██║██╔══██║██╔══╝  ██║     ██║     $(RESET)\n"
	@printf "$(CYAN)║      ██║ ╚═╝ ██║██║██║ ╚████║██║$(BLUE)███████║██║  ██║███████╗███████╗███████╗$(RESET)\n"
	@printf "$(CYAN)║      ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝$(BLUE)╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝$(RESET)\n"
	@printf "$(TITLE)║                                                                              ║$(RESET)\n"
	@printf "$(TITLE)║                                                                              ║$(RESET)\n"
	@printf "$(GREEN)║       ╔═══════════════════════════════════════════════════════════════╗       $(RESET)\n"
	@printf "$(GREEN)║       ║            $(WHITE)🐚 $(BOLD)A Beautiful Shell Implementation$(RESET) $(GREEN)🐚            ║       $(RESET)\n"
	@printf "$(GREEN)║       ║         $(CYAN)Full POSIX compliance $(WHITE)• $(BLUE)Pipes $(WHITE)• $(PURPLE)Redirections $(WHITE)• $(RED)Built-ins$(GREEN)         ║       $(RESET)\n"
	@printf "$(GREEN)║       ║              $(YELLOW)Advanced parsing with Binary Tree architecture$(GREEN)              ║       $(RESET)\n"
	@printf "$(GREEN)║       ║                   $(YELLOW)Crafted with $(RED)♥$(YELLOW) by $(CYAN)@luarodri$(YELLOW) & $(CYAN)@iwietzke$(GREEN)                   ║       $(RESET)\n"
	@printf "$(GREEN)║       ╚═══════════════════════════════════════════════════════════════╝       $(RESET)\n"
	@printf "$(TITLE)║                                                                              ║$(RESET)\n"
	@printf "$(TITLE)╚══════════════════════════════════════════════════════════════════════════════╝$(RESET)\n"
	@printf "\n"
	@printf "$(B_GREEN)                          🎉 SUCCESSFULLY COMPILED! 🎉                           $(RESET)\n"
	@printf "$(B_BLUE)                        Your shell is ready to command! 💪                       $(RESET)\n"
	@printf "\n"

%.o: %.c
	@${CC} ${FLAGS} ${READLINE} ${IFLAGS} -c $< -o $@
	@$(progress_bar)

clean:
	@printf "$(YELLOW)🧹 Cleaning object files...$(RESET)\n"
	@${RM} ${OBJS}
	@if [ -d ${LIBFTDIR} ]; then make -C ${LIBFTDIR} clean; fi
	@printf "$(GREEN)✓ Clean completed.$(RESET)\n"

fclean: clean
	@printf "$(YELLOW)💥 Full clean with libft removal...$(RESET)\n"
	@${RM} ${NAME}
	@rm -rf ${LIBFTDIR}
	@printf "$(GREEN)✓ Full clean with libft removal completed.$(RESET)\n"

test: ${NAME} readline.supp
	@printf "$(BLUE)🧪 Running tests with Valgrind...$(RESET)\n"
	${VALGRIND} ./${NAME}

readline.supp:
	@printf "$(YELLOW)📝 Creating readline suppression file...$(RESET)\n"
	@echo "{" > readline.supp
	@echo "    leak readline" >> readline.supp
	@echo "    Memcheck:Leak" >> readline.supp
	@echo "    ..." >> readline.supp
	@echo "    fun:readline" >> readline.supp
	@echo "}" >> readline.supp
	@echo "{" >> readline.supp
	@echo "    leak add_history" >> readline.supp
	@echo "    Memcheck:Leak" >> readline.supp
	@echo "    ..." >> readline.supp
	@echo "    fun:add_history" >> readline.supp
	@echo "}" >> readline.supp
	@echo "{" >> readline.supp
	@echo "    leak rl_parse_and_bind" >> readline.supp
	@echo "    Memcheck:Leak" >> readline.supp
	@echo "    ..." >> readline.supp
	@echo "    fun:add_history" >> readline.supp
	@echo "}" >> readline.supp
	@printf "$(GREEN)✓ Suppression file created.$(RESET)\n"

env: ${NAME}
	@printf "$(BLUE)🌍 Running with clean environment...$(RESET)\n"
	${ENV} ./${NAME}

re: fclean all

# Force rebuild of everything including libft
re-all: fclean all

# Debug rule to check libft
debug-libft:
	@printf "$(BLUE)🔍 Libft Debug Information:$(RESET)\n"
	@printf "$(BLUE)📂 Libft directory: ${LIBFTDIR}$(RESET)\n"
	@printf "$(BLUE)📁 Libft exists: $(shell [ -d ${LIBFTDIR} ] && echo "$(GREEN)YES$(RESET)" || echo "$(RED)NO$(RESET)")\n"
	@printf "$(BLUE)📚 Libft.a exists: $(shell [ -f ${LIBFTDIR}/libft.a ] && echo "$(GREEN)YES$(RESET)" || echo "$(RED)NO$(RESET)")\n"
	@if [ -d ${LIBFTDIR} ]; then \
		printf "$(BLUE)📋 Libft contents:$(RESET)\n"; \
		ls -la ${LIBFTDIR}/ | head -10; \
	fi

# Show compilation stats
stats:
	@printf "$(BLUE)📊 Project Statistics:$(RESET)\n"
	@printf "$(YELLOW)📁 Total source files: $(BOLD)$(TOTAL_FILES)$(RESET)\n"
	@printf "$(YELLOW)📂 Source directories:$(RESET)\n"
	@find srcs -type d | sed 's/^/  /'
	@printf "$(YELLOW)🗂️  Include files:$(RESET)\n"
	@find includes -name "*.h" | sed 's/^/  /'

.PHONY: all clean fclean re re-all test env debug-libft stats