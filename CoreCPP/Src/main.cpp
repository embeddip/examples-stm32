#include "main.h"

#include "libjpeg.h"
#include <embedDIP.hpp>
#include <image_data.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int mainCPP()
{
    memory_init();

    embedDIP::Image yuvImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_YUV);
    embedDIP::Image grayImg(256, 256, IMAGE_FORMAT_GRAYSCALE);
    embedDIP::Image magnitude(256, 256, IMAGE_FORMAT_GRAYSCALE);

    embedDIP::Serial serial(&stm32_uart);

    serial.init();

    serial.capture(yuvImg);
    yuvImg.cvtColor(grayImg, );
    serial.send(inImg);


    /*
    inImg.fft(fftImg);
    fftImg.fftshift();

    fftImg._abs(magnitude);

    filter.getFilter(FREQ_FILTER_GAUSSIAN_LOWPASS, 40.0f, 0.0f);

    magnitude.multiply(filter, output);

    output._add(1);
    output._log();

    output.convertTo();
    serial.send(output);
    */

    while (1)
    {
        ;
    }
}