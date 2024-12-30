## Mutex
### std::mutex 
- offers exclusive, non-recursive ownership semantics:

- A calling thread *owns* a `mutex` from the time that it successfully calls either `lock` or `try_lock`.
- When a thread owns a `mutex`, all other threads will block (for calls to `lock`) or receive a false return value (for `try_lock`) if they attempt to claim ownership of the `mutex`.
- A calling thread must not own the `mutex` prior to calling `lock` or `try_lock`.

**Note:** std::mutex is neither copyable nor movable

### std::shared_mutex
The shared_mutex class is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads. In contrast to other mutex types which facilitate exclusive access, a shared_mutex has two levels of access:
- `shared` - several threads can share ownership of the same mutex.
- `exclusive` - only one thread can own the mutex

If one thread has acquired the exclusive lock (through `lock, try_lock`), no other threads can acquire the lock (including the shared).

If one thread has acquired the shared lock (through `lock_shared, try_lock_shared`), no other thread can acquire the exclusive lock, but can acquire the shared lock.

```c++
smtx.lock_shared(); // better to use: std::shared_lock lock(smtx);

#include <chrono>
#include <iostream>
#include <shared_mutex>
#include <syncstream>
#include <thread>
#include <mutex>
 
std::shared_mutex m;
int i = 10;
 
void read_shared_var(int id)
{
    // both the threads get access to the integer i
    std::shared_lock<std::shared_mutex> slk(m);
    const int ii = i; // reads global i

    std::osyncstream(std::cout) << '#' << id << " read i as " << ii << "...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::osyncstream(std::cout) << '#' << id << " woke up..." << std::endl;
}
 
int main()
{
    std::thread r1{read_shared_var, 1};
    std::thread r2{read_shared_var, 2};

    r1.join();
    r2.join();
}
```

### std::recursive_mutex (C++11)
The recursive_mutex class is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads.

If you want to call functions recursively, which lock the same mutex, then they either
- have to use one `recursive mutex`, or
- have to `unlock and lock` the `same non-recursive mutex` again and again (beware of concurrent threads!) (assuming this is semantically sound, it could still be a performance issue), or
- have to somehow annotate which mutexes they already locked (simulating recursive ownership/mutexes).

Example: `recursive_mutex`

```c++
class X
{
    std::recursive_mutex m;
    std::string shared;
public:
    void fun1()
    {
        std::lock_guard<std::recursive_mutex> lk(m);
        shared = "fun1";
        std::cout << "in fun1, shared variable is now " << shared << '\n';
    }
    
    void fun2()
    {
        std::lock_guard<std::recursive_mutex> lk(m);
        shared = "fun2";
        std::cout << "in fun2, shared variable is now " << shared << '\n';
        fun1(); // recursive lock becomes useful here
        std::cout << "back in fun2, shared variable is " << shared << '\n';
    }
};
```

Example: Using `non-recursive_mutex` have to unlock before.
```c++
class X
{
    std::mutex m;
    std::string shared;
public:
    void fun1()
    {
        std::lock_guard<std::mutex> lk(m);
        shared = "fun1";
        std::cout << "in fun1, shared variable is now " << shared << '\n';
    }
    void fun2()
    {
        std::lock_guard<std::mutex> lk(m);
        shared = "fun2";
        std::cout << "in fun2, shared variable is now " << shared << '\n';
        m.unlock();
        fun1(); // recursive lock becomes useful here
        std::cout << "back in fun2, shared variable is " << shared << '\n';
    }
};
```

## Lock
### std::lock_guard
-When a lock_guard object is created, it attempts to take ownership of the mutex it is given. When control leaves the scope in which the lock_guard object was created, the lock_guard is `destructed and the mutex is released`.
```c++
void safe_increment(int iterations)
{
    const std::lock_guard<std::mutex> lock(g_i_mutex);
    while (iterations-- > 0)
        g_i = g_i + 1;
    std::cout << "thread #" << std::this_thread::get_id() << ", g_i: " << g_i << '\n';
 
    // g_i_mutex is automatically released when lock goes out of scope
}
```

**Note:** 
- The lock_guard class is `non-copyable` (Copy constructor is deleted)
- only lock with mode `exclusive` althought you use std::shared_mutex

### std::unique_lock
- The class unique_lock is movable, but not copyable 

**Note:** Difference between std::lock_guard and std::uniue_lock is lock_guard will call lock() and unlock() automatically when construct and out of scope. otherwise, unique_lock can call lock, unlock anywhere if you want to self custom. 

- Constructor
```c++
unique_lock() noexcept;                         (1)	(since C++11)
unique_lock( unique_lock&& other ) noexcept;    (2)	(since C++11)
explicit unique_lock( mutex_type& m );          (3)	(since C++11)
unique_lock( mutex_type& m, std::defer_lock_t t ) noexcept; (4)	(since C++11)
unique_lock( mutex_type& m, std::try_to_lock_t t ); (5)	(since C++11)
unique_lock( mutex_type& m, std::adopt_lock_t t );
```

### std::scoped_lock
- The key feature of std::scoped_lock is that it can lock multiple mutexes simultaneously and guarantees that they are unlocked in the correct order when the lock object is destroyed.
- When a scoped_lock object is created, it attempts to take ownership of the mutexes it is given. When control leaves the scope in which the scoped_lock object was created, the scoped_lock is destructed and the `mutexes` are released.

```c++ 
std::scoped_lock lock(e1.m, e2.m); 
```

### std::defer_lock 
- A tag used with std::lock_guard or std::unique_lock in C++ to defer the locking of a mutex. 
It provides a way to create a lock object `without immediately locking the mutex`, allowing for more control over when the mutex is actually locked.

```c++
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void print_numbers(int id) {
    // Create the unique_lock object but do not lock the mutex yet
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    // Do some work without holding the lock
    std::cout << "Thread " << id << " is doing some work." << std::endl;
    // Now, explicitly lock the mutex at a later point in time

    lock.lock();
    std::cout << "Thread " << id << " is now locked and printing numbers." << std::endl;
    // Simulate some operation
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread " << id << ": " << i << std::endl;
    }

    // Lock is automatically released when it goes out of scope
}

int main() {
    std::thread t1(print_numbers, 1);
    std::thread t2(print_numbers, 2);

    t1.join();
    t2.join();

    return 0;
}
```
### std::adopt_lock 
- std::adopt_lock is a tag used with std::unique_lock in C++ to indicate that the lock object is not responsible for locking the associated mutex.
Instead, the mutex is assumed to be already locked when the std::unique_lock is created.
This tag is useful when you need to pass a mutex that's already locked by another part of your program to a std::unique_lock object, without trying to lock it again.

* When to Use std::adopt_lock?
You would use std::adopt_lock in situations where:

- You already have a mutex that has been locked by some other code (maybe by a std::lock_guard or another std::unique_lock).
- You need to pass that locked mutex into a std::unique_lock but do not want it to attempt locking the mutex again (which would cause undefined behavior or a deadlock).

**Note:** Only use std::adopt_lock when you're sure the mutex is already locked. If you try to use std::adopt_lock on an unlocked mutex, it will lead to undefined behavior.

```c++
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void print_numbers(int id) {
    // Lock the mutex using std::lock_guard
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Thread " << id << " has locked the mutex." << std::endl;

    // Now create a unique_lock, but do not lock the mutex again
    std::unique_lock<std::mutex> unique_lock(mtx, std::adopt_lock);
    
    // The mutex is now adopted by unique_lock, and it does not try to lock it again
    std::cout << "Thread " << id << " has adopted the already locked mutex." << std::endl;
    
    // Do some work while holding the lock
    std::cout << "Thread " << id << " is printing numbers." << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread " << id << ": " << i << std::endl;
    }

    // Mutex will be automatically released when unique_lock goes out of scope
}

int main() {
    // Start two threads
    std::thread t1(print_numbers, 1);
    std::thread t2(print_numbers, 2);

    t1.join();
    t2.join();

    return 0;
}
```