/*
 * Author: Matt McFarland -- 12/8/2015
 * file: bitonic_test.c
 *
 * This file includes an executable for that tests the bitonic_search function
 * developed in bitonic.c.
 */

#include <stdio.h> 		// for printing
#include "bitonic.h"	// for bitonic_search()

/*
 * Runs several tests on the bitonic_search function
 *
 * Returns 0 if all tests are successful. 
 * If tests fail, returns the number of failed tests.
 */
int main (void) {
    
    int status = 0, failures = 0;

    printf("Running bitonic array search tests\n");

    /* 
     * Create arrays to test
     */
    int empty[1] 		= {0};
    int regular_even[]  = {1, 2, 3, 5, 9, 8, 7, 4};
    int regular_odd[]   = {1, 2, 3, 4, 12, 11, 9};
    int edge_left[]     = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int edge_right[]    = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size_one[]      = {2};

    // create a long array with no duplicated elements that has a pivot in the middle
    int long_size = 1500;
    int long_array[long_size]; 
    int fill_val = -long_size / 2;
    for (int i = 0; i < long_size; i++) {
        long_array[i] = fill_val;

        if (i < long_size / 2) 
            fill_val = fill_val + 2;

        else if (i == long_size / 2)
            fill_val++;

        else
             fill_val = fill_val - 2;

    }

    /*
     * Run tests
     */
    if (-1 != bitonic_search(	   empty, 						    0, 	     42) ) failures++; 	// try size 0
    if (-1 != bitonic_search((void *)0x0, sizeof(empty) / sizeof(int), empty[0]) ) failures++;	// try null array pointer

    failures += test_array(regular_even,    sizeof(regular_even) / sizeof(int)  );
    failures += test_array(regular_odd,     sizeof(regular_odd) / sizeof(int)   );
    failures += test_array(edge_left,       sizeof(edge_left) / sizeof(int)     );
    failures += test_array(edge_right,      sizeof(edge_right) / sizeof(int)    );
    failures += test_array(size_one,        sizeof(size_one) / sizeof(int)      );
    failures += test_array(long_array,      sizeof(long_array) / sizeof(int)    );

    /*
     * Search for nonexistent values
     */
    if (-1 != bitonic_search(regular_even,	sizeof(regular_even) / sizeof(int), -1)) 	failures++;
 	if (-1 != bitonic_search(regular_even,	sizeof(regular_even) / sizeof(int), 100)) 	failures++;   
 	if (-1 != bitonic_search(regular_even,	sizeof(regular_even) / sizeof(int), 6)) 	failures++;
 	if (-1 != bitonic_search(size_one,		sizeof(size_one) / sizeof(int), 100)) 		failures++;

    if (failures != 0) {
        printf("%d tests failed\n", failures);
        status = 1;
    } else {
        printf("All tests succeeded!\n");
    }
        
    return status;
}
