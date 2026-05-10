#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(256, 256, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image outImg(256, 256, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image filterImg(256, 256, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  serial.capture(inImg);
  inImg.fft(inImg);
  inImg.fftshift();

  filterImg.getFilter(FREQ_FILTER_GAUSSIAN_BANDPASS, 10.0f, 60.0f);
  inImg.ffilter2D(filterImg, outImg);

  outImg.fftshift();
  outImg.ifft(outImg);
  outImg.convertTo();
  serial.send(outImg);

  while (1);
}
