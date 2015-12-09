/*
 * Author: Matt McFarland -- 12/8/2015
 * file: bitonic.h
 *
 * Description:
 * 		This file contains prototypes for functions used to find whether a 
 * 		bitonic array (defined below) contains a certain element.
 * 
 */

#ifndef BITONIC_h
#define BITONIC_h

/*
 * Given a bitonic array containing _size_ integers, this function will return the index
 * of the target element sought in the array if it is present in the array. Duplicate elements
 * should not exist in this bitonic array. This search performs with O(log(n)) efficiency.
 * 
 * Returns:
 * 		The index of the target in the bitonic array if it exists.
 * 		-1 if the target does not exist in the bitonic array or was found
 * 			on both the increasing and decreasing halves (duplicates)
 *
 * Note: If the target element is duplicated on the same half of the bitonic array (duplicates
 * 		exist exclusively on the increasing or decreasing half), this search function will return
 * 		an index of the first encountered instance of the duplicated target integer. It will not
 * 		detect duplicates that are exclusively on the side of the array.
 */
int bitonic_search(int * arr, int size, int target);

/*
 * Uses the bitonic_search function to find each and every element of the bitonic 
 * array of _size_ integers. This function will return the number of failed tests.
 */
int test_array(int * arr, int size);

#endif // BITONIC_h
