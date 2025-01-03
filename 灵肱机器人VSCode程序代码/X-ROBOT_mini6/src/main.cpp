///////////////////////////////////////////////////////////////基础库
#include "Arduino.h"
#include <stdio.h>
#include "string.h"
///////////////////////////////////////////////////////////////freertos操作系统必加库
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
/////////////////////////////////////////////////////////////////LVGL必加库
#include <SPI.h>
#include <TFT_eSPI.h>
#include "demos\lv_demos.h"
#include "lvgl_all.h"
/////////////////////////////////////////////////////////////////RGB灯必加库
#include "RGB.h"
/////////////////////////////////////////////////////////////////CAN通信必加库
#include "CAN.h"
//////////////////////////////////////////////////////////////////UI设置
#include "ui_main.h"   
/////////////////////////////////////////////////////////////////esp_now无线通信
#include <WiFi.h>
#include <esp_now.h>
/////////////////////////////////////////////////////////////////SD卡
#include "SD.h"
#include <ArduinoJson.h>
///////////////////////////////////////////////////////////////
#include "task.h"

//const char* ssid = "TP-LINK_1FD1";
//const char* password = "1234567890";

File myFile2;

/*


CAN0 J1(1);
CAN0 J2(2);
CAN0 J3(3);
CAN0 J4(4);
CAN0 J5(5);
CAN0 J6(6);
*/








void setup() 
{
    pinMode(34,INPUT);
    pinMode(35,INPUT);
    greed2();
  //  greed();
    app_twai_init();//CAN初始化
    rgb_init();   //RGB初始化
    //SD.begin(15);
    lvgl_init();    //LVGL初始化
     

    delay(100);



   // xTaskCreate(&RGB_task,"RGB_task",2048,NULL,1,NULL);         //RGB任务开启
     

   // delay(500);
   // xTaskCreate(&LVGL_task,"LVGL_task",102400,NULL,6,NULL);      //LVGL任务开启
   // xTaskCreate(&CAN_task,"CAN_task",10240,NULL,4,NULL);        //CAN任务开启

    
    

    


}

void loop() 
{
      lvgl_update();
}


