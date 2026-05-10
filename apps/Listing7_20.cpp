#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image outImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  vector<float> lowPassFilter3x3(3, 1);

  serial.capture(inImg);

  inImg.sepFilter2D(outImg, lowPassFilter3x3, lowPassFilter3x3, 1.0 / 9.0);
  outImg.convertTo();
  serial.send(outImg);

  while (1);
}
