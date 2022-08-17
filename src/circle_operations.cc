#include "circle_operations.hh"

#include "circle.hh"

#include <iostream>

void draw(Circle const& c) { std::cout << "Drawing a circle\n"; }

int& get_prop(Circle& c) { return c.prop; }
int const& get_prop(Circle const& c) { return c.prop; }
