#include "graph/graph.h"

#include <gtest/gtest.h>

#include <memory>

using std::make_unique;

using sf::Vector2f;

using graph::Node;

TEST(Graph, Node) {
    // Create a node with cost 1.0 and heuristic 2.0
    auto node = make_unique<Node>(1.0f, 2.0f);

    // Check that the node's cost and heuristic are correct
    EXPECT_EQ(node->cost(), 1.0f);
    EXPECT_EQ(node->heuristic(), 2.0f);
    EXPECT_EQ(node->totalCost(), 3.0f);

    // Create a node with given parent, cost, and heuristic
    auto parent = make_unique<Node>(1.0f, 2.0f);
    auto child = make_unique<Node>(std::move(parent), 3.0f, 4.0f);

    // Check that the child's parent, cost, and heuristic are correct
    EXPECT_EQ(child->parent()->cost(), 1.0f);
    EXPECT_EQ(child->parent()->heuristic(), 2.0f);
    EXPECT_EQ(child->cost(), 3.0f);
    EXPECT_EQ(child->heuristic(), 4.0f);
    EXPECT_EQ(child->totalCost(), 7.0f);

    // Create a node with given parent, cost, heuristic, and position (x, y)
    auto parent2 = make_unique<Node>(1.0f, 2.0f);
    auto child2 = make_unique<Node>(std::move(parent2), 3.0f, 4.0f,
                                    sf::Vector2f(5.0f, 6.0f));

    // Check that the child's parent, cost, heuristic, and position are correct
    EXPECT_EQ(child2->parent()->cost(), 1.0f);
    EXPECT_EQ(child2->parent()->heuristic(), 2.0f);
    EXPECT_EQ(child2->cost(), 3.0f);
    EXPECT_EQ(child2->heuristic(), 4.0f);
    EXPECT_EQ(child2->totalCost(), 7.0f);
    EXPECT_EQ(child2->position().x, 5.0f);
    EXPECT_EQ(child2->position().y, 6.0f);

    // Check that mutators work
    child2->set_cost(7.0f);
    child2->set_heuristic(8.0f);
    child2->set_position(Vector2f(9.0f, 10.0f));
    EXPECT_EQ(child2->cost(), 7.0f);
    EXPECT_EQ(child2->heuristic(), 8.0f);
    EXPECT_EQ(child2->totalCost(), 15.0f);

    child2->reset_parent();

    // Check that the child's parent is nullptr
    EXPECT_EQ(child2->parent(), nullptr);
}