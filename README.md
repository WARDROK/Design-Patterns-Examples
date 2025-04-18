# Design-Patterns-Examples

## Prototype Design Pattern

**Prototype** allows you to create new objects by cloning existing instances with their current state, rather than instantiating objects from scratch using constructors. This can help avoid costly initialization steps.

**Usage example:**

- Instead of repeatedly performing complex initializations (e.g., loading data from a database or file, or performing heavy calculations), you create a prototype object and then clone it as needed. Changes in the prototype's state are automatically propagated to new objects, thereby simplifying management and improving application performance.

## Composite Design Pattern

**Composite** enables you to treat individual objects and groups of objects uniformly. It allows you to build tree structures where clients can work with both single elements (leaves) and composite objects (nodes) in a consistent manner.

### Main features:

- Creation of tree structures.
- Uniform treatment of individual objects and their compositions.
- Simplifies client code since there is no need to differentiate between a single element and a group of elements.

## Adapter Design Pattern

**Adapter** enables interoperability between interfaces that are normally incompatible. Using an adapter, you can adapt the interface of an existing class (Adaptee) to meet the needs of the client that expects a different interface (Target).

### How it works:

- **Target:** Defines the interface expected by the client.
- **Adaptee:** Provides useful functionality, but its interface does not match the Target interface.
- **Object Adapter:** Uses composition by holding an instance of the Adaptee and translating calls from the Target into calls to the Adaptee.
- **Class Adapter:** Uses inheritance; the adapter inherits both from the Target interface and the Adaptee, allowing direct invocation of Adaptee’s methods.

## Proxy Pattern: Virtual Proxy and Copy-on-Write Proxy

**Proxy** provides control over access to an object by introducing a level of indirection. The following two types of proxies are presented:

1. **Virtual Proxy**  
   Enables lazy initialization of an object—an expensive-to-create object is not instantiated until it is actually needed. This helps conserve system resources.

2. **Copy-on-Write Proxy**  
   Allows an object to be shared for read-only operations. When a write operation is attempted and the object is shared, a deep copy is made so that the modification does not affect other instances. This is useful for efficient memory management.

### How it works:

- **Virtual Proxy:**  
  Maintains a private pointer `resource_` to a resource (e.g., an `ExpensiveResource`) that is created only upon the first method call.

- **Copy-on-Write Proxy:**  
  Maintains a private pointer `resource_` to a shared object (e.g., a `Document`) using `std::shared_ptr`. When a modification is requested and the object is shared (reference count > 1), a new copy of the object is created to ensure isolated modification.

## Observer Pattern

**Observer** enables a one-to-many dependency between objects such that when one object (the Subject) changes its state, all its dependent objects (Observers) are automatically notified and updated. This pattern is especially useful for implementing event-based or user interface systems.

### How it works:

- **Subject:**  
  Maintains a list of observers and provides methods for registering and unregistering them. When its state changes, it notifies all registered observers.

- **Observer:**  
  Defines an interface with a method (e.g., `update()`) to be called when the Subject changes. Concrete observers implement this interface to perform specific actions in response to notifications.

- **Notification:**  
  The Subject calls the notification method, iterating through its list of observers and informing them about the change.

## Command Pattern

**Command** encapsulates a request as an object. This enables you to pass, store, and delay the execution of commands, as well as to implement operations such as queuing, logging, and undo/redo functionality.

### General idea:

- **Encapsulation of requests:**  
  The request (e.g., a method call) is wrapped in an object that stores all parameters needed for execution.
- **Decoupling:**  
  The Invoker (the object that executes the command) is decoupled from the Receiver (the object that performs the actual action). The client only needs to interact with the command interface.
- **Flexibility:**  
  Commands can be stored, passed as parameters, and executed at any time, allowing for highly flexible and extensible architectures.

## Decorator Pattern

**Decorator** dynamically adds additional responsibilities to an object without altering its interface. This pattern allows you to extend an object's functionality at runtime by wrapping it with one or more decorator classes.

### General idea:

- **Base:**  
  A common base class (interface) represents the object to be decorated (e.g., `Coffee`).
- **Component:**  
  A concrete class (e.g., `SimpleCoffee`) implements the interface, providing basic functionality.
- **Decorator:**  
  An abstract decorator class (`CoffeeDecorator`) also implements the interface and holds a pointer/reference to a component object. Concrete decorators (e.g., `MilkDecorator`, `SugarDecorator`) extend the functionality by adding new features.
