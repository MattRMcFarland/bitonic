# Bitonic
How to check if a bitonic array contains a certain integer? 

## What is a bitonic array?
 A bitonic array is an array of integers that is sorted in increasing order
 to a certain point and then sorted in decreasing order after that point. It is
 assumed that bitonic array DOES NOT contain duplicate elements 
 
 Here are some examples of biotonic arrays:
 {1, 2, 3, 4, 5, 0, -1, -2, -3} 	 -- pivot point occurs at index 5
 {1, 3, 5, 7, 9, 8, 6, 4, 2, 0}	 -- pivot point occurs at index 4
 {1, 2, 3, 4, 5}		 			 -- pivot points occurs at the last element
 {5, 4, 3, 2, 1} 				 -- pivot points occurs at first element
 
  
## Purpose: 
 I was asked how to best search through a bitonic array as part of an interview,
 and I thought the exercise was interesting enough to merit a full implementation
 after the interview was over. This implementation uses a binary search to find 
 the array's pivot point and binary searches to examine the increasing and decreasing
 halves of the array for the sought element. Off-by-one errors and indexing bugs abounded
 during development. Implementing this in C made the task more difficult. 

## Build and Run
 Using this Makefile, just running "make" will compile the source object files and a test
 executable that tests the bitonic_search function.