/*
 * Copyright 2010 Dan Colish
 * All rights reserved.
 *
 * This file is part of 'snoctxt' and is distributed under the BSD license.
 * See LICENSE for more details.
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int count_ln(FILE* foo) {
    int lines = 0;
    size_t len;
    while(fgetln(foo, &len)) {
        lines++;
    }
    return lines;
}


char** copy_lines(FILE* snoc_dst, int nlines) {
    int i = 0;
    char* lnptr = NULL;
    char** lines = NULL;
    size_t len;

    rewind(snoc_dst);
    lines = (char**)malloc(sizeof(char*) * nlines);
    while((lnptr = fgetln(snoc_dst, &len))) {
        lines[i] = (char*)malloc(sizeof(char) * len+1);
        strncpy(lines[i], lnptr, len);
        i++;
    }

    rewind(snoc_dst);
    return lines;
}


void fprintln(FILE* dst, char** lines, int nlines) {
    int i = 0;
        
    for (i = 0; i < nlines; i++) {
        fprintf(dst, "%s", lines[i]);
    }
}

void free_array(void** array, int size){
    int i;
    for (i = 0; i < size; i++) {
        free(array[i]);
    }

    free(array);
}

int main(int argc, char** argv) {

   
    int c;


    int nlines = 0;
    int ilines = 0;

    char* s_snoc_dst;
    char* s_snoc_src;
    char* message;

    char** lines = NULL;
    char** newlines = NULL;

    FILE* snoc_src;
    FILE* snoc_dst;

    while (1) {
         static struct option long_otps[] = {
             {"source", required_argument, 0, 's'},
             {"destination", required_argument, 0, 'd'},
             {0, 0, 0, 0}
         };
        int option_index = 0;    
        c = getopt_long(argc, argv, "s:d:", long_otps,
                        &option_index);

        if (c == -1) {
            break;
        }

        switch (c) { 
            
        case 's':
            s_snoc_src = malloc(sizeof optarg);
            strcpy(s_snoc_src, optarg);
            break;

        case 'd':
            s_snoc_dst = malloc(sizeof optarg);
            strcpy(s_snoc_dst, optarg);
            break;

        default:
            message = "Illegal Option Found\n";
            printf("%s", message);
            abort();
        }
    }
    snoc_src = fopen(s_snoc_src, "r");
    snoc_dst = fopen(s_snoc_dst, "r+");
    if (!snoc_src || !snoc_dst) {
        printf("%s\n", "One or more of the specified files were not found");
        return 1;
    }

    nlines = count_ln(snoc_dst);
    ilines = count_ln(snoc_src);
    lines = copy_lines(snoc_dst, nlines);

    newlines =  copy_lines(snoc_src, ilines);
    snoc_dst = freopen(s_snoc_dst, "w", snoc_dst);

    fprintln(snoc_dst, newlines, ilines);
    fprintln(snoc_dst, lines, nlines);

    free_array((void**)lines, nlines);
    free_array((void**)newlines, ilines);
        
    fclose(snoc_src);
    fclose(snoc_dst);


    return 0;
}
