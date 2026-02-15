# C_Vector
This library is most likely not the best, but it is something
The goal is to mimic the std::vector functionality and have "overloading" to make your life easier.


## Functions

- `vector( typeof ) foo`
This initializes a vector object
- `vector_push_back( foo, value )`
Adds `value` onto the end of vector `foo`
- `vector_free( foo )`
Frees vector object from memory
- `vector_capacity( foo )`
Returns `size_t` of capacity
- `vector_at()`
vector_front
vector_back
vector_reserve
vector_clear
vector_empty
vector_resize
vector_erase
vector_shrink_to_fit
