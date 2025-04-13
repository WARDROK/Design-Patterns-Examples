/*
 * Scalable & Prototype Factory Pattern Example
 * ----------------------------------------------
 * This example demonstrates two factory patterns:
 *
 * 1. Scalable Factory:
 *    - Registers creation functions for various concrete types (e.g., Square, Circle)
 *      identified by an ID.
 *    - When a client requests a figure by its ID, the factory invokes the corresponding creation function.
 *
 * 2. Prototype Factory:
 *    - Registers prototype objects that represent concrete types.
 *    - When creating a new object, the factory clones the registered prototype,
 *      thereby producing a new instance with the same state.
 */

#include <iostream>
#include <memory>
#include <map>
#include <functional>

// Base class for all Figures
class Figure
{
public:
    virtual void draw() const = 0;
    // Virtual clone method for Prototype Factory
    virtual std::unique_ptr<Figure> clone() const = 0;
    virtual ~Figure() = default;
};

// Concrete class: Square
class Square : public Figure
{
    void draw() const override
    {
        std::cout << "Drawing a Square" << std::endl;
    }

    std::unique_ptr<Figure> clone() const override
    {
        return std::make_unique<Square>(*this);
    }
};

// Concrete class: Circle
class Circle : public Figure
{
public:
    void draw() const override
    {
        std::cout << "Drawing a Circle" << std::endl;
    }
    std::unique_ptr<Figure> clone() const override
    {
        return std::make_unique<Circle>(*this);
    }
};

// -------------------------
// Scalable Factory Pattern
// -------------------------
class ScalableFactory
{
public:
    // Define the type for the function that creates a Figure object.
    using CreateFigFun = std::function<std::unique_ptr<Figure>()>;

    // Register a creation function for a given ID.
    bool registerFigure(int id, CreateFigFun func)
    {
        return _registry.emplace(id, func).second;
    }

    // Create a Figure object by its ID using the registered creation function.
    std::unique_ptr<Figure> cretateFigure(int id)
    {
        auto it = _registry.find(id);
        if (it != _registry.end())
        {
            return (it->second)();
        }
        std::cerr << "Unknow figure id: " << id << std::endl;
        return nullptr;
    }

private:
    std::map<int, CreateFigFun> _registry;
};

// -------------------------
// Prototype Factory Pattern
// -------------------------
class PrototypeFactory
{
public:
    // Register a prototype for a given ID.
    bool registerPrototype(int id, std::unique_ptr<Figure> prototype)
    {
        _prototypes[id] = std::move(prototype);
        return true;
    }

    // Create a new Figure object by cloning the registered prototype.
    std::unique_ptr<Figure> createFigure(int id)
    {
        auto it = _prototypes.find(id);
        if (it != _prototypes.end())
        {
            return it->second->clone();
        }
        std::cerr << "Unknown prototype id: " << id << std::endl;
        return nullptr;
    }

private:
    std::map<int, std::unique_ptr<Figure>> _prototypes;
};

int main()
{
    // ---------- Scalable Factory Example ----------
    ScalableFactory scalableFactory;
    scalableFactory.registerFigure(1, []()
                                   { return std::make_unique<Square>(); });
    scalableFactory.registerFigure(2, []()
                                   { return std::make_unique<Circle>(); });

    std::cout << "Scalable Factory:" << std::endl;
    auto fig1 = scalableFactory.cretateFigure(1);
    if (fig1)
        fig1->draw();
    auto fig2 = scalableFactory.cretateFigure(2);
    if (fig2)
        fig2->draw();
    auto fig3 = scalableFactory.cretateFigure(3);
    if (fig3)
        fig3->draw();

    // ---------- Prototype Factory Example ----------
    PrototypeFactory prototypefactory;

    // Registering prototypes with unique_ptr
    prototypefactory.registerPrototype(1, std::make_unique<Square>());
    prototypefactory.registerPrototype(2, std::make_unique<Circle>());

    std::cout << "Prototype Factory:" << std::endl;
    auto figure1 = prototypefactory.createFigure(1);
    if (figure1)
        figure1->draw();

    auto figure2 = prototypefactory.createFigure(2);
    if (figure2)
        figure2->draw();

    // Attempt to create an object with an unknown ID
    auto figure3 = prototypefactory.createFigure(3);
    if (figure3)
        figure3->draw();

    return 0;
}