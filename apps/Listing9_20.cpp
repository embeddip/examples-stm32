#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

static const std::vector<std::vector<float>> SOBEL_X_3x3 = {
    {-1.f, 0.f, 1.f}, {-2.f, 0.f, 2.f}, {-1.f, 0.f, 1.f}};

static const std::vector<std::vector<float>> SOBEL_Y_3x3 = {
    {1.f, 2.f, 1.f}, {0.f, 0.f, 0.f}, {-1.f, -2.f, -1.f}};

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image outImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image sX(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image sY(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  serial.capture(inImg);

  inImg.filter2D(SOBEL_X_3x3, sX);
  inImg.filter2D(SOBEL_Y_3x3, sY);

  sX.convertTo();
  serial.send(sX);

  sY.convertTo();
  serial.send(sY);

  outImg.gradientMagnitude(sX, sY);

  outImg.convertTo();
  serial.send(outImg);

  while (1) {
    ;
  }
}
