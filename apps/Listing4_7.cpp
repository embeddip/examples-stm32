#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

int application()
{
    embedDIP::Image rgbImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888);
    embedDIP::Image rgb565Img(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
    embedDIP::Image rgbRoundTripImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888);
    embedDIP::Image grayOrig(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
    embedDIP::Image grayRoundTrip(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
    embedDIP::Image diffImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

    embedDIP::Serial serial(&stm32_uart);
    serial.init();

    serial.capture(rgbImg);

    rgbImg.cvtColor(rgb565Img, CVT_RGB888_TO_RGB565);
    rgb565Img.cvtColor(rgbRoundTripImg, CVT_RGB565_TO_RGB888);

    rgbImg.cvtColor(grayOrig, CVT_RGB888_TO_GRAYSCALE);
    rgbRoundTripImg.cvtColor(grayRoundTrip, CVT_RGB888_TO_GRAYSCALE);
    grayOrig.difference(grayRoundTrip, diffImg);
    diffImg.convertTo();
    serial.send(diffImg);

    while (1);
}
