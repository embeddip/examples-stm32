#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image outImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  embedDIP::Kernel k;

  serial.init();
  serial.capture(inImg);

  inImg.grayscaleThreshold(inImg, 80);

  k.getStructuringElement(MORPH_ELLIPSE, 3);

  inImg.erode(outImg, k, 1);
  outImg.negative(outImg);
  serial.send(outImg);

  inImg.erode(outImg, k, 2);
  outImg.negative(outImg);
  serial.send(outImg);

  inImg.erode(outImg, k, 3);
  outImg.negative(outImg);
  serial.send(outImg);

  while (1);
}
