import pygame
from collections import deque
import random

# Constants for drawing the graph
WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600
NODE_RADIUS = 20
NODE_COLOR = (0, 0, 255)
EDGE_COLOR = (255, 0, 0)
FONT_SIZE = 20


class Node:
    def __init__(self, id, x, y):
        self.id = id
        self.neighbors = []
        self.x = x
        self.y = y

    def draw(self, screen):
        pygame.draw.circle(
            screen, NODE_COLOR, (self.x, self.y), NODE_RADIUS
        )
        font = pygame.font.SysFont(None, FONT_SIZE)
        text = font.render(str(self.id), True, (255, 255, 255))
        screen.blit(
            text,
            (self.x - NODE_RADIUS // 2, self.y - NODE_RADIUS // 2),
        )


def generate_graph(num_nodes, num_edges):
    nodes = [
        Node(
            i,
            random.randint(NODE_RADIUS, WINDOW_WIDTH - NODE_RADIUS),
            random.randint(NODE_RADIUS, WINDOW_HEIGHT - NODE_RADIUS),
        )
        for i in range(num_nodes)
    ]
    edges = 0

    while edges < num_edges:
        node1, node2 = random.sample(nodes, 2)
        if node2 not in node1.neighbors and node1 != node2:
            node1.neighbors.append(node2)
            node2.neighbors.append(node1)
            edges += 1

    return nodes


def display_tree(screen, root):
    stack = [(root, 0)]
    seen = set()

    while stack:

        node, depth = stack.pop()
        if node in seen:
            continue

        node.draw(screen)

        for neighbor in node.neighbors:
            if neighbor not in seen:
                pygame.draw.line(
                    screen,
                    EDGE_COLOR,
                    (node.x, node.y),
                    (neighbor.x, neighbor.y),
                )
            stack.append((neighbor, depth + 1))

        seen.add(node)


pygame.init()
screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
pygame.display.set_caption("Graph Display")
clock = pygame.time.Clock()

# prompt user for number of nodes and edges
num_nodes = int(input("Enter number of nodes: "))
num_edges = int(input("Enter number of edges: "))

nodes = generate_graph(num_nodes, num_edges)

# randomize the root node (if it has no neighbors, re-randomize)
while True:
    root = random.choice(nodes)
    if root.neighbors:
        break

print("Graph generated:")

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill((255, 255, 255))
    display_tree(screen, root)
    pygame.display.update()
    clock.tick(60)

pygame.quit()
