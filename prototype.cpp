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
    std::unique_ptr<int> year = std::make_unique<int>();
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

    // For deep copy, especially important with pointers
    Sheep(const Sheep &other)
    {
        name = other.name;
        color = other.color;
        year = std::make_unique<int>(*other.year);
    }

    std::unique_ptr<Animal> clone() const override
    {
        return std::make_unique<Sheep>(*this);
    }

    void speak() const override
    {
        std::cout << name << " the " << color << ", year: " << *year << " sheep says: Baa!" << std::endl;
    }
};

// Client
int main()
{
    std::unique_ptr<Animal> orginal = std::make_unique<Sheep>("Dolly", "white");
    *orginal->year = 12;
    orginal->speak(); // Dolly the white, year: 12 sheep says: Baa!

    std::unique_ptr<Animal> clone1 = orginal->clone();
    clone1->speak(); // Dolly the white, year: 12 sheep says: Baa!

    orginal->color = "black";
    *orginal->year = 13;

    std::unique_ptr<Animal> clone2 = orginal->clone();
    clone1->speak(); // Dolly the white, year: 12 sheep says: Baa!
    clone2->speak(); // Dolly the black, year: 13 sheep says: Baa!

    return 0;
}