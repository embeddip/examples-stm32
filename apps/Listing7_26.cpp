#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888);
  embedDIP::Image outImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888);

  embedDIP::Image rImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image gImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image bImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Image rOutImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image gOutImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image bOutImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  vector<vector<float>> lowPassFilter3x3(3, vector<float>(3, 1.0f / 9.0f));

  serial.init();

  serial.capture(inImg);

  inImg.rgbSplit(rImg, gImg, bImg);

  rImg.filter2D(lowPassFilter3x3, rOutImg);
  gImg.filter2D(lowPassFilter3x3, gOutImg);
  bImg.filter2D(lowPassFilter3x3, bOutImg);

  rOutImg.convertTo();
  gOutImg.convertTo();
  bOutImg.convertTo();

  outImg.rgbMerge(rOutImg, gOutImg, bOutImg);

  serial.send(outImg);
  while (1);
}
