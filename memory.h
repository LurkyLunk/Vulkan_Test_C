#include <vulkan/vulkan.h>

void CreateBuffers(uint32_t inputSize, uint32_t outputSize,
                        uint32_t inputSizeUni1, uint32_t inputSizeUni2);
void DestroyBuffers(void);

void CopyToInputBuffer(void *data, uint32_t size);
void CopyFromOutputBuffer(void *data, uint32_t size);
void CopyToOutputBuffer(void *data, uint32_t size);
void CopyToInputBufferUni1(void *data, uint32_t size);
void CopyToInputBufferUni2(void *data, uint32_t size);
