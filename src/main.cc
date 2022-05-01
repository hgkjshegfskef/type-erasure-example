#include "circle.hh"
#include "shape.hh"
#include "shape_operations.hh"
#include "square.hh"

int main() {
    Circle c{3};
    Shape s1{c};
    Shape s2{Circle{3.0}};
    Shape s4{Shape{Circle{3.0}}};
    Shape s5{std::move(s2)};
    Shape s6 = s5;

    std::vector<Shape> shapes;
    shapes.emplace_back(Circle{1.0});
    shapes.emplace_back(Square{2.0});
    draw_all_shapes(shapes);

    Shape s7 = Shape{Circle{3.0}};
    Shape s8{s7};
    const Circle c1{1};
    Shape s9{c1};
    const Shape s10{std::move(c1)};
    const Shape s11{Shape{Circle{1}}};
    const Shape s12{s11};
    Shape& s13 = s9;
    Shape const& s14 = s12;
}
