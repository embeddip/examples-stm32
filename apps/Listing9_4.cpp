#include "main.h"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image outImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  serial.capture(inImg);

  inImg.grayscaleOtsu(outImg);

  serial.send(outImg);

  while (1);
}
