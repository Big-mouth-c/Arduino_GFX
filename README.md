# Arduino_GFX

Arduino_GFX is a Arduino graphics library supporting various displays with various data bus interfaces.

This library start rewrite from Adafruit_GFX, LovyanGFX, TFT_eSPI, Ucglib, and more...

![GitHub release (latest by date)](https://img.shields.io/github/v/release/moononournation/Arduino_GFX)
![GitHub Release Date](https://img.shields.io/github/release-date/moononournation/Arduino_GFX)
![GitHub commits since latest release (by date)](https://img.shields.io/github/commits-since/moononournation/Arduino_GFX/latest)
![GitHub last commit](https://img.shields.io/github/last-commit/moononournation/Arduino_GFX)

![GitHub Sponsors](https://img.shields.io/github/sponsors/moononournation)
![Twitter Follow](https://img.shields.io/twitter/follow/moononournation)

## Ease of use

### Simple Declaration

```C
#include <Arduino_GFX_Library.h>
Arduino_DataBus *bus = new Arduino_HWSPI(16 /* DC */, 5 /* CS */);
Arduino_GFX *gfx = new Arduino_ILI9341(bus, 17 /* RST */);
```

### And Simple Usage

```C
gfx->begin();
gfx->fillScreen(RGB565_BLACK);
gfx->setCursor(10, 10);
gfx->setTextColor(RGB565_RED);
gfx->println("Hello World!");
```

## Get Started

If you are new on this library, I always recommend try Library Example PDQgraphicstest first. You can find it at Arduino IDE -> File menu -> Examples -> GFX Library for Arduino -> PDQgraphicstest.

After open the example, you can see many tabs. The first is PDQgraphicstest, the main program. Start from the second tab, it is related header files, Arduino_GFX_databus.h, ... etc.

### Using supported Dev Device

If you are using below listed support dev device, simply select the Arduino_GFX_dev_device.h and uncomment the define of your dev device. E.g. if you are using LilyGo T-Deck:

```C
...
// #define JC3248W535
#define LILYGO_T_DECK
// #define LILYGO_T_DISPLAY
...
```

### Custom device and display

If you are not using supported dev device:

- Default DataBus is using Arduino SPI. Other DataBus can modify in Arduino_GFX_databus.h.

- Default Display is using ILI9341 LCD. Other Display can modify in Arduino_GFX_display.h.

## More Details

<details>

<summary>U8g2 Font Support</summary>

[U8g2](https://github.com/olikraus/u8g2.git) provided various font type and stored in compressed format. So U8g2 font gives more UI design possibilities and still can fit in the MCU limited storage space. Using U8g2 font in Arduino_GFX simply include U8g2lib.h before Arduino_GFX_Library.h:

```C
#include <U8g2lib.h>
#include <Arduino_GFX_Library.h>
```

And then setfont file to use:

```C
gfx->setCursor(10, 20);
gfx->setFont(u8g2_font_maniac_tr);
gfx->println("Hello World!");
```

U8g2 font list can be found at: <https://github.com/olikraus/u8g2/wiki/fntlistall>

### U8g2 Unicode (UTF8) Font Support

Another U8g2 font advantage is the font support Unicode glyphs. Simply enable setUTF8Print:

```C
gfx->begin();
gfx->fillScreen(RGB565_BLACK);
gfx->setUTF8Print(true);
```

And then print UTF8 string as usual:

```C
gfx->setCursor(0, 16);

gfx->setFont(u8g2_font_unifont_tr);
gfx->println("Hello World!");

gfx->setFont(u8g2_font_unifont_t_polish);
gfx->println("Witaj świecie!");

gfx->setFont(u8g2_font_unifont_t_vietnamese1);
gfx->println("Chào thế giới!");

gfx->setFont(u8g2_font_unifont_t_chinese2);
gfx->println("世界你好!");

gfx->setFont(u8g2_font_unifont_t_japanese1);
gfx->println("こんにちは世界!");

gfx->setFont(u8g2_font_unifont_t_korean1);
gfx->println("안녕하세요, 세계입니다!");
```

U8g2 Unifont list can be found at: <https://github.com/olikraus/u8g2/wiki/fntgrpunifont>

### Extra Fonts

Besides U8g2 generated font, Arduino_GFX also generated some useful font set:

#### [Chill-Bitmap v2.400](https://github.com/Warren2060/Chill-Bitmap)

##### u8g2_font_chill7_h_cjk

- Glyphs: 13478/13478
- Size: 254,960
- Generation script:

```console
otf2bdf ChillBitmap7x.ttf -p 6 -o ChillBitmap7x.bdf
bdfconv -v -f 1 -b 1 -m "0-4294967295" ChillBitmap7x.bdf -o u8g2_font_chill7_h_cjk.h -n u8g2_font_chill7_h_cjk
```

#### [Cubic 11 v1.013](https://github.com/ACh-K/Cubic-11)

##### u8g2_font_cubic11_h_cjk

- Glyphs: 10167/10167
- Size: 337,650
- Generation script:

```console
otf2bdf Cubic_11_1.013_R.ttf -p 9 -o Cubic_11_1.013_R.bdf
bdfconv -v -f 1 -b 1 -m "0-4294967295" Cubic_11_1.013_R.bdf -o u8g2_font_cubic11_h_cjk.h -n u8g2_font_cubic11_h_cjk
```

#### [QuanPixel](https://diaowinner.itch.io/galmuri-extended)

##### u8g2_font_quan7_h_cjk

- Glyphs: 18082/18082
- Size: 335,225
- Generation script:

```console
./bdfconv -v -f 1 -b 1 -m "0-4294967295" quan.bdf -o u8g2_font_quan7_h_cjk.h -n u8g2_font_quan7_h_cjk
```

#### [unifont_jp-14.0.02](http://unifoundry.com/pub/unifont/unifont-14.0.02/font-builds/unifont_jp-14.0.02.bdf.gz)

##### u8g2_font_unifont_h_utf8

- Glyphs: 57389/57389
- Size: 2,250,360
- Generation script:

```console
bdfconv -v -f 1 -b 1 -m "0-1114111" unifont_jp-14.0.02.bdf -o u8g2_font_unifont_h_utf8.h -n u8g2_font_unifont_h_utf8
```

##### u8g2_font_unifont_t_chinese

- Glyphs: 22145/57389
- Size: 979,557
- Generation script:

```console
bdfconv -v -f 1 -m "32-127,11904-12351,19968-40959,63744-64255,65280-65376" unifont_jp-14.0.02.bdf -o u8g2_font_unifont_t_chinese.h -n u8g2_font_unifont_t_chinese
```

##### u8g2_font_unifont_t_chinese4

- Glyphs: 7199/57389
- Size: 298,564
- Traditional Chinese common font list: <https://raw.githubusercontent.com/ButTaiwan/cjktables/master/taiwan/edu_standard_1.txt>
- Simplified Chinese common font list: <http://zht.glyphwiki.org/font/gw1197839.source>
- extra font list: 32-127,11904-12351,63744-64255,65280-65376
- Generation script:

```console
bdfconv -v -f 1 -M chinese4.list unifont_jp-14.0.02.bdf -o u8g2_font_unifont_t_chinese4.h -n u8g2_font_unifont_t_chinese4
```

##### u8g2_font_unifont_t_cjk

- Glyphs: 41364/57389
- Size: 1,704,862
- Generation script:

```console
bdfconv -v -f 1 -m "32-127,4352-4607,11904-12255,12288-19903,19968-40943,43360-43391,44032-55203,55216-55295,63744-64255,65072-65103,65280-65519" unifont_jp-14.0.02.bdf -o u8g2_font_unifont_t_cjk.h -n u8g2_font_unifont_t_cjk
```

</details>

<details>

<summary>Performance</summary>

This library is not putting speed at the first priority, but still paid much effort to make the display look smooth.

### Figures

Below are some figures compare with other 3 Arduino common display libraries.

- Arduino IDE: 1.8.15
- arduino-esp32: 1.0.6
- Dev Board: TTGO T8 v1.8
- PSRAM: disable
- Display: ILI9341
- Interface: SPI
- SPI Frequency: 40MHz
- Test time: 2021 Jun 16

| Benchmark          |  Adafruit_GFX | *Arduino_GFX* |    Lovyan_GFX |      TFT_eSPI |
| ------------------ | ------------- | ------------- | ------------- | ------------- |
| Screen fill        |       195,782 |     *160,094* |       154,341 |       155,938 |
| Text               |        97,662 |      *18,960* |        22,473 |        21,752 |
| Pixels             |     1,365,211 |     *903,549* |       867,702 |       775,781 |
| Lines              |     1,062,311 |     *412,026* |       269,060 |       264,950 |
| Horiz/Vert Lines   |        17,637 |      *14,197* |        13,692 |        13,833 |
| Rectangles-filled  |       406,817 |     *332,696* |       320,761 |       323,908 |
| Rectangles         |        11,641 |       *9,254* |         8,545 |         8,714 |
| Triangles-filled   |       150,941 |     *118,010* |       105,661 |       109,675 |
| Triangles          |        58,843 |      *23,570* |        15,884 |        16,277 |
| Circles-filled     |        76,739 |      *52,170* |        42,787 |        45,827 |
| Circles            |       118,125 |      *40,955* |        25,959 |        25,269 |
| Arcs-filled        |      N/A      |      *33,381* |        21,546 |      N/A      |
| Arcs               |      N/A      |      *66,054* |        47,901 |      N/A      |
| Rounded rects-fill |       408,534 |     *338,136* |       318,882 |       323,189 |
| Rounded rects      |        43,185 |      *21,562* |        13,089 |        15,371 |

### Why Run Fast?

- No read operation. Since not all display provide read back graphic memories API, Arduino_GFX skip all read operations. It can reduce the library size footprint and sometimes reduce the operation time.
- Tailor-made data bus classes. Arduino_GFX decouple data bus operation from display driver, it is more easy to write individual data bus class for each platform.

</details>

<details>

<summary>Supported Interfaces</summary>

### Various data bus interfaces

Arduino_GFX utilizes Arduino Built-in SPI class to support 8-bit SPI for most platforms.

Most tiny displays in hobbyist electronics world support 8-bit SPI, but some require 9-bit SPI. Arduino_GFX should be the first Arduino display library that can use ESP32 SPI to support 9-bit hardware SPI. It is important to support the displays that require 9-bit SPI interface. (e.g. HX8357B, ...)

Larger displays most likely do not support standalone SPI since it is not fast enough to refresh the full screen details. Most of them support 8-bit/16-bit Parallel interface.

Some larger display require RGB + 3-bit SPI combo interface, This interface requies at most 3(9-bit SPI) + 4(CS, CD, WR, RD) + 24(RBG888) = 31 pins. Most dev board do not have enough GPIO to support this. Arduino_GFX is stick to RGB565 color, so RGB666 and RGB888 require some connection hack. E.g. RGB666 connect R5 and R6 together, B5 and B6 together to become RGB565. Then the least GPIO requirement can become 3(9-bit SPI) + 2(CD, WR) + 16(RBG565) = 21 pins. **Remember always pull down CS pin and always pull up RD pin.**

### Currently Supported data bus [[Wiki](https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class)]

- 8-bit and 9-bit hardware SPI (ESP32SPI)
- 8-bit hardware SPI (HWSPI, ESP8266SPI, mbedSPI, NRFXSPI, RPiPicoSPI)
- 8-bit and 9-bit software SPI (SWSPI)
- 8-bit parallel interface (SWPAR8, AVRPAR8, ESP32LCD8, ESP32PAR8, ESP32S2PAR8, RPiPicoPAR8, RTLPAR8, STM32PAR8)
- 16-bit parallel interface (ESP32LCD16, ESP32PAR16, ESP32S2PAR16, RPiPicoPAR16)
- RGB565+SPI interface (ESP32RGBPanel)

#### Note

ESP32LCD8, ESP32LCD16 and ESP32RGBPanel only supported by arduino-esp32 v2.x and no longer support in v3.0.

</details>

<details>

<summary>Supported Dev Board</summary>

### Currently Supported Dev Board

- Ameba RTL8722DM Board (AMB 21)
- Ameba RTL8722DM MINI Board (AMB 23)
- Arduino Mega 2560 [[demo video](https://youtu.be/Hn2cTNrkOSM)]
- Arduino Nano
- Arduino Nano BLE 33
- Arduino Pro Micro
- Arduino UNO
- Arduino UNO R4 Minima [[demo video](https://youtu.be/M1TuEU5uPb0)]
- Arduino UNO R4 WiFi [[demo video](https://youtu.be/GB90AFSLIFo)]
- ESP8266 Series
- ESP32 Series
- ESP32-C3 Series
- ESP32-S2 Series
- ESP32-S3 Series
- Raspberry Pi Pico
- Raspberry Pi Pico W
- rtlduino BW16 (by Ai-Thinker)
- Sony Spresense
- WeAct BlackPill V2.0 (BlackPill F411CE)
- [Seeed Studio XIAO SAMD21](https://www.seeedstudio.com/Seeeduino-XIAO-3Pcs-p-4546.html)
- [Seeed Studio XIAO ESP32C3](https://www.seeedstudio.com/Seeed-XIAO-ESP32C3-p-5431.html)
- [Seeed Studio XIAO ESP32S3](https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html)

</details>

<details>

<summary>Supported Dev Device</summary>

### Currently Supported Dev Device [[Wiki](https://github.com/moononournation/Arduino_GFX/wiki/Dev-Device-Declaration)]

- [ESP32-1732S019](https://www.aliexpress.com/item/1005005059421229.html) [[demo video](https://youtube.com/shorts/VS4Qb3g2dWk)] [[LVGL demo video](https://youtu.be/V5xib6OnWiM)]
- ESP32-2432S028
- ESP32-2424012 [[demo video](https://youtu.be/EXw_yEMgug8)]
- ESP32-3248S035
- ESP32-4827A043 [[demo video](https://youtu.be/pd1DTW9QHkg)] [[LVGL demo video](https://youtu.be/L8iYjiy-DUI)]
- [ESP32-4827S043](https://www.aliexpress.com/item/1005004788147691.html) [[demo video 1](https://youtu.be/60rl7QoU4Sc)] [[demo video 2](https://youtube.com/shorts/QY09u37htIk)] [[LVGL demo video](https://youtu.be/VvpILAVyPt8)]
- [ESP32-8048S043](https://www.aliexpress.com/item/1005004788147691.html) [[demo video](https://youtu.be/tXBVTAzSf58)]
- [ESP32-8048S070](https://www.aliexpress.com/item/1005004952726089.html) [[LVGL demo video](https://youtu.be/7BRGVsnQpgE)]
- [ESP32 LCDKIT](https://docs.espressif.com/projects/espressif-esp-dev-kits/en/latest/esp32/esp32-lcdkit/user_guide.html)
- [ESP32-S3-EYE](https://github.com/espressif/esp-who/blob/master/docs/en/get-started/ESP32-S3-EYE_Getting_Started_Guide.md)
- [ESP32-S3-Box](https://www.espressif.com/en/news/ESP32-S3-BOX_video)
- [ESP32-S3-Box-3](https://www.espressif.com/en/news/ESP32-S3-BOX-3)
- [ESP32-S3-RGB](https://github.com/W00ng/ESP32-S3-RGB-Panel) [[LVGL demo video](https://youtu.be/d11yUvjh34A)]
- ESP32S3-2.1-TP
- [ESPboy](https://www.espboy.com) [[demo video](https://youtu.be/Cx82XWrc8-0)]
- [Guition JC1060P470](https://www.aliexpress.com/item/1005008328088576.html) [[demo video](https://youtu.be/CF1EDSQDHQ8)] [[LVGL demo](https://youtu.be/CF1EDSQDHQ8)]
- [LILYGO T-Deck](https://www.lilygo.cc/products/t-deck?bg_ref=Ts2JN05e23) [[demo video](https://youtube.com/shorts/fXKTVqjUoPM)]
- [LILYGO T-Deck Plus](https://www.lilygo.cc/products/t-deck-plus-1?bg_ref=Ts2JN05e23)
- [LILYGO T-Display](https://www.lilygo.cc/products/lilygo®-ttgo-t-display-1-14-inch-lcd-esp32-control-board?bg_ref=Ts2JN05e23)
- [LILYGO T-Display-S3](https://www.lilygo.cc/products/t-display-s3?bg_ref=Ts2JN05e23) [[demo video](https://youtu.be/kpRC64QNQAo)]
- [LILYGO T-Display-S3 AMOLED](https://www.lilygo.cc/products/t-display-s3-amoled?bg_ref=Ts2JN05e23) [[demo video](https://youtu.be/NvOGJAMlh1M)]
- [LILYGO T-Display-S3 AMOLED 1.64](https://www.lilygo.cc/products/t-display-s3-amoled-1-64?bg_ref=Ts2JN05e23) [[demo video](https://youtu.be/5O3fQ1xNsrg)][[LVGL demo video](https://youtu.be/6UEaxWfxm9g)]
- [LILYGO T-Display S3 Long](https://www.lilygo.cc/products/t-display-s3-long?bg_ref=Ts2JN05e23)[[LVGL demo video](https://youtu.be/OuxLFwxvcVc)]
- [LILYGO T-Display S3 Pro](https://www.lilygo.cc/products/t-display-s3-pro?bg_ref=Ts2JN05e23) [[demo video](https://youtube.com/shorts/PE-GKTzbdP8)]
- [LILYGO T-QT Pro](https://www.lilygo.cc/products/t-qt-pro?bg_ref=Ts2JN05e23) [[demo video](https://youtube.com/shorts/V1MCQ1tQ8PM)]
- [LILYGO T-RGB](https://www.lilygo.cc/products/t-rgb?bg_ref=Ts2JN05e23) [[LVGL demo video](https://youtu.be/BKEl_pWp_qQ)]
- [LILYGO T-Track](https://www.lilygo.cc/products/t-track?bg_ref=Ts2JN05e23) [[demo video](https://youtu.be/6wmUhp-5eMg)][[LVGL demo video](https://youtu.be/wQjMu5JZSkg)]
- LILYGO T-Watch
- [LILYGO T-Watch 2021](https://www.lilygo.cc/products/t-watch-2021?bg_ref=Ts2JN05e23)
- [LILYGO T4 S3](https://www.lilygo.cc/products/t4-s3?bg_ref=Ts2JN05e23)[[LVGL demo video](https://youtu.be/h4vXEYrDERM)]
- [M5Stack Core Family](https://shop.m5stack.com/collections/m5-controllers/CORE)
- [M5Stack AtomS3](https://shop.m5stack.com/products/atoms3-dev-kit-w-0-85-inch-screen)[[demo video](https://youtu.be/8u4TwZHmnN0)]
- [Makerfabs ESP32 3.5" TFT Touch with Camera](https://www.makerfabs.com/esp32-3.5-inch-tft-touch-capacitive-with-camera.html)
- [Makerfabs ESP32-S3 TFT 4.0"](https://www.makerfabs.com/esp32-s3-parallel-tft-with-touch-4-inch.html) [[demo video](https://youtu.be/Fmxd-Xu97C8)]
- [Makerfabs ESP32-S3 TFT 4.3" v1.3](https://www.makerfabs.com/esp32-s3-parallel-tft-with-touch-4-3-inch.html) [[demo video](https://youtu.be/oQ57L2gTHoo)]
- [Odroid Go](https://www.hardkernel.com/shop/odroid-go/)
- [seeed studio Wio Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
- [Waveshare ESP32-C6-LCD-1.47](https://www.waveshare.com/esp32-c6-lcd-1.47.htm?&aff_id=107987)
- [Waveshare ESP32-C6-LCD-1.9](https://www.waveshare.com/esp32-c6-lcd-1.9.htm?&aff_id=107987)[[demo video](https://youtube.com/shorts/OryF57VqufY?feature=share)]
- [Waveshare ESP32-S3 1.46inch Round Display Development Board](https://www.waveshare.com/esp32-s3-touch-lcd-1.46b.htm?&aff_id=107987) [[demo video](https://youtube.com/shorts/tqyqxdRA550)]
- [Waveshare ESP32-S3-Touch-LCD-1.3](https://www.waveshare.com/esp32-s3-lcd-1.3.htm?&aff_id=107987) [[demo video](https://youtube.com/shorts/_n3qTa_nVGE)]
- [Waveshare ESP32-S3-Touch-LCD-1.3 with case and prism cube](https://www.waveshare.com/esp32-s3-lcd-1.3.htm?sku=30559&aff_id=107987) [[demo video](https://youtube.com/shorts/tqyqxdRA550)]
- [Waveshare ESP32-S3-Touch-LCD-2.8](https://www.waveshare.com/esp32-s3-touch-lcd-2.8.htm?&aff_id=107987) [[demo video](https://youtube.com/shorts/1RU_EanUgSU)
- [Waveshare ESP32-S3-Touch-AMOLED-1.64](https://www.waveshare.com/esp32-s3-touch-amoled-1.64.htm?&aff_id=107987)[[demo video](https://youtube.com/shorts/aTTQ9PKgESU?feature=share)]
- [Waveshare ESP32-S3-Touch-AMOLED-1.8](https://www.waveshare.com/esp32-s3-touch-amoled-1.8.htm?&aff_id=107987)[[demo video](https://youtube.com/shorts/sHjCoPSsC2Q?feature=share)]

- [Waveshare ESP32-S3-Touch-AMOLED-2.41](https://www.waveshare.com/esp32-s3-touch-amoled-2.41.htm?&aff_id=107987)
- [Waveshare RP2040-LCD-0.96](https://www.waveshare.com/rp2040-lcd-0.96.htm?&aff_id=107987)
- [Waveshare RP2040-LCD-1.28](https://www.waveshare.com/rp2040-lcd-1.28.htm?&aff_id=107987)
- [Waveshare RP2350-LCD-0.96](https://www.waveshare.com/rp2350-lcd-0.96.htm?&aff_id=107987)
- [wireless-tag WT-32-SC01](http://www.wireless-tag.com/portfolio/wt32-sc01/)
- [Elecrow ESP Terminal with 3.5" parallel RGB display DLC35010R](https://www.elecrow.com/esp-terminal-with-esp32-3-5-inch-parallel-480x320-tft-capacitive-touch-display-rgb-by-chip-ili9488.html) [[demo video](https://youtu.be/QRDVuwayNFw)]
- [Elecrow Wizee-ESP32 WZ8048C050](https://www.elecrow.com/esp32-display-5-inch-hmi-display-rgb-tft-lcd-touch-screen-support-lvgl.html)
- [wireless-tag ZX2D10GE10R-V4848](https://github.com/wireless-tag-com/ZX2D10GE01R-V4848)
- [wireless-tag ZX3D50CE02S](https://github.com/wireless-tag-com/ZX3D50CE02S)
- [wireless-tag ZX3D95CE01S-AR](https://github.com/wireless-tag-com/ZX3D95CE01S-AR-4848)
- [wireless-tag ZX3D95CE01S-TR](https://github.com/wireless-tag-com/ZX3D95CE01S-TR-4848) [[demo video](https://www.youtube.com/shorts/5u6_C-krK2Q)]
- [QM Smart Panlee 7.0 inch serial screen ZX7D00CE01S](http://en.smartpanle.com/product-item-19.html) [[demo video](https://youtu.be/r-zAMUzpkGE)]

</details>

<details>

<summary>Supported Display</summary>

### Currently Supported Display [[Wiki](https://github.com/moononournation/Arduino_GFX/wiki/Display-Class)]

- GC9A01 240x240 round display [[demo video](https://youtu.be/kJrAFm20-zg)]
- GC9C01 360x360 round display [[demo video](https://youtube.com/shorts/Sk9sVT9PawA)]
- GC9106 80x160 [[demo video](https://youtu.be/RToGeeb1jxQ)]
- GC9107 128x128 [[demo video](https://youtube.com/shorts/V1MCQ1tQ8PM)]
- GC9503V 480x480 (RGB) [[demo video](https://youtube.com/shorts/hk7ZMBRCmjI)]
- HX8347C 240x320 [[demo video](https://youtu.be/25ymuV51YQM)]
- HX8347D 240x320 [[demo video](https://youtu.be/sv6LGkLRZjI)]
- HX8394 720x1280 [[demo video](https://www.bilibili.com/video/BV1eNLRzaEFL)]
- HX8352C 240x400 [[demo video](https://youtu.be/m2xWYbS3t7s)]
- HX8357A 320x480 [[demo video](https://youtu.be/wJkLO_xCTXA)] (currently only portrait works, i.e. rotation 0 and 2)
- HX8357B 320x480 (9-bit SPI) [[demo video](https://youtu.be/pB6_LOCiUqg)]
- HX8369A 480x800 [[demo video](https://youtu.be/sXpU8bhtXKQ)] [[LVGL demo video](https://youtu.be/q575lTuVDcU)]
- ILI6122 480x800 (RGB)
- ILI6485 480x272 (RGB) [[demo video](https://youtu.be/60rl7QoU4Sc)]
- ILI9225 176x220 [[demo video](https://youtu.be/jm2UrCG27F4)]
- ILI9341 240x320 [[demo video](https://youtu.be/NtlEEL7MkQY)]
- ILI9341 240x320 (8-bit/16-bit Parallel) [[demo video](https://youtu.be/xuVx0dzQ7nM)]
- ILI9342 320x240 [[demo video](https://youtu.be/UoPpIjVSO5Q)]
- ILI9481 320x480 (18 bit color) [[demo video](https://youtu.be/YxjuuCFhlqM)]
- ILI9486 320x480 (8-bit/16-bit Parallel) [[demo video](https://youtu.be/GB90AFSLIFo)]
- ILI9486 320x480 (18 bit color) [[demo video](https://youtu.be/pZ6izDqmVds)]
- ILI9488 320x480 (3 bit color with canvas) [[demo video](https://youtu.be/r7be0WbIBYk)]
- ILI9488 320x480 (18 bit color) [[demo video](https://youtu.be/NkE-LhtLHBQ)]
- ILI9806 (8-bit/16-bit Parallel) 480x854 [[demo video](https://youtu.be/mYv-wdtWr8s)] [[LVGL demo video](https://youtu.be/PqjV8lovg_c)][[2](https://youtu.be/j31KZoQUKis)]
- JBT6K71 240x320 (8-bit Parallel) [[demo video](https://youtu.be/qid3F4Gb0mM)]
- NT35310 320x480 [[demo video](https://youtu.be/bvIz5CoYPNk)]
- NT35510 480x800 (8-bit/16-bit Parallel) [[demo video](https://youtu.be/C_1ASzUN3bg)]
- NT39125 240x376 (8-bit/16-bit Parallel) [[demo video](https://youtu.be/JGMrM18JAFA)]
- NV3007 142x428 [[demo video](https://youtube.com/shorts/ePcf0LmMgOo)]
- NV3041A 480x272 [[demo video](https://youtu.be/pd1DTW9QHkg)]
- OTM8009A 480x800 (8-bit/16-bit Parallel)
- R61529 320x480 (8-bit/16-bit Parallel) [[demo video](https://youtu.be/s93gxjbIAT8)]
- Raspberry Pi DPI Display (RPi_DPI_RGBPanel) Any Resolution [[demo video](https://youtube.com/shorts/IqQEq-VLVwI)]
- SEPS525 160x128 [[demo video](https://youtu.be/tlmvFBHYv-k)]
- SSD1283A 130x130 [[demo video](https://youtu.be/OrIchaRikiQ)]
- SSD1331 96x64 [[demo video](https://youtu.be/v20b1A_KDcQ)]
- SSD1351 128x128 [[demo video](https://youtu.be/5TIM-qMVBNQ)]
- SSD1351 128x96
- ST7735 128x160 (various tabs) [[demo video](https://youtu.be/eRBSSD_N9II)]
- ST7735 128x128 (various tabs) [[demo video](https://youtu.be/6rueSV2Ee6c)]
- ST7735 80x160 [[demo video](https://youtu.be/qESHDuYo_Mk)]
- ST7701 480x480 (RGB) [[demo video](https://youtube.com/shorts/JV8Rzxop5EQ)] [[2.1" round display demo video](https://youtube.com/shorts/WLWio1CjBoo?feature=share)] [[2.8" round display demo video](https://youtube.com/shorts/Ih_QlttWTVk?feature=share)]
- ST7789 135x240 [[demo video](https://youtu.be/Zk81_T8c20E)]
- ST7789 240x240 [[demo video](https://youtu.be/Z27zYg5uAsk)]
- ST7789 240x240 [[demo video](https://youtu.be/9AqsXMB8Qbk)]
- ST7789 240x280 round corner display [[demo video](https://youtu.be/KzDC02wg8z0)]
- ST7789 240x320 [[demo video](https://youtu.be/ZEvc1LkuVuQ)]
- ST7796 320x480 [[demo video](https://youtu.be/hUL-RuG4MAQ)]
- WEA2012 356x400 [[demo video](https://youtube.com/shorts/neDyijFrfQY)] [[LVGL demo video](https://youtube.com/shorts/z9Z_u0xg_as)]

### Tobe Support Display (Sponsors can make it happen)

- Mono display supported by co-operate with Canvas
- Multi-color e-ink display supported by co-operate with Canvas

</details>

<details>

<summary>Canvas (framebuffer)</summary>

### Canvas Class [[Wiki](https://github.com/moononournation/Arduino_GFX/wiki/Canvas-Class)]

- Arduino_Canvas (16-bit pixel)
- Arduino_Canvas_3bit (1/4 memory space of 16-bit pixel)
- Arduino_Canvas_Indexed (half memory space of 16-bit pixel)
- Arduino_Canvas_Mono (1/16 memory space of 16-bit pixel)

</details>

<details>

<summary>LVGL Support</summary>

### 3 LVGL demo in Library Examples

- LvglBenchmark [[demo video](https://youtu.be/75Qx-UEgabY)]
- LvglHelloWorld
- LvglWidgets

</details>

<details>

<summary>Feature Wishlist</summary>

### Sponsors can make it happen

- Print color Emoji Characters
- Load bitmap font files from flash / SD
- Fill Gradient (Discussion #128)

</details>

<details>

<summary>Using source code come from</summary>

- <https://github.com/adafruit/Adafruit-GFX-Library.git>
- <https://github.com/adafruit/Adafruit_ILI9341.git>
- <https://github.com/adafruit/Adafruit-SSD1351-library.git>
- <https://github.com/ananevilya/Arduino-ST7789-Library.git>
- <https://github.com/BasementCat/arduino-tft-gif.git>
- <https://github.com/Bodmer/TFT_eSPI.git>
- <https://github.com/daumemo/IPS_LCD_R61529_FT6236_Arduino_eSPI_Test.git>
- <https://github.com/espressif/arduino-esp32.git>
- <https://github.com/espressif/esp-idf.git>
- <https://github.com/gitcnd/LCDWIKI_SPI.git>
- <https://github.com/hi631/LCD_NT35510-MRB3971.git>
- <https://github.com/lcdwiki/LCDWIKI_SPI.git>
- <https://github.com/Xinyuan-LilyGO/T-RGB.git>
- <https://github.com/lovyan03/LovyanGFX.git>
- <https://github.com/modi12jin/Arduino-ESP32-WEA2012.git>
- <https://github.com/nopnop2002/esp-idf-parallel-tft.git>
- <https://github.com/olikraus/u8g2.git>

</details>

## Sponsorship vs Support

As you may already aware there are lack of sponsorship in this project. Convert the funding in terms of man power, it is much lower than 1 man hour per month. So don't expect too much on the support. Expecially the features not realted to my planned maker projects ;>

For the same reason, Arduino_GFX only focus on the Arduino IDE support. Any other IDE, e.g. PlatformIO, if you found an issue at that IDE but normal at Arduino IDE, please direct report to that IDE for better support.

**Please use Discussions space for new hardware support or new feature request. I will direct close any non-issue issues. And I will consider report the users who insist raising duplicate issue continuously.**

If you like Arduino_GFX, you can:

[![Buy Me A Coffee](https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png)](https://www.buymeacoffee.com/moononournx)
