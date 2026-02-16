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
Returns `size_t` of capacity of vector `foo`
- `vector_at( foo, index )`
Returns pointer of type vector(`typeof`) at `index`
- `vector_front( foo )`
Returns pointer to first data item in vector `foo`
- `vector_back( foo )`
Returns pointer to last data item in vector `foo`
- `vector_reserve( foo, size )`
Reserve `size` number of elements in vector `foo`
- `vector_clear( foo )`
Set size of vector `foo` to zero
- `vector_empty( foo )`
Set size of vector `foo` to zero  (?)
- `vector_resize( foo, size )`
Resize vector `foo` to arbitrary `size`
- `vector_erase( foo, index )`
Remove element at `index` from vector `foo`
- `vector_shrink_to_fit( foo )`
Optimize vector `foo` to fit `foo->capacity = foo->size`
- `vector_insert( foo, position, value )`
Inserts `value` into vector `foo` at `position`
- `vector_insert( foo, position, count, value )`
Inserts `count` of `value` into vector `foo` at `position`
- `vector_insert( foo, position, start, end, bar )`
Inserts subsection `start, end` of vector `bar` into vector `foo`
