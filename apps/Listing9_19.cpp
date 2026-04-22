#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image gX(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image gY(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image magnitudeOut(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image phaseOut(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  serial.capture(inImg);

  inImg.gaussianGradients(gX, gY, 1.2f);

  gX.convertTo();
  serial.send(gX);
  gY.convertTo();
  serial.send(gY);

  magnitudeOut.gradientMagnitude(gX, gY);
  magnitudeOut.convertTo();
  serial.send(magnitudeOut);

  phaseOut.gradientPhase(gX, gY);
  phaseOut.convertTo();
  serial.send(phaseOut);

  while (1) {
    ;
  }
}
