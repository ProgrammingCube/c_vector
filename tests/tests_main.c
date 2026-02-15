#include <stdio.h>
#include <assert.h>
#include "vector.h"

void test_growth()
{
    vector( int ) v = NULL;

    for ( int i = 0; i < 100; i++ )
    {
        vector_push_back( v, i );
    }

    assert( vector_size( v ) == 100 );
    assert( v[ 25 ] == 25 );
    assert( v[ 50 ] == 50 );
    assert( v[ 75 ] == 75 );
    assert( vector_capacity( v ) >= 100 );
    
    vector_free( v );
    printf( "Test Growth:\tPASSED\n" );
}

void test_at()
{
    vector( int ) v = NULL;
    vector_push_back( v, 100 );
    
    int* ptr = vector_at( v, 0 );
    assert( *ptr == 100 );

    // Test bounds check
    int* bad_ptr = vector_at( v, 500 );
    assert( bad_ptr == NULL );

    vector_free( v );
    printf( "Test At:\tPASSED\n" );
}

void test_shrink()
{
    vector( int ) v = NULL;

    for ( int i = 0; i < 100; i++ )
    {
        vector_push_back( v, i );
    }

    vector_pop_back( v );
    vector_pop_back( v );
    vector_pop_back( v );

    assert( v[ 96 ] == 96 );

    vector_free( v );
    printf( "Test Shrink:\tPASSED\n" );
}

void test_insert()
{
    vector( int ) v = NULL;

    for ( int i = 0; i < 10; i++ )
    {
        vector_push_back( v, i );
    }

    // Insert 99 at position 5
    vector_insert( v, 5, 99 );

    assert( v[ 5 ] == 99 );
    assert( v[ 6 ] == 5 ); // Original value at pos 5 should now be at pos 6

    vector_free( v );
    printf( "Test Insert:\tPASSED\n" );
}

void test_rets()
{
    vector( int ) v = NULL;

    for ( int i = 0; i < 100; i++ )
    {
        vector_push_back( v, i );
    }

    int* ptr = vector_front( v );
    assert( *ptr == 0 );
    ptr = vector_back( v );
    assert( *ptr == 99 );

    vector_free( v );
    printf( "Test Rets:\tPASSED\n" );
}

void test_clear()
{
    vector( int ) v = NULL;

    for ( int i = 0; i < 100; i++ )
    {
        vector_push_back( v, i );
    }

    vector_clear( v );
    assert( vector_size( v ) == 0 );
    assert( vector_empty( v ) );

    vector_free( v );
    printf( "Test Clear:\tPASSED\n" );
}

void test_empty()
{
    vector( int ) v = NULL;
    assert( vector_empty( v ) );

    vector_push_back( v, 1 );
    assert( !vector_empty( v ) );

    vector_free( v );
    printf( "Test Empty:\tPASSED\n" );
}

void test_erase()
{
    vector( int ) v = NULL;

    for ( int i = 0; i < 10; i++ )
    {
        vector_push_back( v, i );
    }

    // Erase element at position 5
    vector_erase( v, 5 );

    assert( v[ 5 ] == 6 ); // Original value at pos 6 should now be at pos 5
    assert( vector_size( v ) == 9 );

    vector_free( v );
    printf( "Test Erase:\tPASSED\n" );
}

/*
void test_resize()
{
    vector( int ) v = NULL;

    vector_resize( v, 5, 42 );
    assert( vector_size( v ) == 5 );
    for ( int i = 0; i < 5; i++ )
    {
        assert( v[ i ] == 42 );
    }

    vector_resize( v, 10, 99 );
    assert( vector_size( v ) == 10 );
    for ( int i = 0; i < 5; i++ )
    {
        assert( v[ i ] == 42 ); // Original values should remain
    }
    for ( int i = 5; i < 10; i++ )
    {
        assert( v[ i ] == 99 ); // New values should be set to default
    }

    vector_free( v );
    printf( "Test Resize:\tPASSED\n" );
}
*/

void test_shrinktofit()
{
    vector( int ) v = NULL;

    for ( int i = 0; i < 100; i++ )
    {
        vector_push_back( v, i );
    }

    for ( int i = 0; i < 90; i++ )
    {
        vector_pop_back( v );
    }

    size_t old_capacity = vector_capacity( v );
    vector_shrink_to_fit( v );
    size_t new_capacity = vector_capacity( v );

    assert( new_capacity >= vector_size( v ) );
    assert( new_capacity < old_capacity );

    vector_free( v );
    printf( "Test Shrink To Fit:\tPASSED\n" );
}

int main()
{
    test_growth();
    test_at();
    test_shrink();
    test_insert();
    test_rets();
    test_clear();
    test_empty();
    test_erase();
    //test_resize();
    test_shrinktofit();
    return 0;
}