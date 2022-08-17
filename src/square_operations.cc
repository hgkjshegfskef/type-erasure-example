#include "square_operations.hh"

#include "square.hh"

#include <iostream>

void draw(Square const& s) { std::cout << "Drawing a square\n"; }
int& get_prop(Square& s) { return s.prop; }
int const& get_prop(Square const& s) { return s.prop; }
