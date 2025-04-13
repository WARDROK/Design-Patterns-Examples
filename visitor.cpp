/*
 * Visitor Pattern Example
 * -------------------------
 * This example demonstrates the Visitor Pattern, which lets you separate an algorithm
 * from the objects on which it operates. By defining a visitor interface with methods for
 * each concrete element type, new operations can be added without modifying the element classes.
 */

#include <iostream>
#include <vector>
#include <memory>

// Forward declarations of concrete element classes.
class ConcreteElementA;
class ConcreteElementB;

// Visitor interface declaring visit methods for each concrete element.
class Visitor
{
public:
    virtual void visit(ConcreteElementA &element) = 0;
    virtual void visit(ConcreteElementB &element) = 0;
    virtual ~Visitor() = default;
};

// Element interface, with an accept method that accepts a visitor.
class Element
{
public:
    virtual void accept(Visitor &visitor) = 0;
    virtual ~Element() = default;
};

// Concrete Element A.
class ConcreteElementA : public Element
{
public:
    void accept(Visitor &visitor) override
    {
        visitor.visit(*this);
    }

    // Specific operation for ConcreteElementA.
    void operationA()
    {
        std::cout << "ConcreteElementA: operationA" << std::endl;
    }
};

// Concrete Element B.
class ConcreteElementB : public Element
{
public:
    void accept(Visitor &visitor) override
    {
        visitor.visit(*this);
    }
    // Specific operation for ConcreteElementB.
    void operationB()
    {
        std::cout << "ConcreteElementB: operationB" << std::endl;
    }
};

// Concrete Visitor that implements operations for each concrete element.
class ConcreteVisitor : public Visitor
{
public:
    void visit(ConcreteElementA &element) override
    {
        std::cout << "ConcreteVisitor: Visiting ConcreteElementA." << std::endl;
        element.operationA();
    }

    void visit(ConcreteElementB &element) override
    {
        std::cout << "ConcreteVisitor: Visiting ConcreteElementB." << std::endl;
        element.operationB();
    }
};

int main()
{
    // Create a collection of elements.
    std::vector<std::unique_ptr<Element>> elements;
    elements.push_back(std::make_unique<ConcreteElementA>());
    elements.push_back(std::make_unique<ConcreteElementB>());

    // Create a visitor.
    ConcreteVisitor visitor;

    // Iterate over elements and accept the visitor.
    for (auto &e : elements)
    {
        e->accept(visitor);
    }

    return 0;
}