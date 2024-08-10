1, shared_ptr
    - Introduce
        - As shown in the example, a smart pointer is a class template that you declare on the stack, and initialize by using a weak pointer that points to a heap-allocated object.
        - The smart pointer destructor contains the call to delete, and because the smart pointer is declared on the stack, its destructor is invoked when the smart pointer goes out of scope, even if an exception is thrown somewhere further up the stack.

    - Defination: 
        - The shared_ptr class describes an object that uses reference counting to manage resources. A shared_ptr object effectively holds a pointer to the resource that it owns or holds a null pointer. A resource can be owned by more than one shared_ptr object; when the last shared_ptr object that owns a particular resource is destroyed, the resource is freed. The size is two pointers; one for the object and one for the shared control block that contains the reference count.

        - All the instances point to the same object, and share access to one "control block" that increments and decrements the reference count whenever a new shared_ptr is added, goes out of scope, or is reset. When the reference count reaches zero, the control block deletes the memory resource and itself.

    - **Notice**
        - Pass the `shared_ptr` by value. This invokes the copy constructor, increments the reference count, and makes the callee an owner.

        -Pass the `shared_ptr` by reference or const reference. In this case, the reference count isn't incremented, and the callee can access the pointer as long as the caller doesn't go out of scope.

    - Use case and Risk
        - Construction:
            std::shared_ptr<int> ptr1 = std::make_shared<int>(5);
            std::shared_ptr<int> ptr1 = new int(5);
            std::shared_ptr<int> ptr1(new int(5));

            - Why we should use std::make_shared instead of new operator?
                --> Use the make_shared function to create a shared_ptr when the memory resource is created for the first time. make_shared is exception-safe. It uses the same call to allocate the memory for the control block and the resource, which reduces the construction overhead. If you don't use make_shared, then you have to use an explicit new expression to create the object before you pass it to the shared_ptr constructor.

        - We can create a shared_ptr point to shared_ptr:
            std::shared_ptr<int> ptr1 = std::make_shared<int>(5);
            std::shared_ptr<std::shared_ptr<int>> ptr2(&ptr1);

        -Leak Memory:
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

