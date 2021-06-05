CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

VulkanTriangle: main.cpp
	g++ $(CFLAGS) -o VulkanTriangle main.cpp HelloTriangleApplication.cpp $(LDFLAGS)

.PHONY: triangle clean

triangle: VulkanTriangle
	./VulkanTriangle

clean:
	rm -f VulkanTriangle