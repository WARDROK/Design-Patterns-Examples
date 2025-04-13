/*
 * Decorator Design Pattern
 * --------------------------
 * This pattern allows you to dynamically add responsibilities to objects without altering their interfaces.
 * By wrapping objects with decorator classes, you can extend their behavior at runtime.
 */

#include <iostream>
#include <memory>
#include <string>

// Base interface for Coffee
class Coffee
{
public:
    virtual std::string getIngredients() const = 0;
    virtual double cost() const = 0;
    virtual ~Coffee() = default;
};

// Concrete component: SimpleCoffee
class SimpleCoffee : public Coffee
{
public:
    std::string getIngredients() const override
    {
        return "Coffee";
    }

    double cost() const override
    {
        return 2.0;
    }
};

// Base decorator: CoffeeDecorator
class CoffeeDecorator : public Coffee
{
protected:
    std::shared_ptr<Coffee> coffee_;

public:
    CoffeeDecorator(const std::shared_ptr<Coffee> &coffee) : coffee_(coffee) {}

    std::string getIngredients() const override
    {
        return coffee_->getIngredients();
    }

    double cost() const override
    {
        return coffee_->cost();
    }
};

// Concrete decorator: MilkDecorator
class MilkDecorator : public CoffeeDecorator
{
public:
    MilkDecorator(const std::shared_ptr<Coffee> &coffee) : CoffeeDecorator(coffee) {}

    std::string getIngredients() const override
    {
        return coffee_->getIngredients() + ", Milk";
    }

    double cost() const override
    {
        return coffee_->cost() + 0.5;
    }
};

// Concrete decorator: SugarDecorator
class SugarDecorator : public CoffeeDecorator
{
public:
    SugarDecorator(const std::shared_ptr<Coffee> &coffee) : CoffeeDecorator(coffee) {}

    std::string getIngredients() const override
    {
        return coffee_->getIngredients() + ", Sugar";
    }

    double cost() const override
    {
        return coffee_->cost() + 0.3;
    }
};

int main()
{
    // Create a simple coffee
    std::shared_ptr<Coffee> coffee = std::make_shared<SimpleCoffee>();
    std::cout << coffee->getIngredients() << " : $" << coffee->cost() << std::endl;

    // Decorate with milk
    coffee = std::make_shared<MilkDecorator>(coffee);
    std::cout << coffee->getIngredients() << " : $" << coffee->cost() << std::endl;

    // Decorate with milka and sugar
    coffee = std::make_shared<SugarDecorator>(coffee);
    std::cout << coffee->getIngredients() << " : $" << coffee->cost() << std::endl;

    return 0;
}