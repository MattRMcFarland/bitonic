// This is the text editor interface. 
// Anything you type or change here will be seen by the other person in real time.
#include "bitonic.h"
#include <stdio.h>


/*
 * Private constants
 */
#define INCREASING  1
#define DECREASING  0

/*
 * Private Prototypes for functions used in bitonic_search
 */

/*
 * recursive function called on sub arrays to find the pivot
 */
int find_pivot_index(int * global_arr, int * global_tail, int * head, int * tail);

/*
 * given an array of _size_ integers that is sorted in INCREASING or DECREASING order, use
 * a binary search to locate the target element
 * 
 * return -1 if element is not found
 * return index of element in sub array if it is
 */
int find_element(int * arr, int size, int arr_type, int target);


/*
 * Given a bitonic array containing _size_ integers, will return the index
 * of the target element. returns -1 if element is not found
 */
int bitonic_search(int * arr, int size, int target) {

    int pivot_index, increasing_search_result, decreasing_search_result;
    int found_target_at = -1;
    decreasing_search_result = increasing_search_result = -1;      // initialize to not found 

    if (!arr || size <= 0)
        return -1;          // error

    else if (size == 1) {   // 1 element array

        if (*arr == target)
            return 0;
        else
            return -1; 

    }

    pivot_index = find_pivot_index(arr, arr + size, arr, arr + size);

    if (pivot_index == size)        // array is strictly INCREASING
        increasing_search_result = find_element(arr, size, INCREASING, target);

    else if (pivot_index == 0)      // array is strictly DECREASING
        decreasing_search_result = find_element(arr, size, DECREASING, target);

    else {                          // search both halves
        increasing_search_result = find_element(arr, pivot_index + 1, INCREASING, target);
        decreasing_search_result = find_element(&arr[pivot_index + 1], size - pivot_index - 1, DECREASING, target);
    }

    if (increasing_search_result >= 0 && decreasing_search_result >= 0)
        found_target_at = -1;       // found duplicates on INCREASING and DECREASING sides

    else if (increasing_search_result >= 0)
        found_target_at = increasing_search_result;    // found target exclusively on the INCREASING half

    else if (decreasing_search_result >= 0) {          // found target on the DECREASING SIDE

        if (pivot_index > 0)
            found_target_at = decreasing_search_result + pivot_index + 1;  // normalize for one indexing of pivot

        else 
            found_target_at = decreasing_search_result; // found target in a strictly DECREASING array 
    }

    return found_target_at;                             // did not find the target
}

/* 
 * Returns index of pivot point of a bitonic array.
 */
int find_pivot_index(int * global_head, int * global_tail, int * sub_head, int * sub_tail) {
    
    // find center
    int size = (int)(sub_tail - sub_head) + 1;
    int center_index = size / 2;
    int pivot_index;

    // where the pivot point can exist -
    //      
    //      when sub_head[center_index] > sub_head[center_index - 1] && sub_head[center_index] > sub_head[center_index + 1]
    //      OR
    //      when sub_head == global_head && center_index == 0;
    //      OR
    //      when sub_head == global_tail && center_index == 0

    if (&sub_head[center_index] == global_head)
        pivot_index = 0;                                                                                 // beginning of array

    else if (&sub_head[center_index] == global_tail)  
        pivot_index = (int)(global_tail - global_head);                                                  // end of array

    else if (sub_head[center_index] > sub_head[center_index - 1] &&     \
             sub_head[center_index] < sub_head[center_index + 1] )   // still increasing
        pivot_index = find_pivot_index(global_head, global_tail, &sub_head[center_index + 1], sub_tail);       // search right half of sub array

    else if (sub_head[center_index] < sub_head[center_index - 1] &&     \
             sub_head[center_index] > sub_head[center_index + 1] )   // decreasing section
        pivot_index = find_pivot_index(global_head, global_tail, sub_head, &sub_head[center_index - 1]);       // search left half of sub array

    else
        pivot_index = (int)(&sub_head[center_index] - global_head);

    return pivot_index;
        
}

/*
 * given an array of _size_ integers that is sorted in INCREASING or DECREASING order, use
 * a binary search to locate the target element.
 * 
 * return -1 if element is not found
 * return index of element in sub array if it is
 */
int find_element(int * arr, int size, int arr_type, int target) {

    int center_element;
    int center_index;
    int found_at = -2;

    if (!arr || size == 0) 
        return -1;
    

    /* base case */
    if (size == 1) {

        if (target == *arr)
            found_at = 0;
        else
            found_at = -1;

    } 

    /* recurse further */
    else {

        center_index = size / 2;
        center_element = arr[center_index];

        if ( (center_element < target && arr_type == INCREASING) ||  \
             (center_element > target && arr_type == DECREASING) )   {

            found_at = find_element(&arr[center_index + 1], size - center_index - 1, arr_type, target);
            if (found_at >= 0)
                found_at += center_index + 1; // found_at the element, so normalize index to caller

        } 

        else if ( (center_element > target && arr_type == INCREASING) ||  \
                  (center_element < target && arr_type == DECREASING) )   { 
            found_at = find_element(arr, center_index, arr_type, target);
        }


        else
            found_at = center_index;

    }

    return found_at;
}

/*
 * Tests the bitonic_search on each and every integer within the bitonic array.
 * Returns the number of failed tests. Returns 0 if no tests fail for the array.
 */
int test_array(int * arr, int size) {

    int quiet_mode = 0;
    int failures = 0;
    int search_result;

    if (!arr)
        return -1;

    if (size > 100) {
        printf("Testing array with %d elements. I'll discontinue my status print statements for this one.\n", size);
        quiet_mode = 1;
    }

    if (!quiet_mode) {
        printf("Testing Array: ");
        for (int i = 0; i < size; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }

    for (int i = 0; i < size; i++) {
        search_result = bitonic_search(arr, size, arr[i]);
        if (search_result != i) 
            failures++;

        if (!quiet_mode) printf("Looking for element %d. Should be at: %d. Found at %d.\n", arr[i], i, search_result);        
    }

    return failures;
}
