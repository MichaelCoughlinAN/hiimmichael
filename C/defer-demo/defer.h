#ifndef DEFER_H
#define DEFER_H

/*
  defer.h — scope-exit cleanup for C using GCC/Clang

  This relies on __attribute__((cleanup)), which is
  widely supported on Linux systems.

  Cleanup function signature:
    void cleanup(void *p);

  Example:
    defer(cleanup_free, ptr);
*/

#define DEFER_CONCAT(a, b) a##b
#define DEFER_MAKE_UNIQUE(a, b) DEFER_CONCAT(a, b)

#define defer(func, var) \
    __attribute__((cleanup(func))) \
    void *DEFER_MAKE_UNIQUE(_defer_var_, __LINE__) = (void *)(var)

#endif /* DEFER_H */
