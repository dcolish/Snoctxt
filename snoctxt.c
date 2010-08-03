#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_ln(FILE* foo) {
    int lines = 0;
    size_t len;
    while(fgetln(foo, &len)) {
        foo += len;
        lines++;
    }
    return lines;
}


int main(int argc, char *argv []) {
    if (argc > 0) {
        int i;
        size_t len = 0;
        int nlines = 0;
        int ilines = 0;
        char* lnptr = NULL;
        char** lines = NULL;
        char* s_snoc_src = argv[1];
        char* s_snoc_dst = argv[2];
        FILE* snoc_src = fopen(s_snoc_src, "r");
        FILE* snoc_dst = fopen(s_snoc_dst, "r+");

        nlines = count_ln(snoc_dst);
        lines = (char**)malloc(sizeof(char) * 512 * nlines);
        rewind(snoc_dst);

        for (i = 0; i < nlines; i++) {
            lnptr = fgetln(snoc_dst, &len);
            lines[i] = (char*)malloc(sizeof(char) * len);
            strcpy(lines[i], lnptr);
        }

        rewind(snoc_dst);

        while(lnptr = fgetln(snoc_src, &len)){
            fprintf(snoc_dst, "%s", lnptr);
            ilines += len;
        }

        fseek(snoc_dst, ilines, SEEK_SET);
        for (i = 0; i < nlines; i++) {
            fprintf(snoc_dst, "%s", lines[i]);
        }

        fclose(snoc_src);
        fclose(snoc_dst);
    }

    return 0;
}
