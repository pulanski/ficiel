#include "graph/graph.h"

#include <gtest/gtest.h>

#include <memory>

#include "SFML/Graphics.hpp"

using std::make_unique;

using sf::Vector2f;

using graph::Edge;
using graph::Node;

TEST(Graph, DAG) {
    RenderWindow window(VideoMode(800, 600), "Graph Test");
    Texture texture;

    if (!texture.loadFromFile("assets/high_res_boid.png")) {
        fmt::print("Failed to load node texture from file\n");
    }

    auto source = make_unique<Node>(window, texture, Vector2f(0.0f, 0.0f));
    auto target = make_unique<Node>(window, texture, Vector2f(10.0f, 10.0f));

    // // Create a new directed acyclic graph from
    // // a given source and target node
    // auto dag = make_unique<graph::DirectedAcyclicGraph>(
    //     &window, std::move(source), std::move(target));

    // // check that the source and target nodes are correct
    // EXPECT_EQ(dag->source()->position(), Vector2f(0.0f, 0.0f));
    // EXPECT_EQ(dag->target()->position(), Vector2f(10.0f, 10.0f));
    // EXPECT_EQ(static_cast<int>(dag->source()->distance_from(dag->target())),
    //           14);

    // auto initial_edge = dag->add_edge(dag->source(), dag->target());

    // // check that the edge is correct
    // EXPECT_EQ(initial_edge->from(), dag->source());
    // EXPECT_EQ(initial_edge->to(), dag->target());

    // EXPECT_EQ(dag->source()->num_outgoing_edges(), 1);
    // EXPECT_EQ(dag->target()->num_incoming_edges(), 1);

    // // check that the graph is correct
    // EXPECT_EQ(dag->num_nodes(), 2);
    // EXPECT_EQ(dag->num_edges(), 1);

    // // Add a node to the graph w/ a given position
    // auto node = dag->add_node(Vector2f(5.0f, 5.0f));

    // // check that the node is correct
    // EXPECT_EQ(node->position(), Vector2f(5.0f, 5.0f));
    // EXPECT_EQ(static_cast<int>(node->distance_from(dag->source())), 7);
    // EXPECT_EQ(static_cast<int>(node->distance_from(dag->target())), 7);

    // // check that the graph is correct
    // EXPECT_EQ(dag->num_nodes(), 3);
    // EXPECT_EQ(dag->num_edges(), 1);

    // // Add edges from the middle node to the source and target nodes
    // auto edge1 = dag->add_edge(node, dag->source());
    // auto edge2 = dag->add_edge(node, dag->target());

    // // check that the edges are correct
    // EXPECT_EQ(edge1->from(), node);
    // EXPECT_EQ(edge1->to(), dag->source());

    // EXPECT_EQ(edge2->from(), node);
    // EXPECT_EQ(edge2->to(), dag->target());

    // // check that the graph is correct
    // EXPECT_EQ(dag->num_nodes(), 3);
    // // source -> node, node -> target, source -> target
    // EXPECT_EQ(dag->num_edges(), 3);

    // Add an edge from a given source node to a new node w/ a given
    // position dag->add_edge_to(dag->source(), Vector2f(1.0f, 9.0f));
}
