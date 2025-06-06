# ------------------------------------------------------------------------------
# Configuration principale
# ------------------------------------------------------------------------------

USE_BONUS   = no

NAME        = output/philo
NAME_BONUS  = philo_bonus
TEST_RUNNER = test_runner

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -Iheader
PTHREAD     = -lpthread

INCLUDES        = -Iheader
INCLUDES_BONUS  = -Iheader

MKDIR   = mkdir -p
RM      = rm -f

# Couleurs
BLACK   = \033[0;30m
RED     = \033[0;91m
GREEN   = \033[0;92m
YELLOW  = \033[0;93m
BLUE    = \033[0;94m
MAGENTA = \033[0;95m
CYAN    = \033[0;96m
WHITE   = \033[0;97m
BOLD    = \033[1m
RESET   = \033[0m

SRC_DIR     = sources
OBJ_DIR     = objects
BONUS_DIR   = sources_bonus
TEST_DIR    = tests

SRC_FILES := $(shell find $(SRC_DIR) -name "*.c" 2>/dev/null)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

BONUS_SRC_FILES := $(shell find $(BONUS_DIR) -name "*.c" 2>/dev/null)
BONUS_OBJ_FILES := $(patsubst $(BONUS_DIR)/%.c, $(OBJ_DIR)/bonus_%.o, $(BONUS_SRC_FILES))

TEST_SRC_FILES := $(SRC_DIR)/init.c $(SRC_DIR)/memory.c $(SRC_DIR)/mini_libft.c \
				  $(SRC_DIR)/monitor.c $(SRC_DIR)/parsing.c $(SRC_DIR)/philo_action.c \
				  $(SRC_DIR)/philosopher.c $(SRC_DIR)/print.c $(SRC_DIR)/safe_sync.c \
				  $(SRC_DIR)/simulation.c $(SRC_DIR)/time.c $(SRC_DIR)/utils.c \
				  \
				  $(TEST_DIR)/test1.c $(TEST_DIR)/test2.c $(TEST_DIR)/test3.c \
				  $(TEST_DIR)/test4.c $(TEST_DIR)/test6.c $(TEST_DIR)/test7.c \
				  $(TEST_DIR)/test8.c $(TEST_DIR)/test9.c $(TEST_DIR)/test10.c

DIRS_TO_CREATE := $(OBJ_DIR)

# ------------------------------------------------------------------------------
# Cibles principales
# ------------------------------------------------------------------------------
all: dirs $(NAME)

dirs:
	@$(MKDIR) $(DIRS_TO_CREATE)

ifeq ($(USE_BONUS), yes)
bonus: dirs $(NAME_BONUS)
endif

# ------------------------------------------------------------------------------
# Compilation binaire principal
# ------------------------------------------------------------------------------
$(NAME): $(OBJ_FILES)
	@set -e; \
	colors="30 31 32 33 34 35 36 37 90 91 92 93 94 95 96 97"; \
	color=$$(echo $$colors | tr ' ' '\n' | shuf -n1); \
	mkdir -p output; \
	printf "\033[2K\r$(CYAN)→ creating output folder...$(RESET)"; \
	printf "\033[2K\r$(CYAN)→ Linking objects...$(RESET)"; \
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) $(PTHREAD); \
	printf "\033[2K\r$(BOLD)$(GREEN)✔ Finished building $(NAME)$(RESET)\n"; \
	clear; \
	printf "\033[1;$$color""m%b$(RESET)\n" "\
██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗\n \
██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝\n \
██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗\n \
██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║\n \
██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║\n \
╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝\n"; \
	printf "\033[0;92m🍝 I never thought philosophy would be so deadly!$(RESET)\n"; \
	count=$$(find $(OBJ_DIR) -name '*.o' ! -name 'bonus_*.o' ! -name 'test_*.o' | wc -l); \
	build_date=$$(date +"%Y-%m-%d %H:%M:%S"); \
	printf "\n$(BOLD)📦 Build summary:$(RESET)\n"; \
	printf "  $(WHITE)• 🧱 Files compiled   :$(RESET) $(GREEN)$$count$(RESET)\n"; \
	printf "  $(WHITE)• 🧵 Threading       :$(RESET) $(GREEN)pthread$(RESET)\n"; \
	printf "  $(WHITE)• 📂 Exec path       :$(RESET) $(CYAN)$(NAME)$(RESET)\n"; \
	printf "  $(WHITE)• 🕒 Date           :$(RESET) $(CYAN)$$build_date$(RESET)\n"

# ------------------------------------------------------------------------------
# Compilation binaire bonus
# ------------------------------------------------------------------------------
$(NAME_BONUS): $(BONUS_OBJ_FILES)
	@set -e; \
	colors="30 31 32 33 34 35 36 37 90 91 92 93 94 95 96 97"; \
	color=$$(echo $$colors | tr ' ' '\n' | shuf -n1); \
	printf "\033[2K\r$(CYAN)→ Linking bonus objects...$(RESET)"; \
	$(CC) $(CFLAGS) $(BONUS_OBJ_FILES) -o $(NAME_BONUS) $(PTHREAD); \
	printf "\033[2K\r$(BOLD)$(GREEN)✔ Finished building $(NAME_BONUS)$(RESET)\n"; \
	clear; \
	printf "\033[1;$$color""m%b$(RESET)\n" "\
██████╗ ██╗  ██╗██╗██╗      ██████╗     ██████╗  ██████╗ ███╗   ██╗██╗   ██╗███████╗\n \
██╔══██╗██║  ██║██║██║     ██╔═══██╗    ██╔══██╗██╔═══██╗████╗  ██║██║   ██║██╔════╝\n \
██████╔╝███████║██║██║     ██║   ██║    ██████╔╝██║   ██║██╔██╗ ██║██║   ██║███████╗\n \
██╔═══╝ ██╔══██║██║██║     ██║   ██║    ██╔══██╗██║   ██║██║╚██╗██║██║   ██║╚════██║\n \
██║     ██║  ██║██║███████╗╚██████╔╝    ██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████║\n \
╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝     ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝\n"; \
	printf "\033[0;92m🌿 Philosophers with processes and semaphores!$(RESET)\n"; \
	count=$$(find $(OBJ_DIR) -name 'bonus_*.o' | wc -l); \
	build_date=$$(date +"%Y-%m-%d %H:%M:%S"); \
	printf "\n$(BOLD)📦 Build summary:$(RESET)\n"; \
	printf "  $(WHITE)• 🧱 Files compiled   :$(RESET) $(GREEN)$$count$(RESET)\n"; \
	printf "  $(WHITE)• 🔄 IPC             :$(RESET) $(GREEN)semaphores$(RESET)\n"; \
	printf "  $(WHITE)• 📂 Exec path       :$(RESET) $(CYAN)$(NAME_BONUS)$(RESET)\n"; \
	printf "  $(WHITE)• 🕒 Date           :$(RESET) $(CYAN)$$build_date$(RESET)\n"

# ------------------------------------------------------------------------------
# Test runner
# ------------------------------------------------------------------------------
$(TEST_RUNNER): $(TEST_SRC_FILES) test_runner.c $(SRC_FILES)
	@printf "\033[2K\r$(YELLOW)→ Building test runner...$(RESET)\n"
	@echo "DEBUG: SRC_FILES = $(SRC_FILES)"
	@echo "DEBUG: TEST_SRC_FILES = $(TEST_SRC_FILES)"
	@echo "DEBUG: Compilation command:"
	@echo "$(CC) $(CFLAGS)  -o $(TEST_RUNNER) test_runner.c $(PTHREAD)"
	@$(CC) $(CFLAGS)  -o $(TEST_RUNNER) test_runner.c $(TEST_SRC_FILES) $(PTHREAD)
	@printf "\033[2K\r$(BOLD)$(GREEN)✔ Test runner built successfully$(RESET)\n"
	@printf "\033[1;96m%b$(RESET)\n" "\
████████╗███████╗███████╗████████╗    ██████╗ ██╗   ██╗███╗   ██╗███╗   ██╗███████╗██████╗ \n \
╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝    ██╔══██╗██║   ██║████╗  ██║████╗  ██║██╔════╝██╔══██╗\n \
   ██║   █████╗  ███████╗   ██║       ██████╔╝██║   ██║██╔██╗ ██║██╔██╗ ██║█████╗  ██████╔╝\n \
   ██║   ██╔══╝  ╚════██║   ██║       ██╔══██╗██║   ██║██║╚██╗██║██║╚██╗██║██╔══╝  ██╔══██╗\n \
   ██║   ███████╗███████║   ██║       ██║  ██║╚██████╔╝██║ ╚████║██║ ╚████║███████╗██║  ██║\n \
   ╚═╝   ╚══════╝╚══════╝   ╚═╝       ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝\n"; \
	printf "\033[0;92m🧪 Ready to test your philosophers!$(RESET)\n"; \
	test_count=$$(echo $(TEST_SRC_FILES) | wc -w); \
	printf "\n$(BOLD)🔬 Test summary:$(RESET)\n"; \
	printf "  $(WHITE)• 📝 Test files      :$(RESET) $(GREEN)$$test_count$(RESET)\n"; \
	printf "  $(WHITE)• 🚀 Run command     :$(RESET) $(CYAN)./$(TEST_RUNNER)$(RESET)\n"

test_runner: $(TEST_RUNNER)

# ------------------------------------------------------------------------------
# Compilation générique
# ------------------------------------------------------------------------------
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "\033[2K\r$(BLUE)Compiling $< → $@$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "\033[2K\r$(GREEN)✔ Compiled $<$(RESET)\n"

$(OBJ_DIR)/bonus_%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "\033[2K\r$(BLUE)Compiling bonus $< → $@$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@
	@printf "\033[2K\r$(GREEN)✔ Compiled bonus $<$(RESET)\n"

# ------------------------------------------------------------------------------
# Nettoyage
# ------------------------------------------------------------------------------
clean:
	@printf "\033[2K\r$(RED)→ Removing object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r logs
	@printf "\033[2K\r$(GREEN)✔ Cleaned object files$(RESET)\n"

fclean: clean
	@printf "\033[2K\r$(RED)→ Removing executables...$(RESET)"
	@$(RM) $(NAME) $(NAME_BONUS) $(TEST_RUNNER)
	@printf "\033[2K\r$(GREEN)✔ Removed executables$(RESET)\n"
	@$(RM) -r ./output
	@printf "\033[2K\r$(GREEN)✔ Removed output dir$(RESET)\n"

re: fclean all

# ------------------------------------------------------------------------------
# Utilitaires de développement
# ------------------------------------------------------------------------------
valgrind: $(NAME)
	@printf "$(YELLOW)🧼 Running Valgrind memory check...$(RESET)\n"
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --track-origins=yes --log-file="valgrind.log" ./$(NAME) 5 800 200 200 12

test: $(TEST_RUNNER)
	@printf "$(CYAN)🧪 Running philosophers tests...$(RESET)\n"
	@./$(TEST_RUNNER)

norm:
	@printf "$(YELLOW)📏 Checking norm...$(RESET)\n"
	@norminette $(SRC_DIR) header | grep -E "(Error|Warning)" || printf "$(GREEN)✔ All files are norm compliant!$(RESET)\n"

help:
	@printf "$(BOLD)🍝 PHILOSOPHERS MAKEFILE HELP$(RESET)\n\n"
	@printf "$(BOLD)Main targets:$(RESET)\n"
	@printf "  $(GREEN)all$(RESET)          - Build main executable ($(NAME))\n"
	@printf "  $(GREEN)bonus$(RESET)        - Build bonus executable ($(NAME_BONUS))\n"
	@printf "  $(GREEN)test_runner$(RESET)  - Build test suite\n"
	@printf "  $(GREEN)clean$(RESET)        - Remove object files\n"
	@printf "  $(GREEN)fclean$(RESET)       - Remove all generated files\n"
	@printf "  $(GREEN)re$(RESET)           - Rebuild everything\n\n"
	@printf "$(BOLD)Development targets:$(RESET)\n"
	@printf "  $(GREEN)test$(RESET)         - Run test suite\n"
	@printf "  $(GREEN)valgrind$(RESET)     - Run with Valgrind\n"
	@printf "  $(GREEN)norm$(RESET)         - Check norm compliance\n"
	@printf "  $(GREEN)help$(RESET)         - Show this help\n\n"
	@printf "$(BOLD)Usage examples:$(RESET)\n"
	@printf "  $(CYAN)make && ./philo 4 410 200 200$(RESET)\n"
	@printf "  $(CYAN)make test$(RESET)\n"
	@printf "  $(CYAN)make bonus && ./philo_bonus 5 800 200 200 7$(RESET)\n"

# ------------------------------------------------------------------------------
# Cibles phony
# ------------------------------------------------------------------------------
.PHONY: all clean fclean re bonus test_runner test valgrind norm help