#pragma once
#include <algorithm>
#include <memory>

#include "graph/graph.h"
#include "utils/tracing.h"

#define FMT_HEADER_ONLY
#include "fmt/format.h"

using std::make_unique;

using graph::Node;
using sf::Texture;

namespace env {

auto init() -> void {
    Texture texture;

    const auto num_nodes = 1000;

    auto nodes = std::vector<std::unique_ptr<Node>>();

    // Create 1000 nodes
    for (int i = 0; i < num_nodes; i++) {
        tracing::debug(format("Creating node {}...", i));
        auto cost = static_cast<float>(rand() % 100);
        auto heuristic = static_cast<float>(rand() % 100);
        auto baby_node = make_unique<Node>(cost, heuristic);

        nodes.push_back(std::move(baby_node));
    }

    // for (int i = 0; i < 1000; i++) {
    //     m_nodes.push_back(new Node());
    // }

    // // Create 1000 edges
    // for (int i = 0; i < 1000; i++) {
    //     m_edges.push_back(new Edge());
    // }

    // // Connect the nodes
    // for (int i = 0; i < 1000; i++) {
    //     m_nodes[i]->addAdjacentNode(m_nodes[i + 1]);
    //     m_nodes[i]->addAdjacentEdge(m_edges[i]);
    // }

    // // Connect the edges
    // for (int i = 0; i < 1000; i++) {
    //     m_edges[i]->setStartNode(m_nodes[i]);
    //     m_edges[i]->setEndNode(m_nodes[i + 1]);
    // }

    // // Set the start and end nodes
    // m_startNode = m_nodes[0];
    // m_endNode = m_nodes[999];

    // // Set the start and end edges
    // m_startEdge = m_edges[0];
    // m_endEdge = m_edges[999];
}

auto render() -> void {
    // for (int i = 0; i < 1000; i++) {
    //     m_nodes[i]->render();
    // }

    // for (int i = 0; i < 1000; i++) {
    //     m_edges[i]->render();
    // }
}

auto update() -> void {
    // for (int i = 0; i < 1000; i++) {
    //     m_nodes[i]->update();
    // }

    // for (int i = 0; i < 1000; i++) {
    //     m_edges[i]->update();
    // }
}

}  // namespace env
