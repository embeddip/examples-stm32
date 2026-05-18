#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image maskImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_MASK);
  embedDIP::Image outImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  serial.capture(inImg);

  Rectangle roi;
  roi.x = 30;
  roi.y = 55;
  roi.width = 400;
  roi.height = 200;

  // tic();
  // inImg.grabCutLite(maskImg, roi, 5);
  inImg.grabCut(maskImg, roi, 5);
  // uint32_t cycleCount = toc();

  maskImg.convertTo();
  serial.send(maskImg);

  inImg._and_(maskImg, outImg);
  serial.send(outImg);

  while (1);
}
