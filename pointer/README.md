# Smart Pointer
## shared_ptr
### Introduce
- The smart pointer is a class template that you `declare on the stack`, and initialize by using a weak pointer that `points to a heap-allocated object`.

- The smart pointer destructor contains the call to delete, and because the smart pointer is declared on the stack, its destructor is invoked when the smart pointer goes out of scope, even if an exception is thrown somewhere further up thestack.
### Defination: 
- The shared_ptr class describes an object that uses reference counting to manage resources. A shared_ptr objecteffectively holds a pointer to the resource that it owns or holds a null pointer. A resource can be owned by more thanone shared_ptr object; when the last shared_ptr object that owns a particular resource is destroyed, the resource is freed. The size is two pointers; one for the object and one for the shared control block that contains the reference count.

- All the instances point to the same object, and share access to one `control block` that increments and decrements thereference count whenever a new shared_ptr is added, goes out of scope, or is reset. When the reference count reaches zero,the control block deletes the memory resource and itself.

### Operation
- Construction:
```c++
std::shared_ptr<int> ptr1 = std::make_shared<int>(5);
std::shared_ptr<int> ptr1 = new int(5);
std::shared_ptr<int> ptr1(new int(5));
```
- We can create a shared_ptr point to shared_ptr:
```c++
        std::shared_ptr<int> ptr1 = std::make_shared<int>(5);
        std::shared_ptr<std::shared_ptr<int>> ptr2(&ptr1);
```

- Why we should use std::make_shared instead of new operator?
--> Use the make_shared function to create a shared_ptr when the memory resource is created for the first time. make_shared is exception-safe. `It uses the same call to allocate the memory for the control block and theresource, which reduces the construction overhead`. If you don't use make_shared, then you have to use an explicitnew expression to create the object before you pass it to the shared_ptr constructor.

**Note:**
- Pass the shared_ptr by `value`. This invokes the copy constructor, `increments the reference count`, and makes the calleean owner.
- Pass the shared_ptr by `reference or const reference`. In this case, `the reference count isn't incremented`, and thecallee can access the pointer as long as the caller doesn't go out of scope.
- When a shared_ptr destroy (reference count = 0), it will call destructor of object.

### Risk
- Leak Memory:
```c++
        class Tester
        {
            public:
            Tester() {cout << "constructor" << endl;}
            ~Tester() {cout << "destructor" << endl;}
            void setShare_ptr(shared_ptr<Tester> sp){ p1 = sp;}
            private:
            shared_ptr<Tester> p1;
            
        };
        int main()
        {
            shared_ptr<Tester> hehe = make_shared<Tester>();
            {
                shared_ptr<Tester> hihi = make_shared<Tester>();
                hehe->setShare_ptr(hihi);
                hihi->setShare_ptr(hehe);
            }
            cout << hehe.use_count() << endl; //2, Tester Destructor cannot call to destroy object.
            return 0;
        }
```
## unique_ptr
### Defination: 
- It `can not be copied` to another unique_ptr, passed by value to a function, or used in any C++ Standard Library algorithm that requires copies to be made. A unique_ptr can only be moved.

- In the range for loop, notice that the unique_ptr is passed by reference. If you try to pass by value here, the compiler will throw an error because the `unique_ptr copy constructor is deleted`.

- We can use std::move() to change object’s owner:
```c++
    std::unique_ptr<int> ptr1 = std::make_unique<int>(10);
    std::unique_ptr<int> ptr2 = std::move(ptr1);

    // *ptr2 = 10; ptr1 -> null 
    std::cout << ptr1 << std::endl; // print 0
```

### make_unique
-When you make a call like 
```c++ 
    func(new A(), new B());
``` 
- The compiler may choose to evaluate the function arguments from left to right, or in any order it so wishes. Let's assume left to right evaluation: What happens when the first new expression succeeds but the second new expression throws?

- The real danger here is when you catch such exception; Yes, you may have caught the `exception thrown by new B()`, and resume normal execution, but `new A() already succeeded`, and its `memory will be silently leaked`. Nobody to clean it up... * sobs...

- But with make_unique, you `cannot have a leak` because `stack unwinding will happen (the destructor of the previously created object will run)`. Hence, having a preference for make_unique will constrain you towards exception safety.