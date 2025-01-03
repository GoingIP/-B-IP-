#ifndef TASK_H
#define TASK_H





void RGB_task(void *pvParams);

void ROBOT_loction_task(void *pvParams);
void esp_now_task(void *pvParams);
void esp_now_task_show();
void ROBOT_record_enable_task();
void ROBOT_record_disable_task();
void ROBOT_replay_enable_task(uint8_t time);
void ROBOT_replay_disable_task();
void ROBOT_replay_delete_task();
#endif 