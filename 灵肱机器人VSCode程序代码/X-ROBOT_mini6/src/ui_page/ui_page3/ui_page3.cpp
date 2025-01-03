#include <Arduino.h>
#include "ui_page3.h"
#include "ui_main.h"
#include <SPI.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include "demos\lv_demos.h"
#include "driver/pcnt.h"
#include "lvgl_all.h"


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "task.h"
TaskHandle_t esp_now_task_handle=NULL;

typedef struct
{
	bool screen_3_del;
	lv_obj_t *screen_3_btn_1;
	lv_obj_t *screen_3_btn_1_label;
}lv_ui;


lv_obj_t *sw1_tab_3;
lv_obj_t *text1_3;
lv_obj_t *text2_3;
lv_obj_t *text3_3;
lv_obj_t *text4_3;
lv_obj_t *text5_3;
lv_obj_t *text6_3;
lv_obj_t *sw2_tab_3;
lv_obj_t * sw1_3;
lv_obj_t * sw2_3;


static void event_cb1(lv_event_t *e){

   lv_event_code_t code =lv_event_get_code(e);
   lv_obj_t * sw= lv_event_get_target(e);
   if(code==LV_EVENT_CLICKED){

        lv_scr_load(scr0);
        lv_indev_set_group(enc_indev, g0);
        if(lv_obj_has_state(sw,LV_STATE_CHECKED)){
    
        }else{

        }
   }


}


static void event_cb2(lv_event_t *e){

   lv_event_code_t code =lv_event_get_code(e);
   lv_obj_t * s= lv_event_get_target(e);
   if(code==LV_EVENT_VALUE_CHANGED){
        if(lv_obj_has_state(s,LV_STATE_CHECKED)){
            lv_label_set_text(sw1_tab_3,"追踪器3D捕捉已启动");
			 xTaskCreate(esp_now_task,"esp_now_task",10240,NULL,5,&esp_now_task_handle);         //esp-now任务开启
     
        }else{
            lv_label_set_text(sw1_tab_3,"追踪器3D捕捉已终止");
			if(esp_now_task_handle!=NULL){
				vTaskDelete(esp_now_task_handle);
				esp_now_task_handle=NULL;
            }
        }
   }
}

void page3_init(){

    




    LV_FONT_DECLARE(lv_font_chinese2_14);
    	//Write codes screen_btn_1
    lv_ui *ui;
	//Write codes screen_3_btn_1
	ui->screen_3_btn_1 = lv_btn_create(scr3);
	ui->screen_3_btn_1_label = lv_label_create(ui->screen_3_btn_1);
	lv_label_set_text(ui->screen_3_btn_1_label, "返回");
	lv_label_set_long_mode(ui->screen_3_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_3_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_3_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_3_btn_1_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_3_btn_1, 79, 232);
	lv_obj_set_size(ui->screen_3_btn_1, 79, 26);

	//Write style for screen_3_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_3_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_3_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_3_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_3_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_3_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_3_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_3_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_3_btn_1, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_3_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_3_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);




	sw1_3 = lv_switch_create (scr3);
    lv_obj_center(sw1_3);
    lv_obj_align(sw1_3 ,LV_ALIGN_CENTER,-80,-85);
    lv_obj_add_event_cb(sw1_3,event_cb2,LV_EVENT_VALUE_CHANGED,NULL);

    sw1_tab_3 =lv_label_create(scr3);
    lv_label_set_text(sw1_tab_3,"追踪器3D捕捉开始");
    lv_obj_align_to(sw1_tab_3,sw1_3,LV_ALIGN_OUT_RIGHT_MID,10,0);
	lv_obj_set_style_text_font(sw1_tab_3, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);

	text1_3 =lv_label_create(scr3);
    lv_label_set_text(text1_3,"J1:0");
	lv_obj_align(text1_3, LV_ALIGN_CENTER, -60, -40);
	//lv_obj_set_style_text_font(text1_3, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);

	text2_3 =lv_label_create(scr3);
    lv_label_set_text(text2_3,"J2:0");
	lv_obj_align(text2_3, LV_ALIGN_CENTER, 40, -40);


	text3_3 =lv_label_create(scr3);
    lv_label_set_text(text3_3,"J3:0");
	lv_obj_align(text3_3, LV_ALIGN_CENTER, -60, -10);

	text4_3 =lv_label_create(scr3);
    lv_label_set_text(text4_3,"J4:0");
	lv_obj_align(text4_3, LV_ALIGN_CENTER, 40, -10);

	text5_3 =lv_label_create(scr3);
    lv_label_set_text(text5_3,"J5:0");
	lv_obj_align(text5_3, LV_ALIGN_CENTER, -60, 20);

	text6_3 =lv_label_create(scr3);
    lv_label_set_text(text6_3,"J6:0");
	lv_obj_align(text6_3, LV_ALIGN_CENTER, 40, 20);

	lv_obj_add_event_cb(ui->screen_3_btn_1,event_cb1,LV_EVENT_CLICKED,NULL);
	lv_group_add_obj(g3, sw1_3);
    lv_group_add_obj(g3, ui->screen_3_btn_1);




}



void page3_loop(){




	
	esp_now_task_show();




}
