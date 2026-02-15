#define VECTOR_EXPORTS
#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define VECTOR_INITIAL_CAPACITY 4
#define VECTOR_GROWTH_FACTOR    2

VECTOR_API void* _vec_grow_if_needed( void* data, size_t item_size )
{
    if ( data == NULL )
    {
        size_t total_size = sizeof( VectorHeader ) + ( VECTOR_INITIAL_CAPACITY * item_size );
        VectorHeader* h = ( VectorHeader* )malloc( total_size );
        if ( !h ) return NULL;

        h->size = 0;
        h->capacity = VECTOR_INITIAL_CAPACITY;
        h->element_size = item_size;

        return ( void* )( h + 1 );
    }

    VectorHeader* h = _vec_get_header( data );

    if ( h->size < h->capacity ) return data;

    // need to grow
    size_t new_cap = h->capacity * VECTOR_GROWTH_FACTOR;
    size_t new_total_size = sizeof( VectorHeader ) + ( new_cap * item_size );

    VectorHeader* new_h = ( VectorHeader* )realloc( h, new_total_size );
    if ( !new_h ) return NULL;

    new_h->capacity = new_cap;
    return ( void* )( new_h + 1 );
}

VECTOR_API void _vec_set_size( void* data, size_t new_size )
{
    if ( data == NULL ) return;
    VectorHeader* h = _vec_get_header( data );
    if ( new_size <= h->capacity )
    {
        h->size = new_size;
    }
}

VECTOR_API void _vec_free_internal( void* data )
{
    if ( data == NULL ) return;
    free( _vec_get_header( data ) );
}

//VECTOR_API void* _vec_at( void* data, size_t index )
//{
//    assert( ( 0 >= index ) && ( index < vector_size( data ) ) );
//    return ( void* )( &data[ index ] );
//}

VECTOR_API void* _vec_at( void* data, size_t index )
{
    if ( data == NULL ) return NULL;

    VectorHeader* h = _vec_get_header( data );

    // Robustness: Bounds checking
    if ( index >= h->size )
    {
        // In a true library, you might want to log an error or assert here
        return NULL; 
    }

    // 1. Cast to char* so pointer arithmetic happens in 1-byte increments
    // 2. Multiply index by element_size to find the exact byte offset
    return ( char* )data + ( index * h->element_size );
}

/**
 * @brief Prepares the vector for insertion by growing and shifting elements.
 * @return New data pointer (may change due to realloc)
 */
VECTOR_API void* _vec_prepare_insert( void* data, size_t pos, size_t count, size_t item_size )
{
    size_t current_size = vector_size( data );
    
    // 1. Ensure we have enough capacity for (current + count)
    // You might need a slightly modified version of grow_if_needed 
    // that accepts a specific "required" capacity.
    for( size_t i = 0; i < count; i++ )
    {
        data = _vec_grow_if_needed( data, item_size );
    }
    
    if ( !data ) return NULL;

    // 2. Shift elements to the right to make a "hole"
    // Use memmove because the source and destination overlap!
    if ( pos < current_size )
    {
        void* src = ( char* )data + ( pos * item_size );
        void* dst = ( char* )data + ( ( pos + count ) * item_size );
        size_t num_bytes = ( current_size - pos ) * item_size;
        memmove( dst, src, num_bytes );
    }
    return data;
}

VECTOR_API void* _vec_realloc_heap(void* data, size_t new_cap, size_t item_size) {
    // If no data exists, this is basically a new allocation
    if (!data) {
        size_t total_size = sizeof(VectorHeader) + (new_cap * item_size);
        VectorHeader* h = (VectorHeader*)malloc(total_size);
        if (!h) return NULL;
        h->size = 0;
        h->capacity = new_cap;
        h->element_size = item_size;
        return (void*)(h + 1);
    }

    VectorHeader* h = _vec_get_header(data);
    size_t total_size = sizeof(VectorHeader) + (new_cap * item_size);

    // realloc handles both shrinking and growing memory blocks
    VectorHeader* new_h = (VectorHeader*)realloc(h, total_size);
    if (!new_h) return data; // If realloc fails, return original data intact

    new_h->capacity = new_cap;
    return (void*)(new_h + 1);
}