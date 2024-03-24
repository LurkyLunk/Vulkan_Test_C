
SOURCES = main.c compute.c device.c instance.c pipeline.c memory.c
HEADERS = compute.h device.h instance.h pipeline.h memory.h

TARGET = vulkan_compute

SHADER_SRC = shader.comp
SHADER_BIN = comp.spv

$(TARGET): $(SOURCES) $(HEADERS) $(SHADER_BIN)
	gcc -g -O0 $(SOURCES) -lvulkan -o $(TARGET)

$(SHADER_BIN): $(SHADER_SRC)
	glslangValidator -V $(SHADER_SRC) -o $(SHADER_BIN)

