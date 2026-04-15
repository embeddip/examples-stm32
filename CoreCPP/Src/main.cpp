#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {

  embedDIP::Image inImg(IMAGE_RES_QQVGA, IMAGE_FORMAT_RGB888);
  embedDIP::Image compressedImg(IMAGE_RES_QQVGA, IMAGE_FORMAT_RGB888);

  embedDIP::Camera camera(&stm32_ov5640);
  embedDIP::Serial serial(&stm32_uart);

  camera.init(IMAGE_RES_QQVGA, IMAGE_FORMAT_RGB888);

  while (1) {
    camera.capture(SINGLE, inImg);
    compress(inImg.raw(), compressedImg.raw(), IMAGE_COMP_JPEG, 75);
    serial.sendJPEG(compressedImg);
    camera.stop();
  }
}
