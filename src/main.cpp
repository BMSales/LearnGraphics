#include <SDL.h>
#include <iostream>

#include "include/app.h"

int main(){
  App app;

  app.Initiate();
  app.Run();
  app.Destroy();

  return 0;
}
