//
//  board.cpp
//  Chess-Board
//
//  Created by Chas Ladhar on 20/05/2024.
//

#include <stdio.h>
#include <iostream>
#include <vector>

#include "board.h"


void createChessboard(std::vector<float> &vertices) {
    float size = 1.0f;
    float thickness = 0.4f; // thickness of the board

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            bool isWhite = (i + j) % 2 == 0;
            float color = isWhite ? 1.0f : 0.0f;

            float x = j * size - 4.0f;
            float y = i * size - 4.0f;
            float z = 0.0f;

            // Create top face of the board square
            vertices.insert(vertices.end(), {
                x, y, z, color, color, color,
                x + size, y, z, color, color, color,
                x, y + size, z, color, color, color,

                x + size, y, z, color, color, color,
                x, y + size, z, color, color, color,
                x + size, y + size, z, color, color, color
            });

            // Create bottom face of the board square
            vertices.insert(vertices.end(), {
                x, y, z - thickness, color, color, color,
                x + size, y, z - thickness, color, color, color,
                x, y + size, z - thickness, color, color, color,

                x + size, y, z - thickness, color, color, color,
                x, y + size, z - thickness, color, color, color,
                x + size, y + size, z - thickness, color, color, color
            });

            // Create the 4 side faces of the board square
            vertices.insert(vertices.end(), {
                // Side 1
                x, y, z, color, color, color,
                x, y, z - thickness, color, color, color,
                x + size, y, z - thickness, color, color, color,

                x, y, z, color, color, color,
                x + size, y, z - thickness, color, color, color,
                x + size, y, z, color, color, color,

                // Side 2
                x, y, z, color, color, color,
                x, y + size, z, color, color, color,
                x, y + size, z - thickness, color, color, color,

                x, y, z, color, color, color,
                x, y + size, z - thickness, color, color, color,
                x, y, z - thickness, color, color, color,

                // Side 3
                x + size, y + size, z, color, color, color,
                x + size, y, z, color, color, color,
                x + size, y, z - thickness, color, color, color,

                x + size, y + size, z, color, color, color,
                x + size, y, z - thickness, color, color, color,
                x + size, y + size, z - thickness, color, color, color,

                // Side 4
                x + size, y + size, z, color, color, color,
                x, y + size, z, color, color, color,
                x, y + size, z - thickness, color, color, color,

                x + size, y + size, z, color, color, color,
                x, y + size, z - thickness, color, color, color,
                x + size, y + size, z - thickness, color, color, color,
            });
        }
    }
}
