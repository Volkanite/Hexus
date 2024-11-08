#define MAX_JMP_SZ 14
#define NOP 0x90 // opcode for NOP
#define JMP 0xE9 // opcode for JUMP

//static const size_t relativeJmpSize = 1 + sizeof(DWORD);
//static const size_t absoluteJmpSize = 2 + sizeof(DWORD)+sizeof(DWORD_PTR);
#define relativeJmpSize 5 // the size of JMP <address>
#define absoluteJmpSize 14 // the size of JMP <address>
typedef enum AddressingMode
{
    Relative = relativeJmpSize,
    Absolute = absoluteJmpSize
}AddressingMode;
#if !defined(_M_AMD64) && !defined(_M_IX86)
#error "_M_AMD64 or _M_IX86 must be defined"
#endif

#ifdef _M_IX86
#include "./hde/hde32.h"
typedef hde32s HDE;
#define HDE_DISASM(code, hs) hde32_disasm(code, hs)
#else
#include "./hde/hde64.h"
typedef hde64s HDE;
#define HDE_DISASM(code, hs) hde64_disasm(code, hs)
#endif


typedef struct DETOUR_PROPERTIES
{
    LPVOID Origin;
    LPVOID Trampoline;
    size_t Length;
}DETOUR_PROPERTIES;


#ifdef __cplusplus
extern "C" {
#endif

void* DetourCreate(LPVOID lpFuncOrig, LPVOID lpFuncDetour, DETOUR_PROPERTIES *Properties);
BOOL DetourDestroy(DETOUR_PROPERTIES* Properties);

#ifdef __cplusplus
}
#endif
