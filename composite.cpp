/*
 * Composite Design Pattern
 * --------------------------
 * This pattern allows you to treat individual objects and their compositions uniformly.
 * It enables the creation of tree structures where clients can work with both single
 * elements (leaves) and groups of objects (composites) in a consistent manner.
 */

#include <iostream>
#include <vector>
#include <memory>

// Abstract component
class Graphic
{
public:
    virtual void draw() const = 0;
    virtual ~Graphic() = default;
};

// Leaf
class Circle : public Graphic
{
public:
    void draw() const override
    {
        std::cout << "Drawing Circle\n";
    }
};

class Square : public Graphic
{
public:
    void draw() const override
    {
        std::cout << "Drawing Square\n";
    }
};

// Composite
class CompositeGraphic : public Graphic
{
private:
    std::vector<std::shared_ptr<Graphic>> _graphics;

public:
    void add(const std::shared_ptr<Graphic> &graphic)
    {
        _graphics.push_back(graphic);
    }

    void draw() const override
    {
        std::cout << "CompositeGraphic contains:" << std::endl;
        for (const auto &graphic : _graphics)
        {
            graphic->draw();
        }
    }
};

// Client
int main()
{
    std::shared_ptr<Circle> circle1 = std::make_shared<Circle>();
    std::shared_ptr<Square> square1 = std::make_shared<Square>();
    std::shared_ptr<Circle> circle2 = std::make_shared<Circle>();

    std::shared_ptr<CompositeGraphic> composite = std::make_shared<CompositeGraphic>();
    composite->add(circle1);
    composite->add(square1);

    std::shared_ptr<CompositeGraphic> mainComposite = std::make_shared<CompositeGraphic>();
    mainComposite->add(composite);
    mainComposite->add(circle2);

    mainComposite->draw();

    return 0;
}