#include "main.h"
#include <embedDIP.hpp>
#include <image_data_rgb.h>

using namespace std;

int application()
{
    embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
    embedDIP::Image outImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

    embedDIP::Serial serial(&stm32_uart);

    embedDIP::Display display(&stm32_ota5180a);

    embedDIP::Camera camera(&stm32_ov5640);

    serial.init();
    display.init();

    serial.capture(inImg);
    camera.init(IMAGE_RES_WQVGA);
    camera.capture(CONTINUOUS, inImg);

    // inImg.logFilter(outImg, 1.0f);

    // outImg.convertTo();

    serial.send(inImg);
    display.show(inImg);

    while (1)
    {
        ;
    }
}