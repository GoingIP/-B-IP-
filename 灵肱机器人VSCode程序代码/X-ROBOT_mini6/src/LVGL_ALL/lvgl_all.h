#ifndef LVGL_ALL_H
#define LVGL_ALL_H

#define ENCODER_PIN_A 36
#define ENCODER_PIN_B 39
#define ENCODER_BUTTON_PIN 0
#define screenWidth  240
#define screenHeight 280


// 声明全局变量
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];
static TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);
static int16_t ec11=0;  




void pcnt_init();
void encoder_read(lv_indev_drv_t * drv, lv_indev_data_t *data);
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );
void tft_init();
void lvgl_init();
void lvgl_date_init();
void lvgl_update();



#endif 