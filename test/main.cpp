#include <iostream>
#include <string>
#include <dlfcn.h>

typedef void (*func_t)(char *output, int outputSize, const char *function);

int main()
{
  void *shared_object = dlopen("./iniDB.so", RTLD_LAZY);
  func_t func = (func_t)dlsym(shared_object, "RVExtension");
  char *output = new char[1024];

  std::cout << "Hello World!" << std::endl;

  func(output, 1024, "version");
  std::cout << output << std::endl;

  func(output, 1024, "read;A3W_76561197999882926;PlayerSave;AssignedItems");

  std::cout << output << std::endl;

  return 0;
}
