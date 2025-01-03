#include <Arduino.h>
#include "ui_page2.h"
#include "ui_main.h"
#include <SPI.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include "demos\lv_demos.h"
#include "driver/pcnt.h"
#include "lvgl_all.h"
#include "task.h"

#include "SD.h"

lv_obj_t *sw1_tab;
lv_obj_t *sw2_tab;
lv_obj_t * sw1;
lv_obj_t * sw2;

lv_obj_t* list;


lv_obj_t * slider1_scr2;
lv_obj_t * S1_scr2;
lv_obj_t * S2_scr2;
typedef struct
{	
	lv_obj_t *screen_2;
	bool screen_2_del;
	lv_obj_t *screen_2_btn_1;
	lv_obj_t *screen_2_btn_1_label;
	lv_obj_t *screen_2_btn_2;
	lv_obj_t *screen_2_btn_2_label;
	
}lv_ui;

static File myFile;
const int CS = 15;
extern String mid_file;

void btn_event_handler(lv_event_t * e) {
    lv_obj_t *btn = lv_event_get_target(e);
    const char *file_name = lv_list_get_btn_text(list,btn); // 获取按钮文本即文件名
    Serial.printf("file_name:");
    Serial.println(String('/') + file_name);
    mid_file= String('/') + file_name;

  
}

uint8_t ListFiles(const char* dirPath, lv_obj_t **btn_all, lv_obj_t *list) {
    lv_obj_clean(list);
    File root = SD.open(dirPath);
    if (!root) {
        Serial.println("Failed to open directory");
        return 0;
    }

    if (!root.isDirectory()) {
        Serial.println("Not a directory");
        return 0;
    }

    uint8_t count = 0; // 初始化计数器
    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            // 处理目录（如果需要）
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());

            // 创建列表项按钮并存储在数组中
            btn_all[count] = lv_list_add_btn(list, LV_SYMBOL_FILE, file.name());
            lv_group_add_obj(g2, btn_all[count]);
            // 添加按钮事件回调
            lv_obj_add_event_cb(btn_all[count], btn_event_handler, LV_EVENT_CLICKED, NULL);
            count++;

            // 如果已经找到 100 个文件，退出循环
            if (count > 99) { // 因为索引从 0 开始，所以这里是 99 而不是 100
                break;
            }
        }
        file = root.openNextFile();
    }
    root.close(); // 关闭根目录
    return count;
}



static void event_cb1(lv_event_t *e){

   lv_event_code_t code =lv_event_get_code(e);
   if(code==LV_EVENT_CLICKED){

       
        
     lv_scr_load(scr0);
     lv_indev_set_group(enc_indev, g0);

       
   }


}

static void event_cb2(lv_event_t *e){

   lv_event_code_t code =lv_event_get_code(e);
   lv_obj_t * s= lv_event_get_target(e);
   if(code==LV_EVENT_VALUE_CHANGED){
        if(lv_obj_has_state(s,LV_STATE_CHECKED)){
            lv_label_set_text(sw1_tab,"结束录制并保存");
     
        }else{
            lv_label_set_text(sw1_tab,"录制下一个动作");
            page2_init_update();
        }
   }


}
static void event_cb3(lv_event_t *e){

   lv_event_code_t code =lv_event_get_code(e);
   lv_obj_t * s= lv_event_get_target(e);
   if(code==LV_EVENT_VALUE_CHANGED){
        if(lv_obj_has_state(s,LV_STATE_CHECKED)){
            lv_label_set_text(sw2_tab,"终止播放");
     
        }else{
            lv_label_set_text(sw2_tab,"再播一遍");
 
        }
   }

}


static void event_cb4(lv_event_t *e){

   lv_event_code_t code =lv_event_get_code(e);
   if(code==LV_EVENT_CLICKED){
		ROBOT_replay_delete_task() ;
        page2_init_update();
   }
}



void page2_init(){

     
    
	LV_FONT_DECLARE(lv_font_chinese2_14);
	lv_obj_t * tabview = lv_tabview_create(scr2,LV_DIR_TOP,50);

    lv_obj_t * tab1 = lv_tabview_add_tab(tabview,"动作录制");
	 
	//  lv_obj_add_style(tab1,&tab_style, LV_PART_MAIN|LV_STATE_DEFAULT);
      lv_obj_t * tab2 = lv_tabview_add_tab(tabview,"动作播放");
    lv_obj_set_style_text_font(tabview, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);
      lv_tabview_set_act(tabview,1,LV_ANIM_OFF);



    	//Write codes screen_btn_1
    lv_ui *ui;
	//Write codes screen_2_btn_1
	ui->screen_2_btn_1 = lv_btn_create(tab1);
	ui->screen_2_btn_1_label = lv_label_create(ui->screen_2_btn_1);
	lv_label_set_text(ui->screen_2_btn_1_label, "返回");
	lv_label_set_long_mode(ui->screen_2_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_2_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_2_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_2_btn_1_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_2_btn_1, 79, 170);
	lv_obj_set_size(ui->screen_2_btn_1, 79, 26);

	//Write style for screen_2_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_2_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_2_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_2_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_2_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_2_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_2_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_2_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_2_btn_1, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_2_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_2_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);



	


	//Write codes screen_2_btn_2
	ui->screen_2_btn_2 = lv_btn_create(tab2);
	ui->screen_2_btn_2_label = lv_label_create(ui->screen_2_btn_2);
	lv_label_set_text(ui->screen_2_btn_2_label, "删除动作");
	lv_label_set_long_mode(ui->screen_2_btn_2_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_2_btn_2_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_2_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_2_btn_2_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_2_btn_2, 138, 2);
	lv_obj_set_size(ui->screen_2_btn_2, 83, 32);

	//Write style for screen_2_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_2_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_2_btn_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_2_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_2_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_2_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_2_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_2_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_2_btn_2, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_2_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_2_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);



	sw1 = lv_switch_create (tab1);
    lv_obj_center(sw1);
    lv_obj_align(sw1 ,LV_ALIGN_CENTER,-80,-85);
    lv_obj_add_event_cb(sw1,event_cb2,LV_EVENT_VALUE_CHANGED,NULL);

    sw1_tab =lv_label_create(tab1);
    lv_label_set_text(sw1_tab,"录制动作");
    lv_obj_align_to(sw1_tab,sw1,LV_ALIGN_OUT_RIGHT_MID,10,0);
	lv_obj_set_style_text_font(sw1_tab, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);


	sw2 = lv_switch_create (tab2);
    lv_obj_center(sw2);
    lv_obj_align(sw2 ,LV_ALIGN_CENTER,-80,-85);
    lv_obj_add_event_cb(sw2,event_cb3,LV_EVENT_VALUE_CHANGED,NULL);

    sw2_tab =lv_label_create(tab2);
    lv_label_set_text(sw2_tab,"播放动作");
    lv_obj_align_to(sw2_tab,sw2,LV_ALIGN_OUT_RIGHT_MID,10,0);
	lv_obj_set_style_text_font(sw2_tab, &lv_font_chinese2_14, LV_PART_MAIN|LV_STATE_DEFAULT);



	list  =  lv_list_create(tab2);
    lv_obj_set_size(list, 200,120);

    lv_obj_center(list);
    lv_list_add_text(list,"SD card");       
	lv_obj_set_style_text_font(list, &lv_font_montserrat_14,0);
    
    //delay(5000);//调试用的，记得删了



    slider1_scr2 =lv_slider_create(tab2);
    lv_obj_set_size(slider1_scr2,120,10);
    lv_obj_align(slider1_scr2,LV_ALIGN_CENTER,0,80);
    lv_slider_set_range(slider1_scr2,0,10);
    S1_scr2 =lv_label_create(tab2);
    lv_label_set_text(S1_scr2,"慢");
    lv_obj_align_to(S1_scr2,slider1_scr2,LV_ALIGN_OUT_RIGHT_MID,20,0);
	S2_scr2 =lv_label_create(tab2);
    lv_label_set_text(S2_scr2,"快");
    lv_obj_align_to(S2_scr2,slider1_scr2,LV_ALIGN_OUT_LEFT_MID,-20,0);


    lv_group_add_obj(g2, sw1);
	lv_group_add_obj(g2, ui->screen_2_btn_1);
	lv_group_add_obj(g2, sw2);
	lv_group_add_obj(g2, ui->screen_2_btn_2);



  
    

     page2_init_update();



    // for(uint8_t i = 0; i > btn_count; i++)
    // {
    //     lv_group_add_obj(g2, btn_all[i]);
    // }
	// lv_group_add_obj(g2, btn_all[0]);
	// lv_group_add_obj(g2, btn_all[1]);
 	// lv_group_add_obj(g2, btn_all[2]);
	// lv_group_add_obj(g2, btn_all[3]);
	// lv_group_add_obj(g2, btn_all[4]);
	lv_group_add_obj(g2, slider1_scr2);

	lv_obj_add_event_cb(ui->screen_2_btn_1,event_cb1,LV_EVENT_CLICKED,NULL);
	lv_obj_add_event_cb(ui->screen_2_btn_2,event_cb4,LV_EVENT_CLICKED,NULL);




}



void page2_init_update(){


  lv_obj_t *btn_all[100];
    SD.begin(CS);
    uint8_t btn_count = ListFiles("/",btn_all,list);
    Serial.print("btn_count:");
    Serial.println(btn_count);


}





void page2_loop(){




    lv_state_t state1 = lv_obj_get_state(sw1);
    if( state1  &   LV_STATE_CHECKED){

      ROBOT_record_enable_task();
 

      }else{
      ROBOT_record_disable_task();
       
      }


	lv_state_t state2 = lv_obj_get_state(sw2);
    if( state2  &   LV_STATE_CHECKED){

      ROBOT_replay_enable_task(2+ lv_slider_get_value(slider1_scr2));
 
	
      }else{
      ROBOT_replay_disable_task();
       
      }


}