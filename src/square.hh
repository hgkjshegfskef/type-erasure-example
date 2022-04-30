#pragma once

class Square {
  public:
    explicit Square(double side) : side_(side) {}

    [[nodiscard]] double get_side() const noexcept { return side_; }

  private:
    double side_;
};
