#include <stdio.h>
#include <string.h>
#include "quicksort.h"

/* Static (private to this file) function prototypes. */
static void swap(void *a, void *b, size_t size);
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*));
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*));

// Return 1 if first int is bigger, -1 if second int is bigger, 0 if same
int int_cmp(const void *a, const void *b) {
	int *first = (int *)a;
	int *second = (int *)b;
	if (*first > *second) {
		return 1;
	}
	else if (*first < *second) {
		return -1;
	}
	else {
		return 0;
	}
}

// Return 1 if first double is bigger, -1 if second double is bigger, 0 if same
int dbl_cmp(const void *a, const void *b) {
	double *first = (double *)a;
	double *second = (double *)b;
	if (*first > *second) {
		return 1;
	}
	else if (*first < *second) {
		return -1;
	}
	else {
		return 0;
	}
}

// Return 1 if first string is bigger, -1 if second string is bigger, 0 if same
int str_cmp(const void *a, const void *b) {
	char *first = (char *)a;
	char *second = (char *)b;
	if (strcmp(first, second) > 0) {
		return 1;
	}
	else if (strcmp(first, second) < 0) {
		return -1;
	}
	else {
		return 0;
	}
}

// Sort array using quicksort_helper
void quicksort(void *array, size_t len, size_t elem_sz, int (*cmp) (const void*, const void*)) {
	quicksort_helper(array, 0, len - 1, elem_sz, cmp);
}

/**
 * Swaps the values in two pointers.
 *
 * Casts the void pointers to type (char *) and works with them as char pointers
 * for the remainder of the function. Swaps one byte at a time, until all 'size'
 * bytes have been swapped. For example, if ints are passed in, size will be 4
 * and this function will swap 4 bytes starting at a and b pointers.
 */
static void swap(void *a, void *b, size_t size) {
    // TODO
    char *a_char = (char *)a;
    char *b_char = (char *)b;
    char m = 'm';
    char *temp = &m;
    for (int i = 0; i < size; i++) {
	*temp = *a_char;
	*a_char = *b_char;
	*b_char = *temp;
	a_char++;
	b_char++;
    }
}

/**
 * Partitions array around a pivot, utilizing the swap function. Each time the
 * function runs, the pivot is placed into the correct index of the array in
 * sorted order. All elements less than the pivot should be to its left, and all
 * elements greater than or equal to the pivot should be to its right.
 */
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*)) {
    // TODO 

    char *array_copy = (char *)array;
    
/*
    else if (elem_sz == 8) {
	double *array_copy = (double *)array;
	double *pivot = &array_copy[left];
    }
    else {
	int *array_copy = (int *)array;
	int *pivot = &array_copy[left];
    }*/

//    pivot = &array[left];

    int s = left;
    char *pivot = array_copy;
    for (int i = left + 1; i <= right; i++) {
	/*
	    if (*(array_copy + i * elem_sz) < *pivot) {
		s++;
		swap((array_copy + s * elem_sz), (array_copy + i * elem_sz), elem_sz);	
	}
	*/
	    //fprintf(stderr, "%d\n", *pivot);
	    if (cmp((array_copy + i * elem_sz), pivot) == -1) {
		s++;
		swap((array_copy + s * elem_sz), (array_copy + i * elem_sz), elem_sz);
	    }
    }
    swap((array_copy + left * elem_sz), (array_copy + s * elem_sz), elem_sz);
    // swap((array_copy + left * elem_sz), (array_copy + s * elem_sz), elem_sz);
    return s;
}

/**
 * Sorts with lomuto partitioning, with recursive calls on each side of the
 * pivot.
 * This is the function that does the work, since it takes in both left and
 * right index values.
 */
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*)) {
    // TODO
    int s;
    if (left < right) {
	s = lomuto(array, left, right, elem_sz, cmp);
	quicksort_helper(array, left, s - 1, elem_sz, cmp);
	quicksort_helper(array, s + 1, right, elem_sz, cmp);
    }
}
