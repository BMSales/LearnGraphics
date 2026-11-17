#include <iostream>

#include "include/app.h"

int main(){
  App app;

  if(!app.Initiate()){
    std::cout << "Failed initiating application" << std::endl;
    return -1;
  };
  app.Run();
  app.Destroy();

  return 0;
}
