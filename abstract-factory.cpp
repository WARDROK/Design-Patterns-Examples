/*
 * Abstract Factory Pattern Example
 * ----------------------------------
 * This example demonstrates the Abstract Factory Pattern.
 * The Abstract Factory provides an interface for creating families of related products
 * (e.g., Monsters and Wizards) without specifying their concrete classes.
 * This allows for the creation of objects that belong to specific "levels" or "themes"
 * (e.g., Beginner and Advanced) by instantiating the appropriate factory.
 */

#include <iostream>
#include <memory>

// Abstract Product: Monster
class Monster
{
public:
    virtual void display() const = 0;
    virtual ~Monster() = default;
};

// Abstract Product: Wizard
class Wizard
{
public:
    virtual void castSpell() const = 0;
    virtual ~Wizard() = default;
};

// Concrete Product for Beginner Level: SmallMonster
class SmallMonster : public Monster
{
public:
    void display() const override
    {
        std::cout << "I am a Small Monster!" << std::endl;
    }
};

// Concrete Product for Beginner Level: HealerWizard
class HealerWizard : public Wizard
{
public:
    void castSpell() const override
    {
        std::cout << "Healer Wizard casts a healing spell!" << std::endl;
    }
};

// Concrete Product for Advanced Level: BigMonster
class BigMonster : public Monster
{
public:
    void display() const override
    {
        std::cout << "I am a Big Monster!" << std::endl;
    }
};

// Concrete Product for Advanced Level: SorcererWizard
class SorcererWizard : public Wizard
{
public:
    void castSpell() const override
    {
        std::cout << "Sorcerer Wizard casts a powerful spell!" << std::endl;
    }
};

// Abstract Factory Interface
class AbstractFactory
{
public:
    virtual std::unique_ptr<Monster> createMonster() = 0;
    virtual std::unique_ptr<Wizard> createWizard() = 0;
    virtual ~AbstractFactory() = default;
};

// Concrete Factory for Beginner Level
class BeginnerFactory : public AbstractFactory
{
public:
    std::unique_ptr<Monster> createMonster() override
    {
        return std::make_unique<SmallMonster>();
    }
    std::unique_ptr<Wizard> createWizard() override
    {
        return std::make_unique<HealerWizard>();
    }
};

// Concrete Factory for Advanced Level
class AdvancedFactory : public AbstractFactory
{
public:
    std::unique_ptr<Monster> createMonster() override
    {
        return std::make_unique<BigMonster>();
    }
    std::unique_ptr<Wizard> createWizard() override
    {
        return std::make_unique<SorcererWizard>();
    }
};

int main()
{
    std::unique_ptr<AbstractFactory> factory;

    // Suppose the user selects the Beginner level.
    factory = std::make_unique<BeginnerFactory>();
    auto monster1 = factory->createMonster();
    auto wizard1 = factory->createWizard();

    monster1->display();  // Outputs: I am a Small Monster!
    wizard1->castSpell(); // Outputs: Healer Wizard casts a healing spell!

    // Later, for Advanced level, the factory is switched.
    factory = std::make_unique<AdvancedFactory>();
    auto monster2 = factory->createMonster();
    auto wizard2 = factory->createWizard();

    monster2->display();  // Outputs: I am a Big Monster!
    wizard2->castSpell(); // Outputs: Sorcerer Wizard casts a powerful spell!

    return 0;
}