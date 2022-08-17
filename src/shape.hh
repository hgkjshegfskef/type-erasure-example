#pragma once

#include "circle_operations.hh"
#include "square_operations.hh"

#include <memory>
#include <type_traits>
#include <utility>

class Shape {
    // Shape's interface is implemented as hidden friends.
    friend void draw(Shape const& shape) {
        // Dispatch in ShapeModel<ConcreteShape>::draw().
        shape.pimpl_->do_draw();
    }

    template <typename S = Shape>
    friend std::enable_if_t<!std::is_const_v<S>, int&> get_prop(Shape& shape) {
        return shape.pimpl_->do_get_prop();
    }
    friend int const& get_prop(Shape const& shape) { return shape.pimpl_->do_get_prop(); }

    class ShapeConcept {
      public:
        virtual ~ShapeConcept() = 0;

        // Shape's interface declaration. The real functions containing implementations are named
        // without the do_ prefix, but in order to facilitate ADL in finding the free functions
        // implementing the interface, the virtual interface functions must be named differently.
        virtual void do_draw() const = 0;

        //        virtual int& do_get_prop() = 0;
        [[nodiscard]] virtual int const& do_get_prop() const = 0;

        // Make ShapeConcept's children copyable through ShapeConcept pointer.
        [[nodiscard]] virtual std::unique_ptr<ShapeConcept> clone() const = 0;

      protected:
        ShapeConcept() = default;
        ShapeConcept(ShapeConcept const&) = default;
        ShapeConcept(ShapeConcept&&) noexcept = default;
        ShapeConcept& operator=(ShapeConcept&&) noexcept = default;
        ShapeConcept& operator=(ShapeConcept const&) = default;
    };

    template <typename ConcreteShape> class ShapeModel final : public ShapeConcept {
      public:
        explicit ShapeModel(ConcreteShape&& concrete_shape)
            // Copy-construct or move-construct the concrete type.
            : object_{std::forward<ConcreteShape>(concrete_shape)} {}

        void do_draw() const override {
            // Call free draw() on objects implementing the Shape interface.
            draw(object_);
        }

        template <typename C = ConcreteShape>
        std::enable_if_t<!std::is_const_v<C>, int&> do_get_prop() {
            return get_prop(object_);
        }
        [[nodiscard]] int const& do_get_prop() const override { return get_prop(object_); }

        [[nodiscard]] std::unique_ptr<ShapeConcept> clone() const override {
            return std::make_unique<ShapeModel>(*this);
        }

      private:
        ConcreteShape object_;
    };

  public:
    template <typename ConcreteShape,
              // Make sure that templated forwarding constructor does not hide the copy constructor.
              // Another very important thing is to decay the ConcreteShape before comparison,
              // otherwise Shape& binds to this constructor.
              std::enable_if_t<!std::is_same_v<Shape, std::decay_t<ConcreteShape>>, bool> = true>
    explicit Shape(ConcreteShape&& concrete_shape)
        // Strip the reference, so that either a copy or a move occurs, but not reference binding.
        : pimpl_{std::make_unique<ShapeModel<std::remove_reference_t<ConcreteShape>>>(
              std::forward<std::remove_reference_t<ConcreteShape>>(concrete_shape))} {}

    // Deep copy of the concrete shape object.
    Shape(Shape const& other) : pimpl_{other.pimpl_->clone()} {}

    // Deep copy of the concrete shape object.
    Shape& operator=(Shape const& rhs) {
        if (&rhs != this) {
            pimpl_ = rhs.pimpl_->clone();
        }
        return *this;
    }

    // unique_ptr is movable by default.
    Shape(Shape&&) noexcept = default;
    Shape& operator=(Shape&&) noexcept = default;

    ~Shape() = default;

  private:
    // Pointer to a ShapeModel, which has a member object of the concrete type.
    std::unique_ptr<ShapeConcept> pimpl_;
};

inline Shape::ShapeConcept::~ShapeConcept() = default;
