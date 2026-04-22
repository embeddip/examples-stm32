#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image cameraImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
  embedDIP::Image serialImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);

  embedDIP::Serial serial(&stm32_uart);
  embedDIP::Display display(&stm32_ota5180a);
  embedDIP::Camera camera(&stm32_ov5640);

  serial.init();
  display.init();
  camera.init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);

  camera.capture(SINGLE, cameraImg);
  display.show(cameraImg);
  HAL_Delay(1000);
  serial.capture(serialImg);
  display.show(serialImg);

  while (1) {
    ;
  }
}