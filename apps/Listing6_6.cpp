#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image wqvgaImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
  embedDIP::Image inImg_qvga(IMAGE_RES_QVGA, IMAGE_FORMAT_RGB565);

  embedDIP::Display display(&stm32_ota5180a);
  embedDIP::Camera camera(&stm32_ov5640);

  display.init();
  camera.init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);

  camera.capture(SINGLE, wqvgaImg);
  display.show(wqvgaImg);
  HAL_Delay(1000);
  camera.stop();

  camera.setRes(IMAGE_RES_QVGA);
  camera.capture(SINGLE, inImg_qvga);
  display.show(inImg_qvga);

  while (1);
}