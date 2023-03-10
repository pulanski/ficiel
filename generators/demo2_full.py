import pygame
import random
import heapq

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

# Set the font for the labels
FONT = pygame.font.SysFont(None, 24)


class Node:
    def __init__(self, id, x, y):
        self.id = id
        self.neighbors = []
        self.distance = float("inf")
        self.visited = False
        self.parent = None
        self.x = x
        self.y = y

    def add_neighbor(self, neighbor):
        self.neighbors.append(neighbor)

    def __lt__(self, other):
        return self.distance < other.distance


class Graph:
    def __init__(self):
        self.nodes = []
        self.edges = []

    def add_node(self, node):
        self.nodes.append(node)

    def add_edge(self, node1, node2, weight):
        node1.add_neighbor((node2, weight))
        node2.add_neighbor((node1, weight))
        self.edges.append((node1, node2))

    def dijkstra(self, start_node, end_node):
        heap = []
        start_node.distance = 0
        heapq.heappush(heap, start_node)

        while heap:
            current_node = heapq.heappop(heap)
            current_node.visited = True

            for neighbor, weight in current_node.neighbors:
                if not neighbor.visited:
                    new_distance = current_node.distance + weight
                    if new_distance < neighbor.distance:
                        neighbor.distance = new_distance
                        neighbor.parent = current_node
                        heapq.heappush(heap, neighbor)

        path = []
        node = end_node
        while node.parent:
            path.append(node)
            node = node.parent
        path.append(start_node)
        path.reverse()

        return path

    def draw(self, screen, path=None):
        screen.fill(WHITE)

        for edge in self.edges:
            pygame.draw.line(screen, BLACK, (edge[0].x, edge[0].y), (edge[1].x, edge[1].y), 2)

        for node in self.nodes:
            pygame.draw.circle(screen, BLUE, (node.x, node.y), RADIUS)

            label = FONT.render(str(node.id), True, WHITE)
            text_rect = label.get_rect(center=(node.x, node.y))
            screen.blit(label, text_rect)

            if node.distance != float("inf"):
                label = FONT.render(str(node.distance), True, GREEN)
                text_rect = label.get_rect(center=(node.x, node.y + RADIUS + MARGIN))
                screen.blit(label, text_rect)

            if path and node in path:
                pygame.draw.circle(screen, RED, (node.x, node.y), RADIUS // 2)

        pygame.display.flip()

    def get_node_by_pos(self, x, y):
        for node in self.nodes:
            if (x - node.x) ** 2 + (y - node.y) ** 2 <= RADIUS ** 2:
                return node
        return None


def main():
    # Initialize Pygame
    pygame.init()

    # Set the size of the screen
    screen = pygame.display.set_mode((SCREEN