import pygame

# Initialize Pygame
pygame.init()
screen = pygame.display.set_mode((800, 600))

# Define colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

# Define graph and nodes
graph = {
    'A': {'B': 1, 'C': 4},
    'B': {'A': 1, 'C': 2, 'D': 5},
    'C': {'A': 4, 'B': 2, 'D': 1},
    'D': {'B': 5, 'C': 1}
}
nodes = {
    'A': (100, 100),
    'B': (200, 100),
    'C': (150, 200),
    'D': (250, 200)
}

# Define font
font = pygame.font.SysFont(None, 24)

# Game loop
source_node = None
destination_node = None
while True:
    # Handle events
    for event in pygame.event.get():
        if