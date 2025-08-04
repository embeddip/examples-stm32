#include "main.h"
#include <embedDIP.hpp>

using namespace std;

int application()
{
    embedDIP::Image rgbImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888);
    embedDIP::Image rgb565Img(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
    embedDIP::Image grayImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

    embedDIP::Serial serial(&stm32_uart);
    serial.init();

    serial.capture(rgbImg);

    rgbImg.cvtColor(rgb565Img, CVT_RGB888_TO_RGB565);
    serial.send(rgb565Img);

    rgbImg.cvtColor(grayImg, CVT_RGB888_TO_GRAYSCALE);
    serial.send(grayImg);

    while (1)
    {
        ;
    }
}