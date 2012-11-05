#include <stdint.h>

#define cimg_display 0
#include "CImg.h"
using namespace cimg_library;

typedef CImg<uint16_t> Image;

extern "C" {
#include "blur_0.h"
#include "blur_1.h"
#include "blur_2.h"
#include "blur_3.h"
#include "blur_4.h"
#include "blur_5.h"
#include "blur_6.h"
#include "blur_7.h"
#include "blur_8.h"
#include "blur_9.h"
#include "blur_10.h"
#include "blur_11.h"
}

// Convert a CIMG image to a buffer_t for halide
buffer_t halideBufferOfImage(Image &im) {
    buffer_t buf = {(uint8_t *)im.data(), 0, false, false, 
                    {im.width(), im.height(), 1, 1}, 
                    {1, im.width(), 0, 0}, 
                    {0, 0, 0, 0}, 
                    sizeof(int16_t)};
    return buf;
}

void make_log(int schedule) {
    Image input(32, 32);
    Image out(32, 32);
    buffer_t inbuf = halideBufferOfImage(input);
    buffer_t outbuf = halideBufferOfImage(out);

    switch(schedule) {
    case 0:
      blur_6(&inbuf, &outbuf);
      blur_6(&inbuf, &outbuf);
      blur_6(&inbuf, &outbuf);
      blur_0(&inbuf, &outbuf);
      return;
    case 1:
      blur_7(&inbuf, &outbuf);
      blur_7(&inbuf, &outbuf);
      blur_7(&inbuf, &outbuf);
      blur_1(&inbuf, &outbuf);
      return;
    case 2:
      blur_8(&inbuf, &outbuf);
      blur_8(&inbuf, &outbuf);
      blur_8(&inbuf, &outbuf);
      blur_2(&inbuf, &outbuf);
      return;
    case 3:
      blur_9(&inbuf, &outbuf);
      blur_9(&inbuf, &outbuf);
      blur_9(&inbuf, &outbuf);
      blur_3(&inbuf, &outbuf);
      return;
    case 4:
      blur_10(&inbuf, &outbuf);
      blur_10(&inbuf, &outbuf);
      blur_10(&inbuf, &outbuf);
      blur_4(&inbuf, &outbuf);
      return;
    case 5:
      blur_11(&inbuf, &outbuf);
      blur_11(&inbuf, &outbuf);
      blur_11(&inbuf, &outbuf);
      blur_5(&inbuf, &outbuf);
      return;
    }
}

int main(int argc, char **argv) {
    make_log(atoi(argv[1]));
    return 0;
}