#ifndef COSMOPOLITAN_LIBC_NT_STRUCT_IMAGERESOURCEDATAENTRY_H_
#define COSMOPOLITAN_LIBC_NT_STRUCT_IMAGERESOURCEDATAENTRY_H_
#if !(__ASSEMBLER__ + __LINKER__ + 0)

struct NtImageResourceDataEntry {
  uint32_t OffsetToData;
  uint32_t Size;
  uint32_t CodePage;
  uint32_t Reserved;
};

#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_NT_STRUCT_IMAGERESOURCEDATAENTRY_H_ */
