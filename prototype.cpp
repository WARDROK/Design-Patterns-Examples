/*
 * Prototype Design Pattern
 * ------------------------
 * This pattern allows cloning existing objects
 * instead of creating new instances from scratch.
 * Useful when object creation is costly.
 * You clone an existing object with its current state.
 */

#include <iostream>
#include <memory>

// Prototype
class Animal
{
public:
    std::string name;
    std::string color;
    virtual std::unique_ptr<Animal> clone() const = 0;
    virtual void speak() const = 0;
    virtual ~Animal() = default;
};

// Concrete prototype
class Sheep : public Animal
{
public:
    Sheep(const std::string &name, const std::string &color)
    {
        this->name = name;
        this->color = color;
    }

    std::unique_ptr<Animal> clone() const override
    {
        return std::make_unique<Sheep>(*this);
    }

    void speak() const override
    {
        std::cout << name << " the " << color << " sheep says: Baa!" << std::endl;
    }
};

// Client
int main()
{
    std::unique_ptr<Animal> orginal = std::make_unique<Sheep>("Dolly", "white");
    orginal->speak(); // Dolly the white sheep says: Baa!

    std::unique_ptr<Animal> clone1 = orginal->clone();
    clone1->speak(); // Dolly the white sheep says: Baa!

    orginal->color = "black";
    std::unique_ptr<Animal> clone2 = orginal->clone();
    clone1->speak(); // Dolly the white sheep says: Baa!
    clone2->speak(); // Dolly the black sheep says: Baa!

    return 0;
}