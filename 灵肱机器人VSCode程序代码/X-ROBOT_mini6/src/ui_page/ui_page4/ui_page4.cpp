#include <Arduino.h>
#include "ui_page4.h"
#include "ui_main.h"
#include <SPI.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include "demos\lv_demos.h"
#include "driver/pcnt.h"
#include "lvgl_all.h"

typedef struct
{
	bool screen_4_del;
	lv_obj_t *screen_4_btn_1;
	lv_obj_t *screen_4_btn_1_label;
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




void page4_init(){

    
    LV_FONT_DECLARE(lv_font_chinese2_14);
    	//Write codes screen_btn_1
    lv_ui *ui;
	//Write codes screen_4_btn_1
	ui->screen_4_btn_1 = lv_btn_create(scr4);
	ui->screen_4_btn_1_label = lv_label_create(ui->screen_4_btn_1);
	lv_label_set_text(ui->screen_4_btn_1_label, "返回");
	lv_label_set_long_mode(ui->screen_4_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_4_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_4_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_4_btn_1_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_4_btn_1, 79, 232);
	lv_obj_set_size(ui->screen_4_btn_1, 79, 26);

	//Write style for screen_4_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_4_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_4_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_4_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_4_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_4_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_4_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_4_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_4_btn_1, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_4_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_4_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);



	lv_obj_add_event_cb(ui->screen_4_btn_1,event_cb1,LV_EVENT_CLICKED,NULL);
    lv_group_add_obj(g4, ui->screen_4_btn_1);





}
