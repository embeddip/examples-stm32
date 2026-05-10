#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888);
  embedDIP::Image outImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  serial.capture(inImg);

  inImg.colorKMeans(outImg, 3);
  // inImg.colorKMeans(outImg, 5);

  serial.send(outImg);

  while (1);
}
