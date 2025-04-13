/*
 * Facade Design Pattern Example
 * -----------------------------
 * This example demonstrates the Facade Pattern, where a single interface (the Facade)
 * simplifies interactions with a complex subsystem composed of multiple components.
 */

#include <iostream>
#include <memory>

// Subsystem A
class SubsystemA
{
public:
    void operationA()
    {
        std::cout << "SubsystemA: Executing operation A." << std::endl;
    }
};

// Subsystem B
class SubsystemB
{
public:
    void operationB()
    {
        std::cout << "SubsystemB: Executing operation B." << std::endl;
    }
};

// Subsystem C
class SubsystemC
{
public:
    void operationC()
    {
        std::cout << "SubsystemC: Executing operation C." << std::endl;
    }
};

// Facade that provides a unified interface to the subsystems
class Facade
{
private:
    std::shared_ptr<SubsystemA> subsystemA_;
    std::shared_ptr<SubsystemB> subsystemB_;
    std::shared_ptr<SubsystemC> subsystemC_;

public:
    Facade() : subsystemA_(std::make_shared<SubsystemA>()),
               subsystemB_(std::make_shared<SubsystemB>()),
               subsystemC_(std::make_shared<SubsystemC>()) {}

    void performOperation()
    {
        std::cout << "Facade: Coordinating subsystems to perform the operation..." << std::endl;
        subsystemA_->operationA();
        subsystemB_->operationB();
        subsystemC_->operationC();
        std::cout << "Facade: Operation completed." << std::endl;
    }
};

int main() {
    Facade facade;
    facade.performOperation();
    return 0;
}