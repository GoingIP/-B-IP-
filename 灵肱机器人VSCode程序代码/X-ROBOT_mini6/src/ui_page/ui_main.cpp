#include <Arduino.h>
#include "ui_main.h"
#include <SPI.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include "demos\lv_demos.h"
#include "driver/pcnt.h"
#include "lvgl_all.h"
#include "ui_page1.h"
#include "ui_page2.h"
#include "ui_page3.h"
#include "ui_page4.h"


lv_obj_t * scr0;
lv_obj_t * scr1;
lv_obj_t * scr2;
lv_obj_t * scr3;
lv_obj_t * scr4;
lv_group_t * g0;
lv_group_t * g1;
lv_group_t * g2;
lv_group_t * g3;
lv_group_t * g4;
lv_indev_t * enc_indev;

typedef struct
{
  
	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *screen_btn_1;
	lv_obj_t *screen_btn_1_label;
	lv_obj_t *screen_btn_2;
	lv_obj_t *screen_btn_2_label;
	lv_obj_t *screen_btn_3;
	lv_obj_t *screen_btn_3_label;
	lv_obj_t *screen_btn_4;
	lv_obj_t *screen_btn_4_label;
	lv_obj_t *screen_1;
}lv_ui;







void test1(){

    static lv_indev_drv_t indev_drv; 
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = encoder_read;
    lv_indev_t * enc_indev = lv_indev_drv_register(&indev_drv);
    lv_obj_t * scr = lv_disp_get_scr_act(NULL); 


    lv_obj_t *dd1 =lv_dropdown_create(scr);
    lv_dropdown_set_options(dd1,"a\nb\nc\nd\ne\nf\n1\n2\n3\n4\n5");
    lv_obj_align(dd1 ,LV_ALIGN_CENTER,0,-80);

    lv_obj_t *dd2 =lv_dropdown_create(scr);
    lv_dropdown_set_options(dd2,"a\nb\nc\nd\ne\nf\n1\n2\n3\n4\n5");
    lv_obj_align(dd2 ,LV_ALIGN_CENTER,0,-40);  

    lv_obj_t *dd3 =lv_dropdown_create(scr);
    lv_dropdown_set_options(dd3,"a\nb\nc\nd\ne\nf\n1\n2\n3\n4\n5");
    lv_obj_align(dd3 ,LV_ALIGN_CENTER,0,0);

    lv_group_t * g = lv_group_create();
    lv_group_add_obj(g, dd1);
    lv_group_add_obj(g, dd2);
    lv_group_add_obj(g, dd3);
    lv_indev_set_group(enc_indev, g);

}












static void event_cb1(lv_event_t *e){

   lv_event_code_t code =lv_event_get_code(e);
   lv_obj_t * sw= lv_event_get_target(e);
   if(code==LV_EVENT_CLICKED){

        lv_scr_load(scr1);
        lv_indev_set_group(enc_indev, g1);
        if(lv_obj_has_state(sw,LV_STATE_CHECKED)){
    
        }else{

        }
   }


}


static void event_cb2(lv_event_t *e){

   lv_event_code_t code =lv_event_get_code(e);
   lv_obj_t * sw= lv_event_get_target(e);
   if(code==LV_EVENT_CLICKED){

        lv_scr_load(scr2);
        lv_indev_set_group(enc_indev, g2);
        if(lv_obj_has_state(sw,LV_STATE_CHECKED)){

        }else{

        }
   }


}




static void event_cb3(lv_event_t *e){

   lv_event_code_t code =lv_event_get_code(e);
   lv_obj_t * sw= lv_event_get_target(e);
   if(code==LV_EVENT_CLICKED){

        lv_scr_load(scr3);
        lv_indev_set_group(enc_indev, g3);
        if(lv_obj_has_state(sw,LV_STATE_CHECKED)){
    
        }else{

        }
   }


}


static void event_cb4(lv_event_t *e){

   lv_event_code_t code =lv_event_get_code(e);
   lv_obj_t * sw= lv_event_get_target(e);
   if(code==LV_EVENT_CLICKED){

        lv_scr_load(scr4);
        lv_indev_set_group(enc_indev, g4);
        if(lv_obj_has_state(sw,LV_STATE_CHECKED)){

        }else{

        }
   }


}





void ui_main_init()
{

    static lv_indev_drv_t indev_drv; 
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = encoder_read;
    enc_indev = lv_indev_drv_register(&indev_drv);

    scr0 = lv_obj_create(NULL);
    scr1 = lv_obj_create(NULL);
    scr2 = lv_obj_create(NULL);
    scr3 = lv_obj_create(NULL);
    scr4 = lv_obj_create(NULL);

    g0 = lv_group_create();
    g1 = lv_group_create();
    g2 = lv_group_create();
    g3 = lv_group_create();
    g4 = lv_group_create();

   LV_FONT_DECLARE(lv_font_chinese2_14);
   lv_ui * ui;
	ui->screen_btn_1 = lv_btn_create(scr0);
	ui->screen_btn_1_label = lv_label_create(ui->screen_btn_1);
	lv_label_set_text(ui->screen_btn_1_label, "电机位置实时调试");
	lv_label_set_long_mode(ui->screen_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_btn_1_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_btn_1, 37, 79);
	lv_obj_set_size(ui->screen_btn_1, 174, 33);

 

	//Write style for screen_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_1, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_btn_2
	ui->screen_btn_2 = lv_btn_create(scr0);
	ui->screen_btn_2_label = lv_label_create(ui->screen_btn_2);
	lv_label_set_text(ui->screen_btn_2_label, "机器人拖动示教");
	lv_label_set_long_mode(ui->screen_btn_2_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_btn_2_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_btn_2_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_btn_2, 37, 123);
	lv_obj_set_size(ui->screen_btn_2, 174, 33);

	//Write style for screen_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btn_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_2, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

   

	//Write codes screen_btn_3
	ui->screen_btn_3 = lv_btn_create(scr0);
	ui->screen_btn_3_label = lv_label_create(ui->screen_btn_3);
	lv_label_set_text(ui->screen_btn_3_label, "机器人追踪器示教");
	lv_label_set_long_mode(ui->screen_btn_3_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_btn_3_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_btn_3, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_btn_3_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_btn_3, 37, 168);
	lv_obj_set_size(ui->screen_btn_3, 174, 33);

	//Write style for screen_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btn_3, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_3, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);



  

	//Write codes screen_btn_4
	ui->screen_btn_4 = lv_btn_create(scr0);
	ui->screen_btn_4_label = lv_label_create(ui->screen_btn_4);
	lv_label_set_text(ui->screen_btn_4_label, "设置");
	lv_label_set_long_mode(ui->screen_btn_4_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_btn_4_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_btn_4, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_btn_4_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_btn_4, 37, 212);
	lv_obj_set_size(ui->screen_btn_4, 174, 33);

	//Write style for screen_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btn_4, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_btn_4, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_4, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

   

   lv_obj_t *text1 =lv_label_create(scr0);
   lv_obj_set_style_text_font(text1, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);
   lv_label_set_text(text1,"灵肱机器人操作系统");
   lv_obj_align(text1,LV_ALIGN_CENTER,0,-100);

   lv_obj_t *text2 =lv_label_create(scr0);
   lv_obj_set_style_text_font(text2, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);
   lv_label_set_text(text2,"B站行走的IP");
   lv_obj_align(text2,LV_ALIGN_CENTER,0,120);

    



   lv_obj_add_event_cb(ui->screen_btn_1,event_cb1,LV_EVENT_CLICKED,NULL);
   lv_obj_add_event_cb(ui->screen_btn_2,event_cb2,LV_EVENT_CLICKED,NULL);
   lv_obj_add_event_cb(ui->screen_btn_3,event_cb3,LV_EVENT_CLICKED,NULL);
   lv_obj_add_event_cb(ui->screen_btn_4,event_cb4,LV_EVENT_CLICKED,NULL);
   

    lv_group_add_obj(g0, ui->screen_btn_1);
    lv_group_add_obj(g0, ui->screen_btn_2);
    lv_group_add_obj(g0, ui->screen_btn_3);
    lv_group_add_obj(g0, ui->screen_btn_4);

    page1_init();
    page2_init();
    page3_init();
    page4_init();


    lv_indev_set_group(enc_indev, g0);
    lv_scr_load(scr0);


}


void ui_main_loop(){



 page1_loop();
 page2_loop();
 page3_loop();
 
}



