#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image outImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  serial.capture(inImg);

  embedDIP::Point seeds[] = {{150, 150}, {310, 90}};
  int numSeeds = sizeof(seeds) / sizeof(seeds[0]);

  inImg.grayscaleRegionGrowing(outImg, seeds, numSeeds, 30);

  serial.send(outImg);

  while (1);
}
