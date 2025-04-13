/*
 * Virtual Proxy and Copy-on-Write Proxy Examples
 * ------------------------------------------------
 * This example demonstrates two types of proxies:
 * 1. Virtual Proxy: Delays the creation of an expensive object until it is needed.
 * 2. Copy-on-Write Proxy: Shares an object for read-only operations and makes a deep copy
 *    when a write operation occurs and the object is shared.
 */

#include <iostream>
#include <memory>
#include <string>

// ------------------ Virtual Proxy Example ------------------

// A class representing a resource_ that is expensive to create.
class ExpensiveResource
{
public:
    ExpensiveResource()
    {
        std::cout << "ExpensiveResource: Initialized" << std::endl;
    }
    void operation()
    {
        std::cout << "ExpensiveResource: Performing operation" << std::endl;
    }
};

// VirtualProxy delays the creation of ExpensiveResource until it is actually needed.
class VirtualProxy
{
private:
    mutable std::unique_ptr<ExpensiveResource> resource_;

public:
    void request() const
    {
        if (!resource_)
        {
            resource_ = std::make_unique<ExpensiveResource>();
        }
        resource_->operation();
    }
};

// ------------------ Copy-on-Write Proxy Example ------------------

// A simple Document class representing an object with modifiable content.
class Document
{
public:
    std::string content;
    Document(const std::string &text) : content(text) {}
    void modify(const std::string &newContent)
    {
        content = newContent;
    }
    void display() const
    {
        std::cout << "Document Content: " << content << std::endl;
    }
};

// DocumentProxy implements a copy-on-write mechanism:
// It holds a shared pointer to a Document. When a write operation is requested
// and the document is shared, it creates a private copy before modification.
// The private resource pointer is named resource_
class DocumentProxy
{
private:
    std::shared_ptr<Document> resource_;

public:
    DocumentProxy(const std::string &text) : resource_(std::make_shared<Document>(text)) {}

    // Read operation: simply delegate to the document.
    void display() const
    {
        resource_->display();
    }

    // Write operation: triggers copy-on-write if the document is shared.
    void modify(const std::string &newContent)
    {
        // If there are multiple references, create a private copy
        if (!resource_.unique())
        {
            resource_ = std::make_shared<Document>(resource_->content);
        }
        resource_->modify(newContent);
    }
};

int main()
{
    // Virtual Proxy demonstration:
    std::cout << "Virtual Proxy Example:" << std::endl;
    VirtualProxy virtualProxy;
    // The expensive resource is not initialized until request() is called.
    virtualProxy.request();
    virtualProxy.request();

    std::cout << std::endl;

    // Copy-on-Write Proxy demonstration:
    std::cout << "Copy-on-Write Proxy Example:" << std::endl;
    DocumentProxy docProxy("Initial Content");
    docProxy.display();

    // Simulate sharing the document proxy
    DocumentProxy docProxy2 = docProxy; // Now docProxy and docProxy2 share the same Document

    // Modify docProxy2 (this will trigger copy-on-write)
    docProxy2.modify("Modified Content");

    std::cout << "After modification:" << std::endl;
    std::cout << "docProxy: ";
    docProxy.display();
    std::cout << "docProxy2: ";
    docProxy2.display();

    return 0;
}