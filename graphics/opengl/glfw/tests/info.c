#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  printf("Compiled against GLFW %i.%i.%i\n",
	 GLFW_VERSION_MAJOR,
	 GLFW_VERSION_MINOR,
	 GLFW_VERSION_REVISION);

  int major, minor, revision;
  glfwGetVersion(&major, &minor, &revision);
  printf("Running against GLFW %i.%i.%i\n", major, minor, revision);
}
