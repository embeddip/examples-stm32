#include "main.h"
#include <embedDIP.hpp>

int application()
{
    embedDIP::Image inputImage(256, 256, IMAGE_FORMAT_GRAYSCALE);
    embedDIP::Image outputImage(256, 256, IMAGE_FORMAT_GRAYSCALE);
    embedDIP::Image filterMask(256, 256, IMAGE_FORMAT_GRAYSCALE);

    if (!inputImage.isValid() || !outputImage.isValid() || !filterMask.isValid()) {
        Error_Handler();
    }

    embedDIP::Serial serial(&stm32_uart);
    serial.init();
    serial.flush();

    serial.capture(inputImage);

    inputImage.fft(inputImage);
    inputImage.fftshift();

    filterMask.getFilter(FREQ_FILTER_IDEAL_HIGHPASS, 30.0f);
    inputImage.ffilter2D(filterMask, outputImage);

    outputImage.ifftshift();
    outputImage.ifft(outputImage);
    outputImage.convertTo();

    serial.send(outputImage);

    while (1) {
        __NOP();
    }

    return 0;
}
