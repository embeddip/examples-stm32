#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);

  embedDIP::Serial serial(&stm32_uart);
  embedDIP::Display display(&stm32_ota5180a);

  serial.init();
  display.init();

  serial.capture(inImg);
  display.show(inImg);

  while (1);
}