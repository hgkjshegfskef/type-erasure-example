#include "circle.hh"
#include "shape.hh"
#include "shape_operations.hh"
#include "square.hh"

int main() {
    std::vector<Shape> shapes;

    shapes.emplace_back(Circle(1.0));
    shapes.emplace_back(Square(2.0));
    shapes.emplace_back(Circle(3.0));

    draw_all_shapes(shapes);
}
