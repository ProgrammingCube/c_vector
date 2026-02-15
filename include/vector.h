#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <string.h>

// --- Visibility Logic ---
#if defined(_WIN32) || defined(__CYGWIN__)
  #ifdef VECTOR_EXPORTS
    #define VECTOR_API __declspec(dllexport)
  #else
    #define VECTOR_API __declspec(dllimport)
  #endif
#else
  #if __GNUC__ >= 4
    #define VECTOR_API __attribute__ ((visibility ("default")))
  #else
    #define VECTOR_API
  #endif
#endif


// [ header ][ data ... ]

/**
 * @brief Vector structure type.
 * 
 * This structure points to the beginning of the vectored data of given (type)
 * 
 * @param type The type of data to store in the vector structure
 * @return void
 */
#define vector(type) type*

// vector_insert hidden functions
#define _vector_insert_3(v, pos, val) \
    _vector_insert_4(v, pos, 1, val)
#define _vector_insert_4(v, pos, count, val) \
    do { \
        size_t _n = (count); \
        void* _tmp = _vec_prepare_insert((v), (pos), _n, sizeof(*(v))); \
        if (_tmp) { \
            (v) = (typeof(v))_tmp; \
            for(size_t _i = 0; _i < _n; ++_i) { (v)[(pos) + _i] = (val); } \
            _vec_set_size((v), vector_size(v) + _n); \
        } \
    } while(0)
#define _vector_insert_5(v, pos, start, end, src) \
    do { \
        size_t _n = (end) - (start); \
        void* _tmp = _vec_prepare_insert((v), (pos), _n, sizeof(*(v))); \
        if (_tmp) { \
            (v) = (typeof(v))_tmp; \
            memcpy(&(v)[pos], &(src)[start], _n * sizeof(*(v))); \
            _vec_set_size((v), vector_size(v) + _n); \
        } \
    } while(0)

// Argument helper, returns the 6th argment, the name we want
#define _GET_VEC_INSERT_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME

#define vector_insert(...) \
    _GET_VEC_INSERT_MACRO(__VA_ARGS__, _vector_insert_5, _vector_insert_4, _vector_insert_3)(__VA_ARGS__)




/**
 * @brief Push back item to vector
 * 
 * @param v Pointer to vector structure
 * @param value Data item to push back onto
 */
#define vector_push_back(v, value) \
    do { \
        void* _tmp = _vec_grow_if_needed((v), sizeof(*(v))); \
        if (_tmp) { \
            (v) = _tmp; \
            (v)[vector_size(v)] = (value); \
            _vec_set_size((v), vector_size(v) + 1); \
        } else { \
            fprintf( stderr, "VECTORLIB: Out of memory\n" ); \
            /* Handle Out of Memory here if you want */ \
        } \
    } while(0)
    // add stderr trace if v is null

#define vector_free(v)  _vec_free_internal(v)
#define vector_size(v) ((v) ? _vec_get_header(v)->size : 0)
#define vector_capacity(v) ((v) ? _vec_get_header(v)->capacity : 0)

#define vector_at(v, index) ((typeof(v))_vec_at((v), (index)))
#define vector_pop_back(v) \
    do { \
        if (vector_size(v) > 0) { \
            _vec_set_size((v), vector_size(v) - 1); \
        } \
    } while(0)
#define vector_front(v) (vector_at((v),0))
#define vector_back(v) (vector_at((v), vector_size(v) - 1))
#define vector_reserve(v, n) \
    do { \
        if ((n) > vector_capacity(v)) { \
            void* _tmp = _vec_realloc_heap((v), (n), sizeof(*(v))); \
            if (_tmp) (v) = (typeof(v))_tmp; \
        } \
    } while(0)
#define vector_clear(v) (_vec_set_size((v), 0))
#define vector_empty(v) (vector_size(v) == 0)
#define vector_resize(v, new_size, default_value) \
    do { \
        size_t _current_size = vector_size(v); \
        if ((new_size) > _current_size) { \
            void* _tmp = _vec_realloc_heap((v), (new_size), sizeof(*(v))); \
            if (_tmp) { \
                (v) = _tmp; \
                for (size_t _i = _current_size; _i < (new_size); ++_i) { \
                    (v)[_i] = (default_value); \
                } \
                _vec_set_size((v), (new_size)); \
            } else { \
                fprintf( stderr, "VECTORLIB: Out of memory\n" ); \
            } \
        } else { \
            _vec_set_size((v), (new_size)); \
        } \
    } while(0)
#define vector_erase(v, pos) \
    do { \
        if (pos < vector_size(v)) { \
            size_t _num_to_move = vector_size(v) - pos - 1; \
            if (_num_to_move > 0) { \
                memmove(&(v)[pos], &(v)[pos + 1], _num_to_move * sizeof(*(v))); \
            } \
            _vec_set_size((v), vector_size(v) - 1); \
        } \
    } while(0)
#define vector_shrink_to_fit(v) \
    do { \
        if ((v) && vector_capacity(v) > vector_size(v)) { \
            /* We realloc to exactly the current size */ \
            void* _tmp = _vec_realloc_heap((v), vector_size(v), sizeof(*(v))); \
            if (_tmp) (v) = (typeof(v))_tmp; \
        } \
    } while(0)

// --- Internal core functions ( compiled in .c ) ---
typedef struct
{
    size_t size;
    size_t capacity;
    size_t element_size;
} VectorHeader;

// Helper to get the header pointer for the data pointer
static inline VectorHeader* _vec_get_header( void* data )
{
    return ( VectorHeader* )( ( char* )data - sizeof( VectorHeader ) );
}

// Function declarations ( implemented in vector_core.c )
VECTOR_API void* _vec_grow_if_needed( void* data, size_t item_size );
VECTOR_API void  _vec_set_size( void* data, size_t new_size );
VECTOR_API void  _vec_free_internal( void* data );
VECTOR_API void* _vec_at( void* data, size_t index );
VECTOR_API void* _vec_prepare_insert( void* data, size_t pos, size_t count, size_t item_size );
VECTOR_API void* _vec_realloc_heap( void* data, size_t needed_cap, size_t item_size );

#endif