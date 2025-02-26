#define expect(expected, actual)                                               \
    if (actual != expected) {                                                  \
        fprintf(stderr,                                                        \
                "X Expected %lld, but got: %lld. File:Line | %s:%d.\n",        \
                expected, actual, __FILE__, __LINE__);                         \
        return 0;                                                              \
    }

#define expectNot(expected, actual)                                            \
    if (actual == expected) {                                                  \
        fprintf(                                                               \
            stderr,                                                            \
            "X Expected %d != %d, but they are equal. File:Line | %s:%d.\n",   \
            expected, actual, __FILE__, __LINE__);                             \
        return 0;                                                              \
    }

#define expectTrue(actual)                                                     \
    if (actual != 1) {                                                         \
        fprintf(stderr,                                                        \
                "X Expected true, but got: false. File:Line | %s:%d.\n",       \
                __FILE__, __LINE__);                                           \
        return 0;                                                              \
    }

#define expectFalse(actual)                                                    \
    if (actual != 0) {                                                         \
        fprintf(stderr,                                                        \
                "X Expected false, but got: true. File:Line | %s:%d.\n",       \
                __FILE__, __LINE__);                                           \
        return 0;                                                              \
    }
