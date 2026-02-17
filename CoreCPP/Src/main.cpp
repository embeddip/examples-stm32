#include "main.h"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image maskImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Image outImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  serial.capture(inImg);

  Rectangle roi;
  roi.x = 87;
  roi.y = 43;
  roi.width = 350;
  roi.height = 180;

  // tic();

  inImg.grabCutLite(maskImg, roi, 10);
  // inImg.grabCut(maskImg, roi, 1);

  // uint32_t cycleCount = toc();

  maskImg.convertTo();
  serial.send(maskImg);

  maskImg.multiply(inImg, outImg);
  outImg.convertTo();
  serial.send(outImg);

  while (1) {
    ;
  }
}