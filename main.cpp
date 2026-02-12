#include <webgpu/webgpu.h>
#include <iostream>

int main() {
    WGPUInstanceDescriptor descriptor {};
    descriptor.nextInChain = nullptr;

#ifdef WEBGPU_BACKEND_EMSCRIPTEN
    WGPUInstance instance = wgpuCreateInstance(nullptr);
#else //  WEBGPU_BACKEND_EMSCRIPTEN
    WGPUInstance instance = wgpuCreateInstance(&descriptor);
#endif //  WEBGPU_BACKEND_EMSCRIPTEN

    if (!instance) {
        std::cerr << "Failed to create WGPU instance" << std::endl;
        return 1;
    }

    std::cout << "WGPU instance: " << instance << std::endl;


    wgpuInstanceRelease(instance);

    return 0;
}