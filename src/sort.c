#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"

#define MAX_STRLEN     64 // Not including '\0'
#define MAX_ELEMENTS 1024

void display_usage(char flag) {
	fprintf(stderr, "Error: Unknown option \'-%c\' received.\n"
                        "Usage: ./sort [-i|-d] [filename]\n"
                        "   -i: Specifies the input contains ints.\n"
                        "   -d: Specifies the input contains doubles.\n"
                        "   filename: The file to sort. If no file is "
                        "supplied, input is read from\n"
                        "             stdin.\n"
                        "   No flags defaults to sorting strings.\n", flag);
}

int main(int argc, char **argv) {

	int dflag = 0;
	int iflag = 0;
	int c;
	opterr = 0; // equivalent to : in bash

	while ((c = getopt(argc, argv, "di")) != -1) {
		switch(c) {
			case 'd':
				dflag = 1;
				break; // needed?
			case 'i':
				iflag = 1;
				break;
			case '?':
				display_usage(optopt);
				return EXIT_FAILURE;
			default:
				return EXIT_FAILURE;
		}
	}

	// tests for multiple filenames
	if (argc - 1 - optind > 0) {
		fprintf(stderr, "Error: Too many files specified.\n");
		return EXIT_FAILURE;
	}

	// tests for too many valid flags
	if (dflag + iflag > 1) {
		fprintf(stderr, "Error: Too many flags specified.\n");
		return EXIT_FAILURE;
	}

	char buf[MAX_ELEMENTS][MAX_STRLEN];

	FILE *infile;
	// tests for invalid filename
	if (optind == 1) {
		
	//	printf("inside optind == 1 loop");

		infile = fopen(argv[optind], "r");
		if (infile == NULL) {
			fprintf(stderr, "Error: Cannot open \'%s\'. "
					"%s.\n", argv[optind], strerror(errno));
			return EXIT_FAILURE;
		}
	}
	else {
		infile = stdin;

		printf("in infile = stdin line\n");
	}

	printf("passed error-checking\n");
	
	// when we do fgets, is there anything read into buf[i]? (what if loop is asking)
	for (int i = 0; i < MAX_ELEMENTS && fgets(buf[i], MAX_STRLEN, infile) != NULL; i++) {
		
		printf("in fgets loop\n");

		// replaces \n with \0 in strings
		char *eoln = strchr(buf[i], '\n');
		if (eoln != NULL) {
			*eoln = '\0';
		}
	}

	printf("passed fgets loop\n");
	
	// passing buf into quicksort
	if (dflag == 1) {
		quicksort((void *) buf, MAX_ELEMENTS, MAX_STRLEN, dbl_cmp);
	}
	else if (iflag == 1) {
		printf("right before iflag quicksort\n");
		quicksort((void *) buf, MAX_ELEMENTS, MAX_STRLEN, int_cmp);
		printf("right after iflag quicksort\n");
	}
	else {
		quicksort((void *) buf, MAX_ELEMENTS, MAX_STRLEN, str_cmp);
	}

//	fprintf(stdout, "%s", (char*) buf);


	// prints buf to stdout and closes infile
	fputs((const char *restrict) buf, stdout);
//	fflush(stdout);
	fclose(infile);

	return EXIT_SUCCESS;

	// read data, takes in filename and outputs array
        // replace \n with \0
        //
        // filestream?
        // fputs string into a filestream: stdout, stdin, stderr, file itself
}
