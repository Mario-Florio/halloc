# halloc

A basic heap allocator in C that replicates core functionality of `malloc` and `free`.

This project exposes two functions:

- `halloc(size_t size)`
- `hfree(void* ptr)`

Internally, it manages a fixed 640KB region via `mmap`, tracks allocations with a custom bitmap, and performs linear scanning for free blocks.

---

## halloc

```c
void* halloc(size_t size);
```
Allocates ```size``` bytes of memory from the managed heap. Returns a pointer to uninitialized memory. Unlike ```malloc```, a request of size 0 is considered invalid and will terminate the program.

#### Parameters:
* ```size```: number of bytes to allocate (must be > 0)

#### Behavior:
* If no sufficient space is available, the allocator exits with an error.
* All allocations are tracked using a simple bitmap scheme with encoded chunk size metadata.

---

## hfree
```c
void hfree(void* ptr);
```
Deallocates a memory block previously returned by ```halloc```.

#### Parameters:
* ```ptr```: memory space to deallocate

#### Behavior:
* If the pointer was never allocated or has already been freed, the function terminates the program.
* Successfully freeing memory updates the internal bitmap and heap state.

---

## Notes
* Total managed heap capacity is statically fixed at 640,000 bytes.
* This is a toy allocator for learning and experimentation purposes.
* No alignment guarantees or thread safety are provided.
