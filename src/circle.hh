#pragma once

class Circle {
  public:
    explicit Circle(double radius) : radius_(radius) {}

    [[nodiscard]] double get_radius() const noexcept { return radius_; }

  private:
    double radius_;
};
