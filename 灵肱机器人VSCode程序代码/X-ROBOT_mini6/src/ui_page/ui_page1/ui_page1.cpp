#include <Arduino.h>
#include "ui_main.h"
#include <SPI.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include "demos\lv_demos.h"
#include "driver/pcnt.h"
#include "lvgl_all.h"
#include "ui_page1.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "task.h"



TaskHandle_t ROBOT_loction_task_handle=NULL;

lv_obj_t * slider1;
lv_obj_t * slider2;
lv_obj_t * slider3;
lv_obj_t * slider4;
lv_obj_t * slider5;
lv_obj_t * slider6;
lv_obj_t * S1;
lv_obj_t * S2;
lv_obj_t * S3;
lv_obj_t * S4;
lv_obj_t * S5;
lv_obj_t * S6;


typedef struct
{
	bool screen_1_del;
	lv_obj_t *screen_1_btn_1;
	lv_obj_t *screen_1_btn_1_label;
}lv_ui;



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
   lv_obj_t * sw= lv_event_get_target(e);
   if(code==LV_EVENT_VALUE_CHANGED){
        if(lv_obj_has_state(sw,LV_STATE_CHECKED)){
	//	xTaskCreate(&RGB_task,"RGB_task",2048,NULL,1,NULL); 
     xTaskCreate(ROBOT_loction_task,"ROBOT_loction_task",10240,NULL,4,&ROBOT_loction_task_handle);        //ROBOT_loction_task任务开启
        }else{
    
            if(ROBOT_loction_task_handle!=NULL){
            vTaskDelete(ROBOT_loction_task_handle);
            ROBOT_loction_task_handle=NULL;
            }
        }
   }


}

void page1_init(){


/*
    lv_obj_t * ui_Button1 ;
    lv_obj_t * ui_Label1  ;
    ui_Button1 = lv_btn_create(scr1);
    lv_obj_set_width(ui_Button1, lv_pct(41));
    lv_obj_set_height(ui_Button1, lv_pct(16));
    lv_obj_set_x(ui_Button1, lv_pct(-3));
    lv_obj_set_y(ui_Button1, lv_pct(-31));
    lv_obj_set_align(ui_Button1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label1 = lv_label_create(scr1);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 2
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 2
    lv_obj_set_x(ui_Label1, lv_pct(-3));
    lv_obj_set_y(ui_Label1, lv_pct(-30));
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "page 1");
*/
	LV_FONT_DECLARE(lv_font_chinese2_14);
    	//Write codes screen_btn_1
    lv_ui *ui;
	//Write codes screen_1_btn_1
	ui->screen_1_btn_1 = lv_btn_create(scr1);
	ui->screen_1_btn_1_label = lv_label_create(ui->screen_1_btn_1);
	lv_label_set_text(ui->screen_1_btn_1_label, "返回");
	lv_label_set_long_mode(ui->screen_1_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_1_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_1_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_1_btn_1_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_1_btn_1, 79, 232);
	lv_obj_set_size(ui->screen_1_btn_1, 79, 26);

	//Write style for screen_1_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_1_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_1_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_1_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_1_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_1_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_1_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_1_btn_1, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_1_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_1_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);



	lv_obj_add_event_cb(ui->screen_1_btn_1,event_cb1,LV_EVENT_CLICKED,NULL);
	



	slider1 =lv_slider_create(scr1);
    lv_obj_set_size(slider1,160,10);
    lv_obj_align(slider1 ,LV_ALIGN_CENTER,0,-80);
    lv_slider_set_range(slider1,0,300);
    S1 =lv_label_create(scr1);
    lv_label_set_text(S1,"0%");
    lv_obj_align_to(S1,slider1,LV_ALIGN_OUT_RIGHT_MID,10,0);
    // lv_slider_set_mode(slider1,LV_SLIDER_MODE_SYMMETRICAL);

    slider2 =lv_slider_create(scr1);
    lv_obj_set_size(slider2,160,10);
    lv_obj_align(slider2 ,LV_ALIGN_CENTER,0,-50);
    lv_slider_set_range(slider2,0,300);
    S2 =lv_label_create(scr1);
    lv_label_set_text(S2,"0%");
    lv_obj_align_to(S2,slider2,LV_ALIGN_OUT_RIGHT_MID,10,0);
  //   lv_slider_set_mode(slider2,LV_SLIDER_MODE_SYMMETRICAL);

    slider3 =lv_slider_create(scr1);
    lv_obj_set_size(slider3,160,10);
    lv_obj_align(slider3 ,LV_ALIGN_CENTER,0,-20);
    lv_slider_set_range(slider3,0,300);
    S3 =lv_label_create(scr1);
    lv_label_set_text(S3,"0%");
    lv_obj_align_to(S3,slider3,LV_ALIGN_OUT_RIGHT_MID,10,0);

    slider4 =lv_slider_create(scr1);
    lv_obj_set_size(slider4,160,10);
    lv_obj_align(slider4 ,LV_ALIGN_CENTER,0,10);
    lv_slider_set_range(slider4,0,300);
    S4 =lv_label_create(scr1);
    lv_label_set_text(S4,"0%");
    lv_obj_align_to(S4,slider4,LV_ALIGN_OUT_RIGHT_MID,10,0);

    slider5 =lv_slider_create(scr1);
    lv_obj_set_size(slider5,160,10);
    lv_obj_align(slider5 ,LV_ALIGN_CENTER,0,40);
    lv_slider_set_range(slider5,0,300);
    S5 =lv_label_create(scr1);
    lv_label_set_text(S5,"0%");
    lv_obj_align_to(S5,slider5,LV_ALIGN_OUT_RIGHT_MID,10,0);

    slider6 =lv_slider_create(scr1);
    lv_obj_set_size(slider6,160,10);
    lv_obj_align(slider6,LV_ALIGN_CENTER,0,70);
    lv_slider_set_range(slider6,0,300);
    S6 =lv_label_create(scr1);
    lv_label_set_text(S6,"0%");
    lv_obj_align_to(S6,slider6,LV_ALIGN_OUT_RIGHT_MID,10,0);






	lv_obj_t * sw1 = lv_switch_create (scr1);
    lv_obj_center(sw1);
    lv_obj_align(sw1 ,LV_ALIGN_CENTER,-60,-115);
    lv_obj_add_event_cb(sw1,event_cb2,LV_EVENT_VALUE_CHANGED,NULL);

    lv_obj_t *sw1_tab =lv_label_create(scr1);
    lv_label_set_text(sw1_tab,"启动按钮");
    lv_obj_align_to(sw1_tab,sw1,LV_ALIGN_OUT_RIGHT_MID,10,0);
	lv_obj_set_style_text_font(sw1_tab, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);

	lv_group_add_obj(g1, sw1);
	lv_group_add_obj(g1, slider1);
    lv_group_add_obj(g1, slider2);
    lv_group_add_obj(g1, slider3);
    lv_group_add_obj(g1, slider4);
    lv_group_add_obj(g1, slider5);
    lv_group_add_obj(g1, slider6);
    lv_group_add_obj(g1, ui->screen_1_btn_1);

}


void page1_loop(){



    lv_label_set_text_fmt(S1,"%d%%",lv_slider_get_value(slider1));
    lv_label_set_text_fmt(S2,"%d%%",lv_slider_get_value(slider2));
    lv_label_set_text_fmt(S3,"%d%%",lv_slider_get_value(slider3));
    lv_label_set_text_fmt(S4,"%d%%",lv_slider_get_value(slider4));
    lv_label_set_text_fmt(S5,"%d%%",lv_slider_get_value(slider5));
    lv_label_set_text_fmt(S6,"%d%%",lv_slider_get_value(slider6));    


}