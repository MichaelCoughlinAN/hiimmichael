# defer-demo

A minimal, production-style example of **scope-exit cleanup in C** using GCC/Clang
`__attribute__((cleanup))`.

This provides Go-style `defer` behavior without fragile macro tricks or manual
`goto cleanup` blocks.

---

## Overview

The `defer` macro attaches a cleanup function to a variable so that the cleanup
runs automatically when the variable goes out of scope.

This includes:

* normal function exit
* early `return`
* error paths

Cleanup order is **LIFO** (last defer runs first), matching typical
resource-ownership semantics.

---

## File Layout

<pre>
defer-demo/
├── defer.h
├── cleanup.h
├── demo.c
└── README.md
</pre>

---

## Requirements

* GCC or Clang
* Linux or Linux-like environment
* C99 or newer

This implementation relies on `__attribute__((cleanup))`, which is widely
supported but not part of ISO C.

---

## Usage

Cleanup functions must have the following signature:

<pre>
void cleanup(void *p);
</pre>

### Example cleanup helpers

<pre>
static inline void cleanup_free(void *p) {
    void *x = *(void **)p;
    if (x) free(x);
}

static inline void cleanup_fclose(void *p) {
    FILE *f = *(FILE **)p;
    if (f) fclose(f);
}
</pre>

### Using defer

<pre>
char *buf = malloc(64);
defer(cleanup_free, buf);

FILE *f = fopen("file.txt", "w");
defer(cleanup_fclose, f);
</pre>

The cleanup functions are called automatically when the scope exits.

---

## Example

From `demo.c`:

<pre>
FILE *f = fopen("test.txt", "w");
if (!f) return 1;
defer(cleanup_fclose, f);

char *buf = malloc(64);
if (!buf) return 1;
defer(cleanup_free, buf);

puts("doing work");
</pre>

Even with an early return, both resources are released correctly.

---

## Build & Run

<pre>
gcc -std=c99 -Wall -Wextra demo.c -o demo
./demo
</pre>

Expected output:

<pre>
program start
doing work
buffer freed
file closed
</pre>

---

## Notes

* No heap allocation inside `defer`
* No macro control-flow tricks
* Predictable and debuggable behavior
* Suitable for real-world Linux C projects

For maximum portability or strict ISO C compliance, consider traditional
`goto cleanup` patterns instead.
