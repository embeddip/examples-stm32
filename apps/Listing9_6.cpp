#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_HSI);

  embedDIP::Image mask(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Image outImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_HSI);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  serial.capture(inImg);

  uint8_t lower[3] = {0, 0, 0};
  uint8_t upper[3] = {26, 255, 255};

  inImg.inRange(mask, lower, upper);

  serial.send(mask);

  // Optional
  inImg._and_(mask, outImg);

  serial.send(outImg);

  while (1);
}
