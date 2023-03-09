from collections import deque
import random


class Node:
    def __init__(self, id):
        self.id = id
        self.neighbors = []


def generate_graph(num_nodes, num_edges):
    nodes = [Node(i) for i in range(num_nodes)]
    edges = 0

    while edges < num_edges:
        node1, node2 = random.sample(nodes, 2)
        print(f"node1: {node1.id}, node2: {node2.id}")
        if node2 not in node1.neighbors and node1 != node2:
            print(f"adding edge between {node1.id} and {node2.id}")
            node1.neighbors.append(node2)
            node2.neighbors.append(node1)
            edges += 1

    return nodes


# Display the graph using DFS
# in a recursive manner
#
# Time complexity: O(V + E)
#
# Space complexity: O(V)
#
# V: number of vertices
# E: number of edges
def display_tree(root):
    stack = [(root, 0)]
    seen = set()

    while stack:

        node, depth = stack.pop()
        if node in seen:
            continue

        print("|  " * depth, end="")
        print("|--({})".format(node.id))
        for neighbor in node.neighbors[::-1]:
            stack.append((neighbor, depth + 1))

        seen.add(node)


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
display_tree(root)
