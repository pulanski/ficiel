import pygame
from collections import deque
import random

# Define some colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

# Set the dimensions of the screen
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600

# Set the margin for each node
MARGIN = 20

# Set the radius for each node
RADIUS = 20


class Pos:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        return Pos(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return Pos(self.x - other.x, self.y - other.y)

    def __mul__(self, other):
        return Pos(self.x * other, self.y * other)

    def __truediv__(self, other):
        return Pos(self.x / other, self.y / other)

    def __floordiv__(self, other):
        return Pos(self.x // other, self.y // other)

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __hash__(self):
        return hash((self.x, self.y))

    


class Node:
    def __init__(self, id, pos):
        self.id = id
        self.pos = pos
        self.neighbors = []
        self.dist = float("inf")
        self.visited = False
        self.parent = None

    def __lt__(self, other):
        return self.dist < other.dist

    def draw(self, screen):
        pygame.draw.circle(screen, BLUE, self.pos, RADIUS)
        font = pygame.font.SysFont(None, 24)
        text = font.render(str(self.id), True, WHITE)
        screen.blit(
            text,
            (self.pos[0] - RADIUS // 2, self.pos[1] - RADIUS // 2),
        )

    def draw_path(self, screen):
        if self.parent:
            pygame.draw.line(
                screen, RED, self.pos, self.parent.pos, 2
            )
            self.parent.draw_path(screen)

    def draw_neighbors(self, screen):
        for neighbor in self.neighbors:
            pygame.draw.line(screen, GREEN, self.pos, neighbor.pos, 2)
            neighbor.draw(screen)
            neighbor.draw_neighbors(screen)

    def draw_visited(self, screen):
        if self.visited:
            pygame.draw.circle(screen, RED, self.pos, RADIUS, 2)
            for neighbor in self.neighbors:
                neighbor.draw_visited(screen)

    def draw_distance(self, screen):
        font = pygame.font.SysFont(None, 24)
        text = font.render(str(self.dist), True, WHITE)
        screen.blit(
            text,
            (self.pos[0] - RADIUS // 2, self.pos[1] - RADIUS // 2),
        )

    def add_neighbor(self, neighbor):
        self.neighbors.append(neighbor)

    def __str__(self):
        return f"Node {self.id} at {self.pos}"


def generate_graph(num_nodes, num_edges, width, height):
    nodes = [
        Node(
            i,
            (
                random.randint(10, width - 10),
                random.randint(10, height - 10),
            ),
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


def dijkstra(graph, start_node, end_node):
    for node in graph:
        node.dist = float("inf")
        node.prev = None

    start_node.dist = 0
    heap = list(graph)
    queue = deque()
    queue.append(start_node)

    while queue:
        node = queue.popleft()

        if node == end_node:
            path = []
            while node:
                path.append(node)
                node = node.prev
            return path[::-1]

        for neighbor in node.neighbors:
            alt = node.dist + 1
            if alt < neighbor.dist:
                neighbor.dist = alt
                neighbor.prev = node

        heap.sort()

        for node in heap:
            if node.dist == float("inf"):
                break
            heap.remove(node)
            queue.append(node)


def draw_nodes(screen, nodes, start_node, end_node, path):
    screen.fill((255, 255, 255))

    for node in nodes:
        color = (0, 0, 0)
        if node == start_node:
            color = (0, 255, 0)
        elif node == end_node:
            color = (255, 0, 0)
        elif node in path:
            color = (0, 0, 255)

        pygame.draw.circle(screen, color, node.pos, 10)

        for neighbor in node.neighbors:
            pygame.draw.line(
                screen, (200, 200, 200), node.pos, neighbor.pos, 2
            )

    pygame.display.flip()


def main():
    pygame.init()

    width, height = 800, 600
    screen = pygame.display.set_mode((width, height))

    num_nodes = 20
    num_edges = 30

    nodes = generate_graph(num_nodes, num_edges, width, height)
    start_node, end_node = None, None
    path = []

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        #     elif event.type == pygame.MOUSEBUTTONDOWN:
        #         pos = pygame.mouse.get_pos()

        #         clicked_node = None
        #         for node in nodes:
        #             if (node.pos[0] - pos[0]) ** 2 + (
        #                 node.pos[1] - pos[1]
        #             ) ** 2 <= 10**2:
        #                 clicked_node = node

        #         if not start_node:
        #             start_node = clicked_node
        #             start_node.dist = 0
        #         elif not end_node and clicked_node != start_node:
        #             end_node = clicked_node
        #             path = dijkstra(nodes, start_node, end_node)
        #         else:
        #             start_node, end_node = None, None
        #             for node in nodes:
        #                 node.dist = float("inf")
        #                 node.prev = None

        # # Clear the screen
        # screen.fill((255, 255, 255))

        # # Draw the edges
        # for node in nodes:
        #     for neighbor, weight in node.edges:
        #         pygame.draw.line(
        #             screen, (0, 0, 0), node.pos, neighbor.pos, 2
        #         )

        # # Draw the nodes
        # for node in nodes:
        #     pygame.draw.circle(screen, (0, 0, 255), node.pos, 10)
        #     if node == start_node:
        #         pygame.draw.circle(screen, (0, 255, 0), node.pos, 10)
        #     elif node == end_node:
        #         pygame.draw.circle(screen, (255, 0, 0), node.pos, 10)

        # # Draw the path
        # for i in range(len(path) - 1):
        #     pygame.draw.line(
        #         screen, (255, 0, 0), path[i].pos, path[i + 1].pos, 4
        #     )

        # Update the display
        pygame.display.flip()
