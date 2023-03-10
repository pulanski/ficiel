#pragma once

#include <memory>
#include <vector>

// #include "graph/edge.h"
// #include "graph/node.h"
#include "utils/tracing.h"

using std::make_unique;
using std::optional;
using std::unique_ptr;
using std::vector;

using sf::Color;
using sf::IntRect;
using sf::RenderWindow;
using sf::Sprite;
using sf::Text;
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

// ---------------------------------------------------------------------------
// Node
// ---------------------------------------------------------------------------

// /// @brief A texture used to render nodes.
// static Texture texture;

// /// @brief The path to the texture used to render the node.
// static constexpr string_view node_texture_path = "assets/node.png";

/// @brief The initial capacity of the graph's nodes vector (i.e. the number of
/// nodes that can be added to the graph before the vector is resized) as well
/// as the initial capacity of the graph's edges vector (i.e. the number of
/// edges that can be added to the graph before the vector is resized).
static constexpr int32_t INITIAL_GRAPH_CAPACITY = 100;

/// @brief Generates a random position within the window.
/// @return A random position within the window.
auto random_position() -> Vector2f {
  return Vector2f(static_cast<float>(rand() % config::WINDOW_HEIGHT),
                  static_cast<float>(rand() % config::PROD_WINDOW_WIDTH));
}

/// @brief Calculates the distance between two points.
/// @param a The first point.
/// @param b The second point.
/// @return The distance between the two points.
auto distance_between(Vector2f a, Vector2f b) -> float {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
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
  /// @brief Constructs a node with a given position.
  Node(RenderWindow& window, Texture& texture, Vector2f position,
       float cost = 0.0f, float heuristic = 0.0f)
      : window_(&window),
        position_(position),
        cost_(cost),
        heuristic_(heuristic) {
    sprite_.setTexture(texture);
    sprite_.setPosition(position_);
    sprite_.scale(4.f, 4.f);
    // m_sprite.scale(0.05f, 0.05f);

    incoming_edges_.reserve(INITIAL_GRAPH_CAPACITY / 10);
    outgoing_edges_.reserve(INITIAL_GRAPH_CAPACITY / 10);

    // build_node();
  }

  /// @brief Node destructor.
  virtual ~Node() {
    tracing::trace(
        format("Node destroyed with cost {}, "
               "heuristic {}, and "
               "position ({}, {})",
               cost_, heuristic_, position_.x, position_.y));
  }

  /// @brief The cost of the path from the start node
  /// to this node. This is the sum of the cost of the
  /// edges from the start node to this node.
  ///
  /// @attention This is the g(n) function in the A* algorithm.
  ///
  /// @return The cost of the path from the start node
  inline auto cost() const { return cost_; }

  /// @brief Returns the heuristic cost of the path from
  ///        this node to the goal node.
  /// @return The heuristic cost of the path from this
  ///         node to the goal node.
  inline auto heuristic() const { return heuristic_; }

  /// Returns the position of the node.
  inline auto position() const { return position_; }

  /// @brief Returns the x-coordinate of the node.
  /// @return The x-coordinate of the node.
  inline auto x() const { return position_.x; }

  /// @brief Returns the y-coordinate of the node.
  /// @return The y-coordinate of the node.
  inline auto y() const { return position_.y; }

  /// @brief The total cost of the path from the start
  ///        node to the goal node through this node.
  ///        This is the sum of the cost of the edges
  ///        from the start node to this node and the
  ///        cost of the edges from this node to the
  ///        goal node.
  /// @return
  inline auto total_cost() const { return cost_ + heuristic_; }

  /// @brief Sets the cost of the path from the start node
  ///        to this node.
  /// @param cost The cost of the path from the start node
  ///             to this node.
  inline auto set_cost(float cost) { cost_ = cost; }

  /// @brief Sets the heuristic cost of the path from
  ///         this node to the goal
  /// @param heuristic The heuristic cost of the path
  ///                  from this node to the goal
  inline auto set_heuristic(float heuristic) { heuristic_ = heuristic; }

  /// @brief Sets the position of the node.
  /// @param position The position of the node.
  inline auto set_position(Vector2f position) { position_ = position; }

  inline auto sprite() { return &sprite_; }

  /// @brief Returns the nodes that are adjacent to this
  /// node.
  // auto adjacent_nodes() const { return m_adjacentNodes; }
  // TODO: iterate over edges and collect nodes

  /// @brief Returns a reference to incoming edges to this node.
  inline auto incoming_edges() { return &incoming_edges_; }

  /// @brief The edges that are outgoing from this node (vector<Edge*>)
  inline auto outgoing_edges() { return &outgoing_edges_; }

  /// @brief Adds an incoming edge to this node.
  /// @param edge The incoming edge to add to this node.
  inline auto add_incoming_edge(Edge* edge) { incoming_edges_.push_back(edge); }

  /// @brief Adds an outgoing edge to this node.
  /// @param edge The outgoing edge to add to this node.
  inline auto add_outgoing_edge(Edge* edge) { outgoing_edges_.push_back(edge); }

  /// @brief Returns the number of incoming edges to this node.
  /// @return The number of incoming edges to this node.
  inline auto num_incoming_edges() { return incoming_edges_.size(); }

  /// @brief Returns the number of outgoing edges from this node.
  /// @return The number of outgoing edges from this node.
  inline auto num_outgoing_edges() { return outgoing_edges_.size(); }

  /// @brief Returns the number of edges connected to this node.
  /// @return The number of edges connected to this node.
  inline auto num_edges() {
    return num_incoming_edges() + num_outgoing_edges();
  }

  /// @brief Returns the distance from this node to another node.
  /// @param other The other node to calculate the distance to.
  /// @return The distance from this node to the other node.
  inline auto distance_from(Node* other) {
    return distance_between(position_, other->position_);
  }

  /// @brief Renders the node to the screen.
  inline auto render() {
    window_->draw(sprite_);
    // m_window->draw(m_text);
  }

  /// @brief Sets the color of the sprite.
  /// @param color The color to set.
  auto set_color(Color color) { sprite_.setColor(color); }

  /// @brief Sets the texture of the sprite.
  /// @param texture The texture to set.
  auto set_texture(Texture* texture) { sprite_.setTexture(*texture); }

  /// @brief Sets the texture rect of the sprite.
  /// @param rect The texture rect to set.
  auto set_texture_rect(IntRect rect) { sprite_.setTextureRect(rect); }

 private:
  /// @brief The ID of the node. This is used to
  /// uniquely identify the node in the graph and
  /// allows for fast lookup of the node in the
  /// graph as well as fast comparison of nodes.
  // u128 m_id;
  // TODO: in the future adapt to using a node registry along
  // with a node arena for fast allocation and deallocation of nodes

  /// @brief The window to draw to.
  RenderWindow* window_;

  /// @brief The position of this node.
  Vector2f position_;

  /// @brief The incoming edges to this node.
  vector<Edge*> incoming_edges_;

  /// @brief The outgoing edges from this node.
  vector<Edge*> outgoing_edges_;

  /// @brief The sprite for the boid (used for drawing)
  Sprite sprite_;

  /// @brief The text for the boid.
  Text text_;

  /// @brief The cost of the path from the start node to
  /// this node.
  float cost_;

  /// @brief The heuristic cost of the path from this
  /// node to the goal node.
  float heuristic_;

  /// @brief Trace the initialization of the node (i.e. the node's cost,
  ///        heuristic, position, etc.)
  auto trace_init() -> void {
    // inline auto trace_init() -> void {
    tracing::debug(format("Node created with cost {}, and heuristic {}", cost(),
                          heuristic()));
    tracing::debug(format("Node position: ({}, {})", x(), y()));
  }

  /// @brief Build the node.
  // auto build_node() -> void {
  //     trace_init();

  //     // m_sprite = Sprite();
  //     // m_sprite.setTexture(*m_texture);
  //     // TODO: here we need to set the origin of the sprite to the center
  //     // of the texture
  //     // m_sprite.setOrigin(m_sprite.getTextureRect().width / 2,
  //     //                    m_sprite.getTextureRect().height / 2);
  //     // m_sprite.setPosition(x(), y());

  //     // cout << "Sprite position: (" << m_sprite.getPosition().x << ", "
  //     //      << m_sprite.getPosition().y << ")" << endl;

  //     incoming_edges()->reserve(INITIAL_GRAPH_CAPACITY / 10);
  //     outgoing_edges()->reserve(INITIAL_GRAPH_CAPACITY / 10);
  // }
};

// // --------------------------------------------------------------------------
// // Edge
// // --------------------------------------------------------------------------

/// @brief Represents an infinite cost for an edge in a graph.
static constexpr int32_t INF = -1;

/// @brief An edge in a graph, can be either directed or undirected.  An
/// edge
///        connects two nodes and has an associated cost.
///
/// @tparam Node The type of the nodes that the edge connects.
/// // TODO: migrate to generic node type via template
class Edge {
 public:
  Edge(Node* start, Node* end, float cost = 0.0f)
      : m_start(start), m_end(end), m_cost(cost) {}

  // Returns a pointer to the start node of this edge.
  auto from() const { return m_start; }

  auto to() const { return m_end; }

  auto set_start(Node* start) -> void { m_start = start; }

  auto set_end(Node* end) -> void { m_end = end; }

  auto cost() const -> float { return m_cost; }

  auto set_cost(float cost) -> void { m_cost = cost; }

  auto len() const -> float { return m_start->distance_from(m_end); }

  // auto angle() const -> float { return m_start->angle(*m_end); }

  auto operator<(const Edge& other) const -> bool {
    return m_cost < other.m_cost;
  }

  auto operator==(const Edge& other) const -> bool {
    return m_start == other.m_start && m_end == other.m_end;
  }

 private:
  /// @brief The start node of this edge.
  Node* m_start;

  /// @brief The end node of this edge.
  Node* m_end;

  /// @brief The cost of this edge.
  float m_cost = INFINITY;

  /// @brief Whether the distance between the start and end nodes of this
  /// edge
  ///        should be used as the cost of the edge.
  bool m_distance_is_cost = true;

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

// //
// ---------------------------------------------------------------------------
// // DAG (Directed Acyclic Graph)
// //
// ---------------------------------------------------------------------------

/// @brief A directed acyclic graph (DAG) is a graph containing both nodes
/// and edges.  The edges are directed and the graph is acyclic (i.e. there
/// are no cycles in the graph). The DAG is used to represent the
/// environment
///
/// NOTE: The DAG can be converted to an adjacency matrix
///
/// The DAG is what the user interacts with inside of the environment when
/// it comes to adding nodes and edges to the graph via mouse clicks.
class DirectedAcyclicGraph {
 public:
  // DirectedAcyclicGraph() = default;
  // DirectedAcyclicGraph(const DirectedAcyclicGraph& other) = delete;
  // DirectedAcyclicGraph(DirectedAcyclicGraph&& other) = delete;
  // auto operator=(const DirectedAcyclicGraph& other)
  //     -> DirectedAcyclicGraph& = delete;
  // auto operator=(DirectedAcyclicGraph&& other)
  //     -> DirectedAcyclicGraph& = delete;

  DirectedAcyclicGraph(RenderWindow* window, Texture* texture,
                       unique_ptr<Node> root, unique_ptr<Node> goal) {
    // TODO: this needs to me changed
    m_root = root.release();
    m_goal = goal.release();

    m_nodes.reserve(INITIAL_GRAPH_CAPACITY);
    m_edges.reserve(INITIAL_GRAPH_CAPACITY);

    m_nodes.push_back(std::move(root));
    m_nodes.push_back(std::move(goal));

    m_window = window;
    m_texture = texture;
  }

  ~DirectedAcyclicGraph() = default;

  auto add_node(unique_ptr<Node> node) -> void {
    m_nodes.push_back(std::move(node));
  }

  auto add_node(Vector2f position) -> Node* {
    // auto node = std::make_unique<Node>(m_window, position);
    auto node = std::make_unique<Node>(*m_window, *m_texture, position);
    auto node_ptr = node.get();
    m_nodes.push_back(std::move(node));
    return node_ptr;
  }

  auto add_edge(Node* from, Node* to) -> Edge* {
    auto edge = std::make_unique<Edge>(from, to);
    auto edge_ptr = edge.get();
    m_edges.push_back(std::move(edge));

    from->add_outgoing_edge(edge_ptr);
    to->add_incoming_edge(edge_ptr);
    return edge_ptr;
  }

  auto render() -> void {
    for (const auto& node : m_nodes) {
      node->render();
    }

    // for (const auto& edge : m_edges) {
    //     edge->render();
    // }
  }

  /// @brief Returns the source node of the graph.
  /// @return The source node of the graph.
  auto source() const { return m_root; }

  /// @brief Returns the target node of the graph.
  /// @return The target node of the graph.
  auto target() const { return m_goal; }

  /// @brief Returns the number of nodes in the graph.
  /// @return The number of nodes in the graph.
  auto num_nodes() const { return m_nodes.size(); }

  /// @brief Returns the number of edges in the graph.
  /// @return The number of edges in the graph.
  auto num_edges() const { return m_edges.size(); }

 private:
  vector<unique_ptr<Node>> m_nodes;
  vector<unique_ptr<Edge>> m_edges;

  Node* m_root;
  Node* m_goal;

  RenderWindow* m_window;
  Texture* m_texture;
};
}  // namespace graph
