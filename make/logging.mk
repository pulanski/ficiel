#------------------------------------------------------------
# Logging utilities
#------------------------------------------------------------

# Regular Colors
GREEN=\033[0;32m # Green
CYAN=\033[0;36m # Cyan
BLACK=\033[0;30m # Black
GRAY=\033[0;37m # Gray
RED=\033[0;31m # Red
BLUE=\033[0;34m # Blue

# Background
ON_GREEN=\033[42m # Green Background
ON_YELLOW=\033[43m # Yellow Background
ON_BLUE=\033[44m # Blue Background

RESET=\033[0m # Text Reset

# Info message (e.g. "INFO Compiling main.cc...")
define INFO
	@echo "$(ON_YELLOW)INFO $(GRAY)    $1$(GRAY)... $(RESET)"
endef

# Note message (e.g. "NOTE main.cc compiled successfully...")
define NOTE
	@echo "$(ON_BLUE)NOTE $(GRAY)    $1$(GRAY)... $(RESET)"
endef

# Error message (e.g. "ERROR main.cc failed to compile...")
define ERROR
	@echo "$(ON_RED)ERROR $(GRAY)   $1$(GRAY)... $(RESET)"
endef

# Success message
define SUCCESS
	@echo "$(ON_GREEN)SUCCESS $(CYAN)$1$(GRAY)... $(RESET)"
endef