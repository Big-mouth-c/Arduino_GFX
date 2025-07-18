#pragma once

// ESP_LCD_Panel implementation for esp32s3.

// This panel implementation requires a hardware setup with
//  * RGB LCD peripheral supported (esps3 for now)
//  * Octal PSRAM onboard
//  * RGB panel, 16 bit-width, with HSYNC, VSYNC and DE signal
//
// It uses a Single Frame Buffer in PSRAM
//
// See: (ESP32 board version 3.x)
// * https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/api-reference/peripherals/lcd/rgb_lcd.html
// * https://github.com/espressif/esp-idf/blob/master/examples/peripherals/lcd/rgb_panel/README.md
//
// The prior implementation (ESP32 board version 2.x) was largely undocumented.

#include "Arduino_DataBus.h"

//#if defined(ESP32) && (CONFIG_IDF_TARGET_ESP32S3)

#if defined(ESP32) && (CONFIG_IDF_TARGET_ESP32S3 || CONFIG_IDF_TARGET_ESP32P4)  //Modify

#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_panel_ops.h"


//#include "esp32s3/rom/cache.h"
// This function is located in ROM (also see esp_rom/${target}/ld/${target}.rom.ld)
//extern int Cache_WriteBack_Addr(uint32_t addr, uint32_t size);

//Modify
// 根据目标芯片选择不同的头文件 （Select different header files according to the target chip）
#if defined(CONFIG_IDF_TARGET_ESP32S3)
    #include "esp32s3/rom/cache.h"
#elif defined(CONFIG_IDF_TARGET_ESP32P4)
    #include "esp32p4/rom/cache.h"
#else
    #error "Unsupported target chip! Please use ESP32-S3 or ESP32-P4."
#endif

// 根据芯片类型选择正确的函数签名 （Select different header files according to the target chip）
#if defined(CONFIG_IDF_TARGET_ESP32P4)
    // ESP32-P4需要使用带gid和map参数的版本
    extern "C" int Cache_WriteBack_Addr_Gid(uint32_t gid, uint32_t map, uint32_t addr, uint32_t size);
    
    // 创建兼容旧版API的包装函数
    static inline int Cache_WriteBack_Addr(uint32_t addr, uint32_t size) {
        // 使用默认gid=0，并同时操作L1 DCache和L2 Cache
        return Cache_WriteBack_Addr_Gid(0, CACHE_MAP_L1_DCACHE | CACHE_MAP_L2_CACHE, addr, size);
    }
#else
    // ESP32-S3及其他芯片使用原始API
    extern "C" int Cache_WriteBack_Addr(uint32_t addr, uint32_t size);
#endif


//#if (!defined(ESP_ARDUINO_VERSION_MAJOR)) || (ESP_ARDUINO_VERSION_MAJOR < 3)
#if (!defined(ESP_ARDUINO_VERSION_MAJOR)) || (ESP_ARDUINO_VERSION_MAJOR >5)
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_interface.h"
#include "esp_private/gdma.h"
#include "esp_pm.h"
#include "hal/dma_types.h"

#include "hal/lcd_hal.h"
#include "hal/lcd_ll.h"

// extract from esp-idf esp_lcd_rgb_panel.c
struct esp_rgb_panel_t
{
  esp_lcd_panel_t base;                                        // Base class of generic lcd panel
  int panel_id;                                                // LCD panel ID
  lcd_hal_context_t hal;                                       // Hal layer object
  size_t data_width;                                           // Number of data lines (e.g. for RGB565, the data width is 16)
  size_t sram_trans_align;                                     // Alignment for framebuffer that allocated in SRAM
  size_t psram_trans_align;                                    // Alignment for framebuffer that allocated in PSRAM
  int disp_gpio_num;                                           // Display control GPIO, which is used to perform action like "disp_off"
  intr_handle_t intr;                                          // LCD peripheral interrupt handle
  esp_pm_lock_handle_t pm_lock;                                // Power management lock
  size_t num_dma_nodes;                                        // Number of DMA descriptors that used to carry the frame buffer
  uint8_t *fb;                                                 // Frame buffer
  size_t fb_size;                                              // Size of frame buffer
  int data_gpio_nums[SOC_LCD_RGB_DATA_WIDTH];                  // GPIOs used for data lines, we keep these GPIOs for action like "invert_color"
  size_t resolution_hz;                                        // Peripheral clock resolution
  esp_lcd_rgb_timing_t timings;                                // RGB timing parameters (e.g. pclk, sync pulse, porch width)
  gdma_channel_handle_t dma_chan;                              // DMA channel handle
  esp_lcd_rgb_panel_frame_trans_done_cb_t on_frame_trans_done; // Callback, invoked after frame trans done
  void *user_ctx;                                              // Reserved user's data of callback functions
  int x_gap;                                                   // Extra gap in x coordinate, it's used when calculate the flush window
  int y_gap;                                                   // Extra gap in y coordinate, it's used when calculate the flush window
  struct
  {
    unsigned int disp_en_level : 1; // The level which can turn on the screen by `disp_gpio_num`
    unsigned int stream_mode : 1;   // If set, the LCD transfers data continuously, otherwise, it stops refreshing the LCD when transaction done
    unsigned int fb_in_psram : 1;   // Whether the frame buffer is in PSRAM
  } flags;
  dma_descriptor_t dma_nodes[]; // DMA descriptor pool of size `num_dma_nodes`
};
#endif // #if (!defined(ESP_ARDUINO_VERSION_MAJOR)) || (ESP_ARDUINO_VERSION_MAJOR < 3)

class Arduino_ESP32RGBPanel
{
public:
  Arduino_ESP32RGBPanel(
      int8_t de, int8_t vsync, int8_t hsync, int8_t pclk,
      int8_t r0, int8_t r1, int8_t r2, int8_t r3, int8_t r4,
      int8_t g0, int8_t g1, int8_t g2, int8_t g3, int8_t g4, int8_t g5,
      int8_t b0, int8_t b1, int8_t b2, int8_t b3, int8_t b4,
      uint16_t hsync_polarity, uint16_t hsync_front_porch, uint16_t hsync_pulse_width, uint16_t hsync_back_porch,
      uint16_t vsync_polarity, uint16_t vsync_front_porch, uint16_t vsync_pulse_width, uint16_t vsync_back_porch,
      uint16_t pclk_active_neg = 0, int32_t prefer_speed = GFX_NOT_DEFINED, bool useBigEndian = false,
      uint16_t de_idle_high = 0, uint16_t pclk_idle_high = 0, size_t bounce_buffer_size_px = 0);

  bool begin(int32_t speed = GFX_NOT_DEFINED);

  bool isUseBigEndian() {
    return _useBigEndian;
  }

  uint16_t *getFrameBuffer(int16_t w, int16_t h);

protected:
private:
  int32_t _speed;
  int8_t _de, _vsync, _hsync, _pclk;
  int8_t _r0, _r1, _r2, _r3, _r4;
  int8_t _g0, _g1, _g2, _g3, _g4, _g5;
  int8_t _b0, _b1, _b2, _b3, _b4;
  uint16_t _hsync_polarity;
  uint16_t _hsync_front_porch;
  uint16_t _hsync_pulse_width;
  uint16_t _hsync_back_porch;
  uint16_t _vsync_polarity;
  uint16_t _vsync_front_porch;
  uint16_t _vsync_pulse_width;
  uint16_t _vsync_back_porch;
  uint16_t _pclk_active_neg;
  int32_t _prefer_speed;
  bool _useBigEndian;
  uint16_t _de_idle_high;
  uint16_t _pclk_idle_high;
  size_t _bounce_buffer_size_px;

  esp_lcd_panel_handle_t _panel_handle = NULL;
};

#endif // #if defined(ESP32) && (CONFIG_IDF_TARGET_ESP32S3)
