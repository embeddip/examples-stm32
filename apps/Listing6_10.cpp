#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);

  embedDIP::Display display(&stm32_ota5180a);
  embedDIP::Camera camera(&stm32_ov5640);

  display.init();
  camera.init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);

  camera.capture(CONTINUOUS, inImg);
  display.show(inImg);

  while (1) {
    ;
  }
}