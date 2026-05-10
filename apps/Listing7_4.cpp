#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image outImg_1(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image outImg_2(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  serial.capture(inImg);

  inImg.powerTransform(outImg_1, 2.0f);
  outImg_1.convertTo();
  serial.send(outImg_1);

  inImg.powerTransform(outImg_2, 1.0f / 2.0f);
  outImg_2.convertTo();
  serial.send(outImg_2);

  while (1);
}
