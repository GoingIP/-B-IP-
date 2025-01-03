#include <SPI.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <Arduino.h>
#include "demos\lv_demos.h"
#include "driver/pcnt.h"
#include "lvgl_all.h"


#include "ui_main.h"
//lv_disp_draw_buf_t draw_buf;
//lv_color_t buf[screenWidth * 10];
//int16_t ec11 = 0;  // 定义并初始化变量
//TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);  // 定义对象



void pcnt_init() {
  pcnt_config_t pcnt_config = {
        .pulse_gpio_num = ENCODER_PIN_A,
        .ctrl_gpio_num = ENCODER_PIN_B,
        .lctrl_mode = PCNT_MODE_KEEP,
        .hctrl_mode = PCNT_MODE_REVERSE,
        .pos_mode = PCNT_COUNT_DEC,
        .neg_mode = PCNT_COUNT_INC,
        .counter_h_lim = 10000,
        .counter_l_lim = -10000,
        .unit =  PCNT_UNIT_0,
        .channel = PCNT_CHANNEL_0,
    };
    pcnt_unit_config(&pcnt_config);
    pcnt_counter_pause( PCNT_UNIT_0);
    pcnt_counter_clear( PCNT_UNIT_0);
    pcnt_counter_resume( PCNT_UNIT_0);

}

void encoder_read(lv_indev_drv_t *drv, lv_indev_data_t *data) {
    
     int16_t count;
    pcnt_get_counter_value( PCNT_UNIT_0, &count);
    pcnt_counter_clear( PCNT_UNIT_0);
     ec11=ec11+count;
    if((ec11>=2)||(ec11<=-2)){
   data->enc_diff =ec11/2;
   ec11=0;
    }else{
   data->enc_diff=0;
    }
    data->state = digitalRead(ENCODER_BUTTON_PIN) == 0 ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;

}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );
    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();
    lv_disp_flush_ready( disp );
}

void tft_init() {
        tft.begin();          /* TFT init */
    tft.setRotation( 2 ); /* Landscape orientation, flipped */
    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );
}

void lvgl_init() {
      pinMode(13,INPUT_PULLUP);
      pinMode(36,INPUT_PULLUP);
      pinMode(39,INPUT_PULLUP);
      pinMode(14,OUTPUT);
      pcnt_init();
      lv_init();
      tft_init();
      lvgl_date_init();
  

}



void lvgl_date_init(){

ui_main_init();




}









void lvgl_update() {
    // 此函数用于在主循环中调用，用于更新显示和处理输入
    lv_task_handler(); // 处理LVGL任务
    ui_main_loop();
   // delay(5);          // 短暂延时以降低处理速度
}

