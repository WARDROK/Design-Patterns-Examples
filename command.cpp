/*
 * Command Pattern Example
 * -------------------------
 * This example demonstrates the Command Pattern, where a request is encapsulated as an object.
 * This allows you to parameterize clients with different requests, queue or log requests, and support undoable operations.
 */

#include <iostream>
#include <memory>

// Command interface that declares the execute method.
class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

// Receiver class that performs the actual operations.
class Light
{
public:
    void turnOn()
    {
        std::cout << "The light is turned on." << std::endl;
    }

    void turnOff()
    {
        std::cout << "The light is turned off." << std::endl;
    }
};

// Concrete command for turning on the light.
class LightOnCommand : public Command
{
private:
    Light &light;

public:
    LightOnCommand(Light &light) : light(light) {}

    void execute() override
    {
        light.turnOn();
    }
};

// Concrete command for turning off the light.
class LightOffCommand : public Command
{
private:
    Light &light;

public:
    LightOffCommand(Light &light) : light(light) {}

    void execute() override
    {
        light.turnOff();
    }
};

// Invoker class that holds a command and triggers its execution.
class RemoteControl
{
private:
    std::shared_ptr<Command> command;

public:
    void setCommand(const std::shared_ptr<Command> &cmd)
    {
        command = cmd;
    }

    void pressButton()
    {
        if (command)
        {
            command->execute();
        }
    }
};

int main()
{
    Light livingRoomLight;

    // Create smart pointer commands.
    std::shared_ptr<Command> lightOn = std::make_shared<LightOnCommand>(livingRoomLight);
    std::shared_ptr<Command> lightOff = std::make_shared<LightOffCommand>(livingRoomLight);

    RemoteControl remote;

    // Turn the light on
    remote.setCommand(lightOn);
    remote.pressButton(); // Outputs: The light is turned on.

    // Turn the light off
    remote.setCommand(lightOff);
    remote.pressButton(); // Outputs: The light is turned off.

    return 0;
}