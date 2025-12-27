#ifndef CLEANUP_H
#define CLEANUP_H

#include <stdio.h>
#include <stdlib.h>

/* Free heap memory safely */
static inline void cleanup_free(void *p) {
    void *x = *(void **)p;
    if (x) {
        puts("buffer freed");
        free(x);
    }
}

/* Close FILE* safely */
static inline void cleanup_fclose(void *p) {
    FILE *f = *(FILE **)p;
    if (f) {
        puts("file closed");
        fclose(f);
    }
}

#endif /* CLEANUP_H */
