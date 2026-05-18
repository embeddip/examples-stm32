#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image wqvgaImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
  embedDIP::Image qqvgaImg(IMAGE_RES_QQVGA, IMAGE_FORMAT_RGB565);

  embedDIP::Camera camera(&stm32_ov5640);
  embedDIP::Serial serial(&stm32_uart);

  camera.init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
  serial.init();

  camera.capture(SINGLE, wqvgaImg);
  serial.send(wqvgaImg);

  camera.stop();
  camera.setRes(IMAGE_RES_QQVGA);
  camera.capture(SINGLE, qqvgaImg);
  serial.send(qqvgaImg);

  while (1);
}
