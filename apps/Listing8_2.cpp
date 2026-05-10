#include "main.h"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(256, 256, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image fftImg(256, 256, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Image magnitudeImg(256, 256, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image phaseImg(256, 256, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();
  serial.capture(inImg);

  inImg.fft(fftImg);
  fftImg.fftshift();

  fftImg._abs_(magnitudeImg);
  fftImg._phase_(phaseImg);

  magnitudeImg._add_(1.0f);
  magnitudeImg._log_();

  magnitudeImg.convertTo();
  serial.send(magnitudeImg);

  phaseImg.convertTo();
  serial.send(phaseImg);

  while (1);
}
