# heapalloc
A basic heap allocator in C.

The goal of heapalloc is to replicate the basic functionality of memory management found within the C standard library. The particular functions being mimicked are ```malloc``` and ```free```. Therefore heapalloc will expose two functions:
- ```halloc```
- ```hfree```

## halloc
```c
    void* halloc(size_t size);
```
Being a replica of malloc, halloc will allocate a specified amount of bytes and returns a pointer to the uninitialized memory space. Unlike malloc, halloc considers a size of 0 unintended behavior and consequently will exit.

#### Parameters
```size```: number of bytes to allocate

## hfree
```c
    void hfree(void* ptr);
```
Similar to free, hfree deallocates memory space allocates by halloc——hfree does not return a value. Passing both a pointer to a memory space which has not been previously allocated with halloc, or has already been freed with hfree, is considered unintended behavior and will cause hfree to exit.

#### Parameters
```ptr```: memory space to deallocate