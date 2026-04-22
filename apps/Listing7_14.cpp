#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image srcImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image refImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image outImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  serial.capture(refImg);

  vector<int> referenceHist(256, 0);
  refImg.histForm(referenceHist);

  serial.capture(srcImg);

  srcImg.histSpec(outImg, referenceHist);
  outImg.convertTo();

  serial.send(outImg);

  while (1) {
    ;
  }
}
