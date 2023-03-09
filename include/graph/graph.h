#pragma once

#include <memory>
#include <vector>

// #include "graph/edge.h"
// #include "graph/node.h"
#include "utils/tracing.h"

using std::optional;
using std::unique_ptr;
using std::vector;

using sf::Sprite;
using sf::Texture;
using sf::Vector2f;

/// @brief Graph-related data structures and algorithms (e.g. Dijkstra's, A*,
/// nodes, edges, adjaceny matrices, etc.)
namespace graph {

class Node;
class Edge;

// ---------------------------------------------------------------------------
// Graph
// ---------------------------------------------------------------------------

// class Graph {
//    public:
//     Graph() = default;
//     Graph(const Graph& other) = delete;
//     Graph(Graph&& other) = delete;
//     auto operator=(const Graph& other) -> Graph& = delete;
//     auto operator=(Graph&& other) -> Graph& = delete;
//     ~Graph() = default;

//     auto add_node(unique_ptr<Node> node) -> void {
//         m_nodes.push_back(std::move(node));
//     }

//     auto add_edge(unique_ptr<Edge> edge) -> void {
//         m_edges.push_back(std::move(edge));
//     }

//     auto render() -> void {
//         for (const auto& node : m_nodes) {
//             node->render();
//         }
//     }

//    private:
//     std::vector<std::unique_ptr<Node>> m_nodes;
//     std::vector<std::unique_ptr<Edge>> m_edges;
// };

// ---------------------------------------------------------------------------
// Node
// ---------------------------------------------------------------------------

/// @brief A texture used to render nodes.
static Texture texture;

/// @brief The path to the texture used to render the node.
static constexpr string_view node_texture_path = "assets/node.png";

/// @brief The initial capacity of the vector of adjacent nodes.
static constexpr int32_t INITIAL_ADJACENT_NODES_CAPACITY = 10;

/// @brief The initial capacity of the vector of adjacent edges.
static constexpr int32_t INITIAL_ADJACENT_EDGES_CAPACITY = 10;

/// @brief Generates a random position within the window.
/// @return A random position within the window.
auto random_position() -> Vector2f {
    return Vector2f(static_cast<float>(rand() % config::WINDOW_HEIGHT),
                    static_cast<float>(rand() % config::WINDOW_WIDTH));
}

/// A node in a graph that can be visited by a graph search algorithm
/// (e.g. Dijkstra's algorithm, A* algorithm, etc.)
///
/// Nodes are connected to other nodes via edges (see Edge class).
///
/// Nodes contain a position, a cost, a heuristic, parent node, vector of
/// adjacent nodes, and vector of adjacent edges.
///
/// They can be rendered to the screen using the render() method.
class Node {
   public:
    /// @brief Constructs a node with no parent, cost, or
    /// heuristic.
    Node()
        : m_parent(nullptr),
          m_cost(0),
          m_heuristic(0),
          m_position(random_position()) {
        build_node();
    }

    /// @brief Constructs a node with the given parent,
    /// cost, heuristic, and position.
    Node(unique_ptr<Node> parent, float cost, float heuristic,
         Vector2f position)
        : m_parent(std::move(parent)),
          m_cost(cost),
          m_heuristic(heuristic),
          m_position(position) {
        build_node();
    }

    /// @brief Constructs a node with the given parent,
    /// cost, and heuristic. The position of the node is
    /// randomly generated.
    Node(unique_ptr<Node> parent, float cost, float heuristic)
        : m_parent(std::move(parent)),
          m_cost(cost),
          m_heuristic(heuristic),
          m_position(random_position()) {
        build_node();
    }

    /// @brief Constructs a node with the given cost and
    /// heuristic. The node has no parent and the position
    /// of the node is randomly generated.
    Node(float cost, float heuristic)
        : m_parent(nullptr),
          m_cost(cost),
          m_heuristic(heuristic),
          m_position(random_position()) {
        build_node();
    }

    /// @brief Node destructor.
    virtual ~Node() {
        tracing::trace(
            format("Node destroyed with cost {}, "
                   "heuristic {}, and "
                   "position ({}, {})",
                   m_cost, m_heuristic, m_position.x, m_position.y));
    }

    /// @brief The cost of the path from the start node
    /// to this node. This is the sum of the cost of the
    /// edges from the start node to this node.
    ///
    /// @attention This is the g(n) function in the A* algorithm.
    ///
    /// @return The cost of the path from the start node
    auto cost() const { return m_cost; }

    /// @brief Returns the heuristic cost of the path from
    ///        this node to the goal node.
    /// @return The heuristic cost of the path from this
    ///         node to the goal node.
    auto heuristic() const { return m_heuristic; }

    /// Returns the position of the node.
    auto position() const { return m_position; }

    /// @brief Returns the x-coordinate of the node.
    /// @return The x-coordinate of the node.
    auto x_coordinate() const { return m_position.x; }

    /// @brief Returns the y-coordinate of the node.
    /// @return The y-coordinate of the node.
    auto y_coordinate() const { return m_position.y; }

    /// Returns the total cost of the path from the start
    /// node to the goal node through this node. This is
    /// the sum of the cost of the edges from the start
    /// node to this node and the cost of the edges from
    /// this node to the goal node.
    auto totalCost() const { return m_cost + m_heuristic; }

    /// @brief The parent node of this node in the
    ///        path from the start node.
    /// @return The parent node of this node in the
    ///         path from the start node.
    auto& parent() const { return m_parent.value(); }

    /// @brief Sets the cost of the path from the start node
    ///        to this node.
    /// @param cost The cost of the path from the start node
    ///             to this node.
    void set_cost(float cost) { m_cost = cost; }

    /// @brief Sets the heuristic cost of the path from
    ///         this node to the goal
    /// @param heuristic The heuristic cost of the path
    ///                  from this node to the goal
    void set_heuristic(float heuristic) { m_heuristic = heuristic; }

    /// @brief Sets the parent node of this node in the
    ///        path from the start node
    /// @param parent The parent node of this node in the
    ///               path from the start node
    void set_parent(unique_ptr<Node> parent) { m_parent = std::move(parent); }

    /// @brief Sets the position of the node.
    /// @param position The position of the node.
    void set_position(Vector2f position) { m_position = position; }

    /// @brief Resets the parent of this node to nullptr.
    auto reset_parent() { m_parent = nullptr; }

    /// @brief Returns the nodes that are adjacent to this
    /// node.
    // auto adjacent_nodes() const { return m_adjacentNodes; }

    /// @brief Returns the edges that are adjacent to this
    /// node.
    // auto adjacent_edges() const { return m_adjacentEdges; }

    // /// @brief Returns the edges that are adjacent to
    // this node. const vector<Edge>& adjacentEdges()
    // const { return m_adjacentEdges; }

    /// @brief Adds the given node to the list of adjacent
    /// nodes.
    // void addAdjacentNode(Node* node) {
    //     m_adjacentNodes.push_back(node);
    //     log(LVL_DEBUG, "Added node %p to adjacent nodes
    //     of node %p", node,
    //         this);
    // }

    /// @brief Adds the given edge to the list of adjacent
    /// edges.
    // void addAdjacentEdge(Edge* edge) {
    //     m_adjacentEdges.push_back(edge);
    //     log(LVL_DEBUG, "Added edge %p to adjacent edges
    //     of node %p", edge,
    //         this);
    // }

    /// @brief Returns the number of adjacent nodes.
    // int numAdjacentNodes() const { return
    // m_adjacentNodes.size(); }

    // /// @brief Returns the number of adjacent edges.
    // int numAdjacentEdges() const { return
    // m_adjacentEdges.size(); }

    /// @brief Returns the adjacent node at the given
    /// index.
    /// @pre The given index is non-negative and less than
    /// the number of adjacent nodes.
    // Node* adjacentNodeAt(int index) const {
    //     assert(index >= 0 && index <
    //     numAdjacentNodes()); return
    //     m_adjacentNodes[index];
    // }

    /// @brief Returns the adjacent edge at the given
    /// index.
    /// @pre The given index is non-negative and less than
    /// the number of adjacent edges.
    // Edge* adjacentEdgeAt(int index) const {
    //     assert(index >= 0 && index <
    //     numAdjacentEdges()); return
    //     m_adjacentEdges[index];
    // }

   private:
    /// @brief The parent node of this node in the path
    /// from the start node to this node.
    optional<unique_ptr<Node>> m_parent;

    /// @brief The cost of the path from the start node to
    /// this node.
    float m_cost;

    /// @brief The heuristic cost of the path from this
    /// node to the goal node.
    float m_heuristic;

    /// @brief The position of this node.
    Vector2f m_position;

    /// @brief The nodes that are adjacent to this node.
    vector<unique_ptr<Node>> m_adjacentNodes;

    /// @brief The edges that are adjacent to this node.
    vector<unique_ptr<Edge>> m_adjacentEdges;

    /// @brief The sprite for the boid (used for drawing)
    Sprite sprite;

    /// @brief Trace the initialization of the node (i.e. the node's cost,
    ///        heuristic, position, etc.)
    auto trace_init() -> void {
        tracing::debug(format("Node created with cost {}, and heuristic {}",
                              cost(), heuristic()));
        tracing::debug(
            format("Node position: ({}, {})", x_coordinate(), y_coordinate()));
    }

    /// @brief Build the node.
    auto build_node() -> void {
        trace_init();

        sprite = Sprite();
        sprite.setTexture(texture);
        // TODO: here we need to set the origin of the sprite to the center of
        // the texture
        // sprite.setOrigin(sprite.getTextureRect().width / 2,
        //                  sprite.getTextureRect().height / 2);
        // sprite.setPosition(position.x, position.y);

        // adjacent_nodes().reserve(INITIAL_ADJACENT_NODES_CAPACITY);
        // adjacent_edges().reserve(INITIAL_ADJACENT_EDGES_CAPACITY);
    }
};

// --------------------------------------------------------------------------
// Edge
// --------------------------------------------------------------------------

/// @brief Represents an infinite cost for an edge in a graph.
static constexpr int32_t INF = -1;

/// @brief An edge in a graph. An edge connects two nodes and has an associated
///        cost.
class Edge {
   public:
    Edge(unique_ptr<Node> start, unique_ptr<Node> end)
        : m_start(std::move(start)), m_end(std::move(end)) {
        // tracing::debug("Edge created with start node {} and end node {}",
        //                m_start, m_end);
    }

    auto start() const -> const auto& { return *m_start; }

    auto end() const -> const auto& { return *m_end; }

    auto set_start(unique_ptr<Node> start) -> void {
        m_start = std::move(start);
    }

    auto set_end(unique_ptr<Node> end) -> void { m_end = std::move(end); }

    auto cost() const -> float { return m_cost; }

    auto set_cost(float cost) -> void { m_cost = cost; }

    // auto len() const -> float { return m_start->dist(*m_end); }

    // auto angle() const -> float { return m_start->angle(*m_end); }

    auto operator<(const Edge& other) const -> bool {
        return m_cost < other.m_cost;
    }

    auto operator==(const Edge& other) const -> bool {
        return m_start == other.m_start && m_end == other.m_end;
    }

   private:
    /// @brief The start node of this edge.
    unique_ptr<Node> m_start;
    /// @brief The end node of this edge.
    unique_ptr<Node> m_end;
    /// @brief The cost of this edge.
    float m_cost = INFINITY;

    /// @brief Prints the edge to the given output stream.
    /// @param os The output stream to print to.
    /// @param edge The edge to print.
    /// @return The output stream.
    // friend auto operator<<(std::ostream& os, const Edge& edge)
    //     -> std::ostream& {
    //     os << "Edge(" << edge.start() << "->" << edge.end() << ")";
    //     return os;
    // }
};
}  // namespace graph
