#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application()
{
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image gH(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image gV(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image magnitudeOut(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image phaseOut(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  serial.capture(inImg);

  inImg.gaussianGradients(gH, gV, 1.2f);

  gH.convertTo();
  serial.send(gH);
  gV.convertTo();
  serial.send(gV);

  magnitudeOut.gradientMagnitude(gH, gV);
  magnitudeOut.convertTo();
  serial.send(magnitudeOut);

  phaseOut.gradientPhase(gH, gV);
  phaseOut.convertTo();
  serial.send(phaseOut);

  while (1);
}
