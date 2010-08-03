# Copyright 2010 Dan Colish
# All rights reserved.
#
# This file is part of 'snoctxt' and is distributed under the BSD license.
# See LICENSE for more details.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char *argv []) {
    if (argc > 0) {
        int i;
        size_t len = 0;
        int nlines = 0;
        int ilines = 0;
        char** lines = NULL;
        char** newlines = NULL;
        char* s_snoc_src = argv[1];
        char* s_snoc_dst = argv[2];
        FILE* snoc_src = fopen(s_snoc_src, "r");
        FILE* snoc_dst = fopen(s_snoc_dst, "r+");

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
    }

    return 0;
}
