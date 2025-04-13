/*
 * Singleton Pattern Example
 * ---------------------------
 * This example demonstrates the Singleton Pattern, ensuring that only one instance
 * of a class exists throughout the application's lifetime. The instance is created
 * when it is first needed (lazy initialization) and can be accessed globally via
 * the static getInstance() method.
 */

#include <iostream>

class Singleton
{
public:
    // Returns the single instance of the Singleton class.
    static Singleton &getInstance()
    {
        static Singleton instance; // Instantiated only once.
        return instance;
    }

    // Example method to demonstrate usage.
    void doSomething()
    {
        std::cout << "Singleton instance doing something." << std::endl;
    }

private:
    // Deleting copy constructor and assignment operator to prevent copies.
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

    // Private constructor prevents direct instantiation.
    Singleton()
    {
        std::cout << "Singleton instance created." << std::endl;
    }
};

int main()
{
    // Access the Singleton instance and invoke a method.
    Singleton::getInstance().doSomething();
    Singleton::getInstance().doSomething();

    // Verify that subsequent calls to getInstance() return the same instance.
    Singleton &instance1 = Singleton::getInstance();
    Singleton &instance2 = Singleton::getInstance();

    if (&instance1 == &instance2)
    {
        std::cout << "Both instance1 and instance2 refer to the same Singleton instance." << std::endl;
    }
    return 0;
}