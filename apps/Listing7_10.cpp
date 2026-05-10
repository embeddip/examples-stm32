#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Serial serial(&stm32_uart);

  serial.init();

  for (int img_idx = 0; img_idx < 4; ++img_idx) {
    serial.capture(inImg);
    vector<int> histogram(256, 0);

    inImg.histForm(histogram);
    serial.send1D(histogram.data(), sizeof(int), 256, SERIAL_DATA_HISTOGRAM);
  }

  while (1);
}
