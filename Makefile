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
RESET       = \033[0m
BOLD        = \033[1m

# ------------------------------------------------------------------------------
# Sources & Objets
# ------------------------------------------------------------------------------

SRC_FILES := main init
OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

# Tests
TEST_FILES := test1
TEST_SRCS := $(addprefix $(TEST_DIR)/, $(addsuffix .c, $(TEST_FILES))) \
			 $(SRC_DIR)/init.c \
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

# ------------------------------------------------------------------------------
# Compilation générique
# ------------------------------------------------------------------------------

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(BLUE)Compiling $< → $@$(RESET)"
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

.PHONY: all clean fclean re tests