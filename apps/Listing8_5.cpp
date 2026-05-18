#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(256, 256, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image outImg(256, 256, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Image magnitudeImg(256, 256, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image phaseImg(256, 256, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  serial.capture(inImg);
  inImg.fft(inImg);
  inImg.fftshift();
  inImg._abs_(magnitudeImg);
  inImg._phase_(phaseImg);

  outImg.polarToCart(magnitudeImg, phaseImg);
  outImg.fftshift();
  outImg.ifft(outImg);
  outImg.convertTo();
  serial.send(outImg);

  while (1);
}
