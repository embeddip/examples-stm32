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
  embedDIP::Image sH(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image sV(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  serial.capture(inImg);

  inImg.filter2D(SOBEL_X_3x3, sH);
  inImg.filter2D(SOBEL_Y_3x3, sV);

  sH.convertTo();
  serial.send(sH);

  sV.convertTo();
  serial.send(sV);

  outImg.gradientMagnitude(sH, sV);

  outImg.convertTo();
  serial.send(outImg);

  while (1);
}
