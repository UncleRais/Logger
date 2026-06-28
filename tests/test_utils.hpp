// Custom macro to track file and line numbers on failure
#define IS_TRUE(expression) \
    if (!(expression)) { \
        std::cout << "FAIL: " << #expression << " in " << __FILE__ << " line " << __LINE__ << std::endl; \
        failed_tests++; \
    } else { \
        passed_tests++; \
    }

// Global counters for test tracking
inline int passed_tests = 0;
inline int failed_tests = 0;
