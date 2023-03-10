#------------------------------------------------------------
# Utility functions
#------------------------------------------------------------

# Recursive wildcard function (https://stackoverflow.com/a/18258352)
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))