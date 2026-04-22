#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application() {
  embedDIP::Image inImg(256, 256, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image outImg(256, 256, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Image TabbyCatMagnitude(256, 256, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image TabbyCatPhase(256, 256, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Image KittenImage(256, 256, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image KittenPhase(256, 256, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);

  serial.init();

// Get Kitten + fft
  serial.capture(inImg);
  inImg.fft(inImg);
  inImg._abs_(TabbyCatMagnitude);
  inImg._phase_(TabbyCatPhase);

// Get TabbyCat + fft
  serial.capture(inImg);
  inImg.fft(inImg);
  inImg._abs_(KittenImage);
  inImg._phase_(KittenPhase);

// TabbyCat's magnitude with Kitten's phase
  outImg.polarToCart(TabbyCatMagnitude, KittenPhase);
  outImg.ifft(outImg);
  outImg.convertTo();
  serial.send(outImg);

// Kitten's magnitude with TabbyCat's phase
  outImg.polarToCart(KittenImage, TabbyCatPhase);
  outImg.ifft(outImg);
  outImg.convertTo();
  serial.send(outImg);

  while (1) {
    ;
  }
}
