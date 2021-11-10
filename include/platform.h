#ifndef PLATFORM_HEADER
#define PLATFORM_HEADER

#if defined(_WIN64) || defined(_WIN32)
#define WINDOWS_OS
#elif defined(__linux__)
#define LINUX_OS
#endif

#if defined(__x86_64__) || defined(_M_AMD64)
#define CPU_64_BITS
#define BOOL_CPU_32_BITS (0)
#elif defined(__i368__) || defined(_X86_) || defined(_M_IX86)
#define CPU_32_BITS 
#define BOOL_CPU_32_BITS (1)
#endif

#endif
