#include "main.hpp"
#include <embedDIP.hpp>
#include <image_data.h>

using namespace std;

int application() {

  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
  embedDIP::Serial serial(&stm32_uart);
  serial.init();

  memcpy(inImg.pixels(), image_data, inImg.size() * inImg.depth());

  serial.send(inImg);

  while (1) {
    ;
  }
}
