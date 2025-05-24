# ------------------------------------------------------------------------------
# Configuration principale
# ------------------------------------------------------------------------------

NAME        = philo
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
LDFLAGS     = -lpthread

# Répertoires
SRC_DIR     = sources
OBJ_DIR     = objects
INC_DIR     = header
TEST_DIR    = tests
OUTPUT_DIR  = output

INCLUDES    = -I$(INC_DIR)

# Commandes pratiques
MKDIR       = mkdir -p
RM          = rm -f

# Couleurs
GREEN       = \033[0;92m
RED         = \033[0;91m
BLUE        = \033[0;94m
CYAN        = \033[0;96m
LIGHT_CYAN  = \033[1;96m
RESET       = \033[0m
BOLD        = \033[1m

# ------------------------------------------------------------------------------
# Sources & Objets
# ------------------------------------------------------------------------------

# Version normale
SRC_FILES := main init utils memory mini_libft parsing time print philosopher monitor simulation philo_action
OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

# Version animée
SRC_FILES_ANIM := main init_anim utils memory mini_libft parsing time print_anim philosopher monitor_anim simulation_anim animation animation_utils philo_action
OBJ_FILES_ANIM := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES_ANIM)))

# Tests
TEST_FILES := test1 test2 test3 test4 test5
TEST_SRCS := $(addprefix $(TEST_DIR)/, $(addsuffix .c, $(TEST_FILES))) \
			 $(SRC_DIR)/init.c \
			 $(SRC_DIR)/memory.c \
			 $(SRC_DIR)/mini_libft.c \
			 $(SRC_DIR)/parsing.c \
			 $(SRC_DIR)/time.c \
			 $(SRC_DIR)/print.c \
			 $(SRC_DIR)/philosopher.c \
			 $(SRC_DIR)/monitor.c \
			 $(SRC_DIR)/simulation.c \
			 $(SRC_DIR)/utils.c \
			 $(SRC_DIR)/philo_action \
			 ./test_runner.c

# ------------------------------------------------------------------------------
# Cibles principales
# ------------------------------------------------------------------------------

all: dirs $(NAME)

dirs:
	@$(MKDIR) $(OUTPUT_DIR) $(OBJ_DIR)

$(NAME): $(OBJ_FILES)
	@echo "$(CYAN)→ Linking $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $^ $(LDFLAGS)
	@echo "$(BOLD)$(GREEN)✔ Finished building $(NAME)$(RESET)"

# Version animée
anim: dirs $(OBJ_FILES_ANIM)
	@echo "$(CYAN)→ Linking $(NAME) with animation...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -lm -o $(NAME) $(OBJ_FILES_ANIM) $(LDFLAGS)
	@echo "$(BOLD)$(GREEN)✔ Finished building animated $(NAME)$(RESET)"
	@echo "$(LIGHT_CYAN)🎬 Run with: ./$(NAME) [args]$(RESET)"

# ------------------------------------------------------------------------------
# Compilation générique
# ------------------------------------------------------------------------------

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(BLUE)Compiling $< → $@$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation spéciale pour les fichiers animés
$(OBJ_DIR)/init_anim.o: $(SRC_DIR)/init_anim.c
	@echo "$(BLUE)Compiling $< → $@ $(CYAN)(animated)$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/print_anim.o: $(SRC_DIR)/print_anim.c
	@echo "$(BLUE)Compiling $< → $@ $(CYAN)(animated)$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/monitor_anim.o: $(SRC_DIR)/monitor_anim.c
	@echo "$(BLUE)Compiling $< → $@ $(CYAN)(animated)$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/simulation_anim.o: $(SRC_DIR)/simulation_anim.c
	@echo "$(BLUE)Compiling $< → $@ $(CYAN)(animated)$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/animation.o: $(SRC_DIR)/animation.c
	@echo "$(BLUE)Compiling $< → $@ $(CYAN)(animated)$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/animation_utils.o: $(SRC_DIR)/animation_utils.c
	@echo "$(BLUE)Compiling $< → $@ $(CYAN)(animated)$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

test_runner: $(TEST_SRCS)
	@echo "$(CYAN)→ Building test runner...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) 

tests: test_runner
	./test_runner

# ------------------------------------------------------------------------------
# Nettoyage
# ------------------------------------------------------------------------------

clean:
	@echo "$(RED)→ Cleaning object files...$(RESET)"
	$(RM) -r $(OBJ_DIR)

fclean: clean
	@echo "$(RED)→ Removing binaries...$(RESET)"
	$(RM) $(NAME) test_runner

re: fclean all

# ------------------------------------------------------------------------------
# Phony
# ------------------------------------------------------------------------------

.PHONY: all clean fclean re tests anim