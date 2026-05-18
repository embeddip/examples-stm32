#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {

  embedDIP::Image inImg(IMAGE_RES_QQVGA, IMAGE_FORMAT_RGB888);
  embedDIP::Image compressedImg(IMAGE_RES_QQVGA, IMAGE_FORMAT_RGB888);

  embedDIP::Camera camera(&stm32_ov5640);
  embedDIP::Serial serial(&stm32_uart);

  camera.init(IMAGE_RES_QQVGA, IMAGE_FORMAT_RGB888);
  serial.init();

  while (1) {
    camera.capture(SINGLE, inImg);
    inImg.compressJPEG(compressedImg, 75);
    serial.sendJPEG(compressedImg);
    camera.stop();
  }
}
