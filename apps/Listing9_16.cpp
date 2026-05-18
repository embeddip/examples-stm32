#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888);
  embedDIP::Image outImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  serial.capture(inImg);

  embedDIP::Point seeds[1] = {{150, 150}};
  inImg.colorRegionGrowing(outImg, seeds, 1, 0.20f);
  serial.send(outImg);

  embedDIP::Point seeds2[1] = {{310, 90}};
  inImg.colorRegionGrowing(outImg, seeds2, 1, 0.20f);
  serial.send(outImg);

  embedDIP::Point seeds3[2] = {{150, 150}, {310, 90}};
  inImg.colorRegionGrowing(outImg, seeds3, 2, 0.30);
  serial.send(outImg);

  while (1);
}
