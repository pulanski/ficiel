#------------------------------------------------------------
# Libraries
#------------------------------------------------------------

include make/logging.mk # logging
include make/utils.mk   # utils
include make/lib.mk     # lib paths
include make/flags.mk   # compiler flags
include make/common.mk  # common (config)

#------------------------------------------------------------
# Source files
#------------------------------------------------------------

# Source files
SRCS := $(call rwildcard,./,*.cc) $(call rwildcard,../common/,*.cc) # plus common files
# Object files
OBJS = $(patsubst %.cc,%.o,$(SRCS))

#------------------------------------------------------------
# Build rules
#------------------------------------------------------------

# Build all
build: $(main_target)

# Build executable
$(main_target): $(OBJS)
	$(Q)$(call INFO, $(addprefix Linking$(CYAN),$@))
ifeq ($(uname_s),Darwin)
	@$(MACOS_COMPILER) -std=c++$(CPP_VERSION) -o $@ $^ $(LDFLAGS) $(MACOS_LIB)
else ifeq ($(uname_s),Linux)
	@$(UBUNTU_COMPILER) -std=c++$(CPP_VERSION) -o $@ $^ $(LDFLAGS) $(UBUNTU_LIB)
endif
# check if linking was successful
ifeq ($(shell echo $$?),0)
	$(call SUCCESS, $(addprefix $(GREEN)Executable$(CYAN),$@)$(GREEN)built successfully)
	$(call NOTE, You can run the executable$(CYAN)$@$(GRAY)with$(BLUE)make run)
else
	$(call ERROR, $(addprefix $(RED)Executable$(CYAN),$@)$(RED)failed to build)
endif
# Move all object files to the build directory
	@mkdir -p ./build
	@mv $(OBJS) ./build

# Build objects
uname_s := $(shell uname -s)
%.o: %.$(FILE_EXTENSION)
	$(call INFO, $(addprefix Compiling$(CYAN),$^))
ifeq ($(uname_s),Darwin)
	@$(MACOS_COMPILER) -std=c++$(CPP_VERSION) -c $^ -o $@ $(MACOS_INCLUDE) $(GENERAL_INCLUDE) $(THIRD_PARTY_INCLUDE)
else ifeq ($(uname_s),Linux)
	@$(UBUNTU_COMPILER) -std=c++$(CPP_VERSION) -c $^ -o $@ $(UBUNTU_INCLUDE) $(GENERAL_INCLUDE) $(THIRD_PARTY_INCLUDE)
endif
# check if compilation was successful
ifeq ($(shell echo $$?),0)
	$(call SUCCESS, $(addprefix $(GREEN)Object$(CYAN),$@)$(GREEN)built successfully$(CYAN))
else
	$(call ERROR, $(addprefix $(RED)Object$(CYAN),$@)$(RED)failed to build$(CYAN))
endif

#------------------------------------------------------------
# Clean rules
#------------------------------------------------------------

# Clean
.PHONY: clean
clean:
	@rm -f $(OBJS) main > /dev/null 2>&1
	@rm -rf ./build > /dev/null 2>&1
# check if clean was successful
ifeq ($(shell echo $$?),0)
	$(call SUCCESS, $(addprefix $(GREEN)Executable$(CYAN),$(main_target))$(GREEN)cleaned successfully)
else
	$(call ERROR, $(addprefix $(RED)Executable$(CYAN),$(main_target) $(RED)failed to clean$(GRAY)...$(RESET)))
endif

#------------------------------------------------------------
# Run rules
#------------------------------------------------------------

# Run
.PHONY: run
run: $(main_target)
	$(call INFO, $(addprefix Running$(CYAN),$(main_target)))
	@./$(main_target) $(ARGS)
