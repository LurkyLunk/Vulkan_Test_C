#include "compute.h"
#include "instance.h"
#include "device.h"
#include "pipeline.h"
#include "memory.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

uint32_t InputData[2][10000];
uint32_t OutputData[1];

void generate(void)
{
    uint32_t maxValue = 0;
    for (uint32_t i = 0; i < 10000; i++)
    {
        for (uint32_t j = 0; j < 10000; j++)
        {
            uint32_t value = InputData[0][i] * InputData[1][j];
            if (value > maxValue) maxValue = value;
        }
    }
    OutputData[0] = maxValue;
}

uint32_t get_time(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}

int main(int ac, char **av)
{
    CreateInstance();
    GetPhysicalDevice();
    CreateDeviceAndComputeQueue();
    CreatePipeline();
    CreateDescriptorSet();
    CreateBuffers(sizeof(InputData), sizeof(OutputData), sizeof(InputData[0]), sizeof(InputData[1]));
    CreateCommandPool();
    PrepareCommandBuffer();

    for (uint32_t i = 0; i < 10000; i++)
    {
        InputData[0][i] = rand() % 1000;
        InputData[1][i] = rand() % 1000;
    }

    CopyToInputBuffer(InputData, sizeof(InputData));
    CopyToInputBufferUni1(InputData[0], sizeof(InputData[0]));
    CopyToInputBufferUni2(InputData[1], sizeof(InputData[1]));

    uint32_t time = get_time();
    generate();
    time = get_time() - time;
    printf("CPU time %u, value = %u\n", time, OutputData[0]);

    time = get_time();
    Compute();
    time = get_time() - time;

    CopyFromOutputBuffer(OutputData, sizeof(OutputData));
    printf("GPU time %u, value = %u\n", time, OutputData[0]);

    DestroyPipeline();
    DestroyCommandPoolAndLogicalDevice();

    return 0;
}
