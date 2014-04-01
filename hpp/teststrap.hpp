/*
 * File:   teststrap.hpp
 * Author: dariush
 *
 * Created on March 31, 2014, 9:36 PM
 */
#ifndef TESTSTRAP_HPP
#define	TESTSTRAP_HPP
#include <assert.h>
#include <typeinfo>
#include "bootstrap.hpp"
/**
 * Make sure the input is true
 */
#define BESURE(o) assert(o)
/**
 * Make sure the arguments are eqaul
 */
#define IS_EQUAL(o, z) BESURE(o == z)
/**
 * Make sure the arguments are NOT eqaul
 */
#define NOT_EQUAL(o, z) BESURE(o != z)
/**
 * Make sure the arguments are eqaul
 */
#define SHOULD_BE(o, z) IS_EQUAL(o, z)
/**
 * Make sure the arguments are NOT eqaul
 */
#define SHOULD_NOT_BE(o, z) NOT_EQUAL(o, z)
/**
 * Make sure the arguments are eqaul
 */
#define IS_SAME(o, z) IS_EQUAL(o, z)
/**
 * Make sure the arguments are NOT eqaul
 */
#define NOT_SAME(o, z) NOT_EQUAL(o, z)
/**
 * Make sure the argument is NOT null
 */
#define NOT_NULL(o) NOT_EQUAL(o,  NULL)
/**
 * Make sure the argument is NULL
 */
#define IS_NULL(o) IS_EQUAL(o,  NULL)
/**
 * Make sure the argument is IS_EQUAL to zero
 */
#define IS_ZERO(o) IS_EQUAL(o, 0)
/**
 * Make sure the argument is NOT IS_EQUAL to zero
 */
#define IS_NOT_ZERO(o) NOT_EQUAL(o, 0)
/**
 * Make sure the argument is true
 */
#define IS_TRUE(o) IS_EQUAL(o, true)
/**
 * Make sure the argument is NOT true
 */
#define IS_NOT_TRUE(o) IS_EQUAL(o, false)
/**
 * Make sure the argument is false
 */
#define IS_FALSE(o) IS_EQUAL(o, false)
/**
 * Make sure the argument is NOT false
 */
#define IS_NOT_FALSE(o) IS_EQUAL(o, true)
/**
 * Make sure the arguments are same type
 */
#define IS(o, z) IS_EQUAL(typeid(o).name(), typeid(z).name())
/**
 * Make sure the arguments are NOT same type
 */
#define IS_NOT(o, z) NOT_EQUAL(typeid(o).name(), typeid(z).name())
/**
 * Make sure the argument is a pointer
 */
#define IS_POINTER(o) IS_EQUAL(typeid(o).name()[0], 'P')
/**
 * Make sure the argument is NOT a pointer
 */
#define IS_NOT_POINTER(o) NOT_EQUAL(typeid(o).name()[0], 'P')
/**
 * Make sure the arguments WHICH ARE POINTERS are pointing same location
 */
#define PSAME_POINT(o, z) IS_SAME(o, z)
/**
 * Make sure the arguments WHICH ARE {NOT} POINTERS are pointing same location
 */
#define NSAME_POINT(o, z) IS_SAME(&o, &z)
/**
 * Make sure the arguments WHICH ARE POINTERS are NOT pointing same location
 */
#define PNOT_SAME_POINT(o, z) NOT_SAME(o, z)
/**
 * Make sure the arguments WHICH ARE {NOT} POINTERS are NOT pointing same location
 */
#define NNOT_SAME_POINT(o, z) NOT_SAME(&o, &z);
/**
 * Make sure the arguments are eqaul
 */
#define ASSERT_IS_EQUAL(o, z) IS_EQUAL(o, z)
/**
 * Make sure the arguments are NOT eqaul
 */
#define ASSERT_NOT_EQUAL(o, z) NOT_EQUAL(o, z)
/**
 * Make sure the arguments are eqaul
 */
#define ASSERT_SAME(o, z) IS_SAME(o, z)
/**
 * Make sure the arguments are NOT eqaul
 */
#define ASSERT_NOT_SAME(o, z) NOT_SAME(o, z)
/**
 * Make sure the argument is NOT null
 */
#define ASSERT_NOT_NULL(o) NOT_NULL(o)
/**
 * Make sure the argument is NULL
 */
#define ASSERT_NULL(o) IS_NULL(o)
/**
 * Make sure the argument is IS_EQUAL to zero
 */
#define ASSERT_ZERO(o) IS_ZERO(o)
/**
 * Make sure the argument is NOT IS_EQUAL to zero
 */
#define ASSERT_NOT_ZERO(o) IS_NOT_ZERO(o)
/**
 * Make sure the argument is true
 */
#define ASSERT_TRUE(o) IS_TRUE(o)
/**
 * Make sure the argument is NOT true
 */
#define ASSERT_NOT_TRUE(o) IS_NOT_TRUE(o)
/**
 * Make sure the argument is false
 */
#define ASSERT_FALSE(o) IS_FALSE(o)
/**
 * Make sure the argument is NOT false
 */
#define ASSERT_NOT_FALSE(o) IS_NOT_FALSE(o)
/**
 * Make sure the arguments are same type
 */
#define ASSERT_IS(o, z) IS(o, z)
/**
 * Make sure the arguments are NOT same type
 */
#define ASSERT_IS_NOT(o, z) IS_NOT(o, z)
/**
 * Make sure the argument is a pointer
 */
#define ASSERT_POINTER(o) IS_POINTER(o)
/**
 * Make sure the argument is NOT a pointer
 */
#define ASSERT_NOT_POINTER(o) IS_NOT_POINTER(o)
/**
 * Make sure the arguments WHICH ARE POINTERS are pointing same location
 */
#define ASSERT_PSAME_POINT(o, z) PSAME_POINT(o, z)
/**
 * Make sure the arguments WHICH ARE {NOT} POINTERS are pointing same location
 */
#define ASSERT_NSAME_POINT(o, z) NSAME_POINT(o, z)
/**
 * Make sure the arguments WHICH ARE POINTERS are pointing same location
 */
#define ASSERT_PNOT_SAME_POINT(o, z) NOT_PSAME_POINT(o, z)
/**
 * Make sure the arguments WHICH ARE {NOT} POINTERS are pointing same location
 */
#define ASSERT_NNOT_SAME_POINT(o, z) NOT_NSAME_POINT(o, z)

/*
 * Include your boostrap files
 */
#endif	/* TESTSTRAP_HPP */
