## Mutex
### std::mutex 
- offers exclusive, non-recursive ownership semantics:

- A calling thread *owns* a `mutex` from the time that it successfully calls either [`lock`] or [`try_lock`].
- When a thread owns a `mutex`, all other threads will block (for calls to [`lock`]) or receive a false return value (for [`try_lock`]) if they attempt to claim ownership of the `mutex`.
- A calling thread must not own the `mutex` prior to calling [`lock`] or [`try_lock`].

**Note:** std::mutex is neither copyable nor movable

### std::shared_mutex
The shared_mutex class is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads. In contrast to other mutex types which facilitate exclusive access, a shared_mutex has two levels of access:
- `shared` - several threads can share ownership of the same mutex.
- `exclusive` - only one thread can own the mutex

If one thread has acquired the exclusive lock (through `lock, try_lock`), no other threads can acquire the lock (including the shared).

If one thread has acquired the shared lock (through `lock_shared, try_lock_shared`), no other thread can acquire the exclusive lock, but can acquire the shared lock.

```c++
smtx.lock_shared(); // better to use: std::shared_lock lock(smtx);
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

**Note:** The lock_guard class is `non-copyable` (Copy constructor is deleted)

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
- When a scoped_lock object is created, it attempts to take ownership of the mutexes it is given. When control leaves the scope in which the scoped_lock object was created, the scoped_lock is destructed and the `mutexes` are released.

```c++ 
std::scoped_lock lock(e1.m, e2.m); 
```
