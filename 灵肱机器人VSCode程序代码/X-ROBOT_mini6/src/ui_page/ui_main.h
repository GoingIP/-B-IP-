#ifndef UI_MAIN_H
#define UI_MAIN_H
#include <lvgl.h>






extern lv_obj_t * scr0;
extern lv_obj_t * scr1;
extern lv_obj_t * scr2;
extern lv_obj_t * scr3;
extern lv_obj_t * scr4;
extern lv_group_t * g0;
extern lv_group_t * g1;
extern lv_group_t * g2;
extern lv_group_t * g3;
extern lv_group_t * g4;
extern lv_indev_t * enc_indev;

void test1();
void ui_main_init();
void ui_main_loop();




static void event_cb2(lv_event_t *e);








#endif 