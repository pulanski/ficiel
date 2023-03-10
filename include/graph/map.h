
// #pragma once

// #include "node.h"

// // auto buildMap(Map* map) -> void {
// //     for (int i = 0; i < MAP_WIDTH; i++) {
// //         for (int j = 0; j < MAP_HEIGHT; j++) {
// //             map->setTile(i, j, Tile::GRASS);
// //         }
// //     }
// // }

// /// The map of the game
// class Map {
//    public:
//     /// @brief Constructs a map with the given width and height
//     Map(int width, int height) : m_width(width), m_height(height) {
//         m_nodes = new Node*[width];
//         for (int i = 0; i < width; i++) {
//             m_nodes[i] = new Node[height];
//         }
//     }

//     /// @brief Destroys the map
//     ~Map() {
//         for (int i = 0; i < m_width; i++) {
//             delete[] m_nodes[i];
//         }
//         delete[] m_nodes;
//     }

//     /// @brief Returns the node at the given coordinates
//     Node* nodeAt(int x, int y) const { return &m_nodes[x][y]; }

//     /// @brief Returns the width of the map
//     int width() const { return m_width; }

//     /// @brief Returns the height of the map
//     int height() const { return m_height; }

//    private:
//     /// @brief The width of the map
//     int m_width;
//     /// @brief The height of the map
//     int m_height;
//     /// @brief The nodes in the map
//     Node** m_nodes;
// };