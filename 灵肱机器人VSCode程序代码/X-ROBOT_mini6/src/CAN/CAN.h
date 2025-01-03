#ifndef CAN_H
#define CAN_H

#include "Arduino.h"
#include "string.h"
class CAN0 
{
    public:
        CAN0(uint8_t ID);
        void enable(uint8_t enable,uint8_t common);
        void zeroing(uint8_t mode,uint8_t common);
        void stop(uint8_t common);
        void speed_mode(uint8_t dir,uint16_t acceleration,uint16_t speed,uint8_t common);
        void force_mode(uint8_t dir,uint16_t accelerated_force,uint16_t force,uint8_t common);
        void location_trapezoidal_mode(bool dir,uint16_t acceleration,uint16_t deceleration,uint16_t max_speed,int32_t location,uint8_t mode,uint8_t common);
        int32_t location_read();
        void location_read_send();
        
    private:
        uint8_t address;     //地址
        uint8_t txCmd1[128];    //分数据1
        uint8_t txCmd2[128];     //分数据2
        uint32_t address_1;    //分地址1
        uint32_t address_2;     //分地址2
        uint8_t rxCmd[128] = {0};  //接收数组
        uint8_t rxCount = 0;     //接收长度
};

void app_twai_init();
void app_twai_send(int id, char cmd[], int len);
void app_twai_recv();
#endif 