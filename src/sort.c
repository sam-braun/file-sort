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
	if ((optind == 2 && argc == 3) || (optind == 1 && argc == 2)) {
		
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
	int j = 0;
	for (j = 0; j < MAX_ELEMENTS && fgets(buf[j], MAX_STRLEN, infile) != NULL; j++) {
		
		printf("in fgets loop\n");

		// replaces \n with \0 in strings
		char *eoln = strchr(buf[j], '\n');
		if (eoln != NULL) {
			*eoln = '\0';
		}
		//j++;
	}
	/*
	int i = 0;
	while (i < MAX_ELEMENTS) {
		if (fgets(buf[i], MAX_STRLEN, infile) == NULL) {
			break;
		}
		//fprintf(stdout, "%s\n", buf[i]);
		i++;
	}*/

	char buf_copy[j][MAX_STRLEN];
	int int_copy[j];
	double double_copy[j];
	for (int k = 0; k < j; k++) {
		strcpy(buf_copy[k], buf[k]);
		if (iflag == 1) {
			int_copy[k] = atoi(buf_copy[k]);
			printf("%d\n", int_copy[k]);
		} else if (dflag == 1) {
			double_copy[k] = atof(buf_copy[k]);
			printf("%f\n", double_copy[k]);
		}
		else {
			strcpy(buf_copy[k], buf[k]);
			printf("%s\n", buf_copy[k]);
		}
	}

	printf("passed fgets loop\n");

	// passing buf into quicksort
	if (dflag == 1) {
		quicksort((void *) double_copy, j, MAX_STRLEN, dbl_cmp);
	}
	else if (iflag == 1) {
		printf("right before iflag quicksort\n");
		quicksort((void *) int_copy, j, sizeof(int), int_cmp);
		printf("right after iflag quicksort\n");
	}
	else {
		quicksort((void *) buf_copy, j, MAX_STRLEN, str_cmp);
	}

	for (int l = 0; l < j; l++) {
		if (iflag == 1) {
			fprintf(stdout, "%d\n", int_copy[l]);
		}
		else if (dflag == 1) {
			fprintf(stdout, "%f\n", double_copy[l]);
		}
		else {
			fprintf(stdout, "%s\n", buf_copy[l]);
		}
	}

	/*int j = 0;
	hile (*buf[j] != "\n") {
		fprintf(stdout, "%s\n", buf[j]);
	}*/

//	fprintf(stdout, "%s", (char*) buf);


// prints buf to stdout and closes infile

	//	fputs((const char *restrict) buf, stdout);

//	fflush(stdout);
	fclose(infile);

	return EXIT_SUCCESS;

	// read data, takes in filename and outputs array
        // replace \n with \0
        //
        // filestream?
        // fputs string into a filestream: stdout, stdin, stderr, file itself
}
