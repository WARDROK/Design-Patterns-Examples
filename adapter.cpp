/*
 * Adapter Pattern Example
 * -------------------------
 * The Adapter pattern allows incompatible interfaces to work together.
 * It adapts an existing class (Adaptee) to a new interface (Target) that clients expect.
 * This example demonstrates both object and class adapters.
 */

#include <iostream>
#include <memory>

// Target interface expected by the client
class ITarget
{
public:
    virtual void request() const = 0;
    virtual ~ITarget() = default;
};

// Existing class (Adaptee) with an incompatible interface
class Adaptee
{
public:
    void specificRequest() const
    {
        std::cout << "Called specificRequest()" << std::endl;
    }
};

// Object Adapter using composition (Method Adapter)
// The adapter contains an instance of Adaptee and translates calls
// from the client's request() to the adaptee's specificRequest() method.
class ObjectAdapter : public ITarget
{
public:
    ObjectAdapter(const std::shared_ptr<Adaptee> &a) : adaptee_(a) {}
    void request() const override
    {
        adaptee_->specificRequest();
    }

private:
    std::shared_ptr<Adaptee> adaptee_;
};

// Class Adapter using inheritance
// The adapter inherits from ITarget and privately from Adaptee,
// allowing it to directly use Adaptee's specificRequest() method.
class ClassAdapter : public ITarget, private Adaptee
{
public:
    void request() const override
    {
        specificRequest();
    }
};

int main()
{
    // Object Adapter usage:
    std::shared_ptr<Adaptee> adapteeObj = std::make_shared<Adaptee>();
    std::unique_ptr<ITarget> objectAdapter = std::make_unique<ObjectAdapter>(adapteeObj);
    std::cout << "Using Object Adapter:" << std::endl;
    objectAdapter->request(); // Outputs: Called specificRequest()

    // Class Adapter usage:
    std::unique_ptr<ITarget> classAdapter = std::make_unique<ClassAdapter>();
    std::cout << "Using Class Adapter:" << std::endl;
    classAdapter->request(); // Outputs: Called specificRequest()

    return 0;
}