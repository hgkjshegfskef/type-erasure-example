#pragma once

#include "circle_operations.hh"
#include "shape_operations.hh"
#include "square_operations.hh"

#include <memory>

class Shape {
    class ShapeConcept {
      public:
        virtual ~ShapeConcept() = 0;
        [[nodiscard]] virtual std::unique_ptr<ShapeConcept> clone() const = 0;

        virtual void draw() const = 0;

      protected:
        ShapeConcept() = default;
        ShapeConcept(ShapeConcept const&) = default;
        ShapeConcept(ShapeConcept&&) noexcept = default;
        ShapeConcept& operator=(ShapeConcept&&) noexcept = default;
        ShapeConcept& operator=(ShapeConcept const&) = default;
    };

    template <typename T> class ShapeModel final : public ShapeConcept {
      public:
        template <typename U>
            requires(!std::same_as<T, U>)
        explicit ShapeModel( // NOLINT(bugprone-forwarding-reference-overload): forwarding ctor will
            U&& value)       // not shadow copy ctor, because U is a different type
            : object_(std::forward<U>(value)) {}

        void draw() const override {
            ::draw(object_); // XXX: why is ADL not working?
        }

        [[nodiscard]] std::unique_ptr<ShapeConcept> clone() const override {
            return std::make_unique<ShapeModel>(*this);
        }

      private:
        T object_;
    };

    friend void draw(Shape const& shape) { shape.pimpl_->draw(); }

  public:
    template <typename T> explicit Shape(T const& x) : pimpl_(new ShapeModel<T>(x)) {}

    Shape(Shape const& other) { pimpl_ = other.pimpl_->clone(); }

    Shape& operator=(Shape const& rhs) {
        if (&rhs != this) {
            pimpl_ = rhs.pimpl_->clone();
        }
        return *this;
    }

    Shape(Shape&& other) noexcept = default;
    Shape& operator=(Shape&& rhs) noexcept = default;
    ~Shape() = default;

  private:
    std::unique_ptr<ShapeConcept> pimpl_;
};
