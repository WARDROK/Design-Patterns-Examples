/*
 * Observer Pattern Example
 * --------------------------
 * This example demonstrates the Observer Pattern, where multiple
 * Observer objects register with a Subject. When the Subject's state changes,
 * it notifies all registered Observers so that they can update accordingly.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>

// Observer interface defining the update method.
class Observer
{
public:
    virtual void update(const std::string &message) = 0;
    virtual ~Observer() = default;
};

// Subject class that maintains a list of observers and notifies them of changes.
class Subject
{
private:
    std::vector<std::shared_ptr<Observer>> observers_;
    std::string state_;

public:
    // Register an observer.
    void addObserver(const std::shared_ptr<Observer> &observer)
    {
        observers_.push_back(observer);
    }

    // Remove an observer.
    void removeObserver(const std::shared_ptr<Observer> &observer)
    {
        observers_.erase(
            std::remove(observers_.begin(), observers_.end(), observer),
            observers_.end());
    }

    // Change the state and notify all observers.
    void setState(const std::string &state)
    {
        state_ = state;
        notifyObservers();
    }

    // Notify all registered observers about the state change.
    void notifyObservers() const
    {
        for (const auto &observer : observers_)
        {
            observer->update(state_);
        }
    }

    // Optionally, retrieve the current state.
    std::string getState() const
    {
        return state_;
    }
};

// A concrete observer that reacts to state changes.
class ConcreteObserver : public Observer
{
private:
    std::string name_;

public:
    ConcreteObserver(const std::string &name) : name_(name) {}

    void update(const std::string &message) override
    {
        std::cout << "Observer [" << name_ << "] received update: " << message << std::endl;
    }
};

int main()
{
    // Create a subject instance.
    Subject subject;

    // Create some observers and register them with the subject.
    std::shared_ptr<Observer> observer1 = std::make_shared<ConcreteObserver>("Observer1");
    std::shared_ptr<Observer> observer2 = std::make_shared<ConcreteObserver>("Observer2");

    subject.addObserver(observer1);
    subject.addObserver(observer2);

    // Change state of subject, observers will be notified.
    subject.setState("State 1: Data Updated");

    // Remove one observer and change state again.
    subject.removeObserver(observer1);
    subject.setState("State 2: New Information");

    return 0;
}
