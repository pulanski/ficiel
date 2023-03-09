#------------------------------------------------------------
# Compiler and linker flags
#------------------------------------------------------------

# Compiler (clang++ or g++ depending on OS)
MACOS_COMPILER=/usr/bin/clang++
UBUNTU_COMPILER=/usr/bin/g++

# Linker flags
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system