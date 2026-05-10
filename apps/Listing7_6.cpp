#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image outImg_1(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image outImg_2(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  vector<uint8_t> breakpoints1 = {0, 128, 255};
  vector<uint8_t> values1 = {0, 32, 255};

  serial.capture(inImg);

  inImg.piecewiseTransform(outImg_1, breakpoints1, values1);
  outImg_1.convertTo();
  serial.send(outImg_1);

  vector<uint8_t> breakpoints2 = {0, 128, 255};
  vector<uint8_t> values2 = {0, 200, 255};

  inImg.piecewiseTransform(outImg_2, breakpoints2, values2);
  outImg_2.convertTo();
  serial.send(outImg_2);

  while (1);
}