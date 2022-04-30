#include "shape_operations.hh"

#include "shape.hh"

void draw_all_shapes(const std::vector<Shape>& shapes) {
    for (auto const& shape : shapes) {
        draw(shape);
    }
}
