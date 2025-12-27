#include <stdlib.h>

#include "defer.h"
#include "cleanup.h"

int main(void) {
    puts("program start");

    FILE *f = fopen("test.txt", "w");
    if (!f) {
        perror("fopen");
        return 1;
    }
    defer(cleanup_fclose, f);

    char *buf = malloc(64);
    if (!buf) {
        perror("malloc");
        return 1;
    }
    defer(cleanup_free, buf);

    puts("doing work");
    fprintf(f, "hello from defer\n");

    /* Uncomment to prove early-return safety */
    /*
    puts("early return");
    return 0;
    */

    puts("normal return");
    return 0;
}
