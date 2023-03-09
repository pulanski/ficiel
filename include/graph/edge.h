// #pragma once

// #include <memory>
// #include <vector>

// #include "graph/node.h"
// #include "utils/tracing.h"

// using graph::Node;
// using std::unique_ptr;

// namespace graph {
// /// @brief Represents an infinite cost for an edge in a graph.
// static const int32_t INFINITY = -1;
// class Edge {
//    public:
//     Edge(unique_ptr<Node> start, unique_ptr<Node> end)
//         : m_start(std::move(start)), m_end(std::move(end)) {
//         // tracing::debug("Edge created with start node {} and end node {}",
//         //                m_start, m_end);
//     }

//     auto start() const -> const auto& { return *m_start; }

//     auto end() const -> const auto& { return *m_end; }

//     auto set_start(unique_ptr<Node> start) -> void {
//         m_start = std::move(start);
//     }

//     auto set_end(unique_ptr<Node> end) -> void { m_end = std::move(end); }

//     auto cost() const -> float { return m_cost; }

//     auto set_cost(float cost) -> void { m_cost = cost; }

//     auto len() const -> float { return m_start->dist(*m_end); }

//     auto angle() const -> float { return m_start->angle(*m_end); }

//     auto operator<(const Edge& other) const -> bool {
//         return m_cost < other.m_cost;
//     }

//     auto operator==(const Edge& other) const -> bool {
//         return m_start == other.m_start && m_end == other.m_end;
//     }

//    private:
//     /// @brief The start node of this edge.
//     unique_ptr<Node> m_start;
//     /// @brief The end node of this edge.
//     unique_ptr<Node> m_end;
//     /// @brief The cost of this edge.
//     float m_cost = INFINITY;

//     /// @brief Prints the edge to the given output stream.
//     /// @param os The output stream to print to.
//     /// @param edge The edge to print.
//     /// @return The output stream.
//     friend auto operator<<(std::ostream& os, const Edge& edge)
//         -> std::ostream& {
//         os << "Edge(" << edge.start() << "->" << edge.end() << ")";
//         return os;
//     }
// };
// }  // namespace graph
