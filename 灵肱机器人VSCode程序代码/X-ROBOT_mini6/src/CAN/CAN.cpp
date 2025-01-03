#include "CAN.h"
#include "driver/twai.h"

static const char *TAG = "TWAI_APP";

twai_message_t tx_message, rx_message;

void app_twai_init() 
{
/*============================================ 串口配置 ===========================================*/
        // 初始化串口
    Serial.begin(115200);
    while (!Serial) {}
/*============================================ TWAI通用配置，1M，26、25 ===========================================*/ 
    // 通用配置
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_26, GPIO_NUM_25, TWAI_MODE_NORMAL);
    
    // 时间配置（1 Mbps 波特率）
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_1MBITS();
    
    // 过滤器配置（接受所有消息）
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
/*============================================ TWAI启动和开始及其调试信息 ===========================================*/ 
    // 安装 TWAI 驱动
    if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK) 
    {
        Serial.println("twai driver installed");
    } 
    else 
    {
        Serial.println("failed to install twai driver");
        return;
    }

    // 启动 TWAI 驱动
    if (twai_start() == ESP_OK) 
    {
        Serial.println("twai driver started");
    } 
    else 
    {
        Serial.println("failed to start twai driver");
        return;
    }
}

void app_twai_send(int id, char cmd[], int len)
{
    // 设置发送消息
    tx_message.identifier = id;     // 扩展帧ID (29位)
    tx_message.data_length_code = len;        // 数据长度
    tx_message.flags = TWAI_MSG_FLAG_EXTD;  // 扩展帧标志

    // 通过循环将 str 的元素赋值给 tx_message.data
    for (int i = 0; i < len; i++)
    {
        tx_message.data[i] = cmd[i];
    }

 //   Serial.print("send data: ");  //这段代码调试时可以开启
   // Serial.println(len);          //这段代码调试时可以开启

    

    //Serial.println(tx_message.data);
    

    if (twai_transmit(&tx_message, pdMS_TO_TICKS(1000)) == ESP_OK)
    {
 //       Serial.println("twai send success!");
    }
    else
    {
        Serial.println("twai send failed!");
    }
}

void app_twai_recv()
{
    // 尝试从 CAN 总线上接收一条消息
    if (twai_receive(&rx_message, pdMS_TO_TICKS(100)) == ESP_OK) 
    {




/*
                                                 //这段代码调试时可以开启
        Serial.println("Message received");

        // 处理接收到的消息
        if (rx_message.extd) 
        {
            Serial.println("Message is in Extended Format");
        } 
        else 
        {
            Serial.println("Message is in Standard Format");
        }
        Serial.printf("ID is 0x%lx\n", (unsigned long)rx_message.identifier);

        if (!(rx_message.rtr))  // 如果不是 RTR 帧
        {
            for (int i = 0; i < rx_message.data_length_code; i++) 
            {
                Serial.printf("Data byte %d = 0x%02X\n", i, (unsigned char)rx_message.data[i]);
            }
        }

*/


    } 
    else //接收失败，寻找原因
    {


        

        Serial.println("Failed to receive message");
        // 获取 TWAI 状态信息
        twai_status_info_t status;
        if (twai_get_status_info(&status) == ESP_OK) 
        {
            Serial.printf("TWAI State: %s\n", (status.state == TWAI_STATE_STOPPED) ? "STOPPED" :
                                                (status.state == TWAI_STATE_RUNNING) ? "RUNNING" :
                                                (status.state == TWAI_STATE_BUS_OFF) ? "BUS-OFF" : "RECOVERY");

            Serial.printf("Messages to TX: %lu\n", (unsigned long)status.msgs_to_tx);
            Serial.printf("Messages to RX: %lu\n", (unsigned long)status.msgs_to_rx);
            Serial.printf("TX Error Counter: %lu\n", (unsigned long)status.tx_error_counter);
            Serial.printf("RX Error Counter: %lu\n", (unsigned long)status.rx_error_counter);
            Serial.printf("TX Failed Count: %lu\n", (unsigned long)status.tx_failed_count);
            Serial.printf("RX Missed Count: %lu\n", (unsigned long)status.rx_missed_count);
            Serial.printf("RX Overrun Count: %lu\n", (unsigned long)status.rx_overrun_count);
            Serial.printf("Arbitration Lost Count: %lu\n", (unsigned long)status.arb_lost_count);
            Serial.printf("Bus Error Count: %lu\n", (unsigned long)status.bus_error_count);
        } 
        else 
        {
            Serial.println("Failed to get TWAI status information");
        }

      
        

    }
}

CAN0::CAN0(uint8_t ID) : address(ID) 
{}

void CAN0::enable(uint8_t enable, uint8_t common) 
{  
    char data[] = {0Xf3,0XAB,enable,common,0X6B};
    app_twai_send(address<<8, data, sizeof(data));   
}

void CAN0::speed_mode(uint8_t dir, uint16_t acceleration, uint16_t speed, uint8_t common) 
{
    char data[] = {0XF6,dir,(acceleration >> 8) & 0xFF, acceleration & 0xFF, (speed >> 8) & 0xFF, speed & 0xFF, common, 0X6B};
    app_twai_send(address<<8, data, sizeof(data));   
}

void CAN0::location_trapezoidal_mode(bool dir, uint16_t acceleration, uint16_t deceleration, 
                                      uint16_t max_speed, int32_t location, uint8_t mode, uint8_t common) 
{

    if(location<0){
        dir=!dir;
        location=-location;
    }
    
    char txCmd1[] = {
        0XFD, dir, (acceleration >> 8) & 0xFF, acceleration & 0xFF, 
        (deceleration >> 8) & 0xFF, deceleration & 0xFF, 
        (max_speed >> 8) & 0xFF, max_speed & 0xFF
    };

    char txCmd2[] = {
        0XFD, (location >> 24) & 0xFF, (location >> 16) & 0xFF, 
        (location >> 8) & 0xFF, location & 0xFF, 
        mode, common, 0X6B
    };
 
    app_twai_send(address<<8 | 0x00, txCmd1, sizeof(txCmd1));
    app_twai_send(address<<8 | 0x01, txCmd2, sizeof(txCmd2)); 
        

}
/*
int32_t CAN0::location_read() 
{
    char data[] = {0x36,0X6B};
    app_twai_send(address<<8 | 0x00, data, sizeof(data));
    app_twai_recv();

    if (rx_message.data[rx_message.data_length_code - 1] == 0x6B) 
    {
        if (rx_message.data[1] == 0x00) 
        {
            return ((int32_t)rx_message.data[3] << 16) | 
                   ((int32_t)rx_message.data[4] << 8) | 
                   (int32_t)rx_message.data[5];
        } 
        else 
        {
            return -(((int32_t)rx_message.data[3] << 16) | 
                      ((int32_t)rx_message.data[4] << 8) | 
                      (int32_t)rx_message.data[5]);
        }
    } 
    else 
    {
        return -1;
    }
    
}

*/


 /*
    char data[] = {0x36,0X6B};
    app_twai_send(address<<8 | 0x00, data, sizeof(data));  
    if (twai_receive(&rx_message, pdMS_TO_TICKS(1)) != ESP_OK) 
    {
         return -2;
    }

    app_twai_send(address<<8 | 0x00, data, sizeof(data));
    if (twai_receive(&rx_message, pdMS_TO_TICKS(3)) != ESP_OK) 
    {
         return -2;
    }

*/

int32_t CAN0::location_read() 
{
       do
    {  
    
    char data[] = {0x36,0X6B};
    app_twai_send(address<<8 | 0x00, data, sizeof(data));

    if (twai_receive(&rx_message, pdMS_TO_TICKS(5)) != ESP_OK) 
    return -2;
    } while (rx_message.identifier != address<<8 | 0x00);//确保数据没有乱窜
  //  }while (rx_message.data[rx_message.data_length_code - 1] == 0x6B && rx_message.identifier != (address << 8));
    //常规处理
    if (rx_message.data[rx_message.data_length_code - 1] == 0x6B) 
    {
        int32_t result = 0;
        if (rx_message.data[1] == 0x00) 
        {
            result =  ((int32_t)rx_message.data[3] << 16) | 
                ((int32_t)rx_message.data[4] << 8) | 
                (int32_t)rx_message.data[5];
        } 
        else 
        {
            result =  -(((int32_t)rx_message.data[3] << 16) | 
                    ((int32_t)rx_message.data[4] << 8) | 
                    (int32_t)rx_message.data[5]);
        }
        memset(rx_message.data, 0, sizeof(rx_message.data));
        return result;
    } 
    else 
    {
        return -1;
    }
}


void CAN0::location_read_send()
{




   char data[] = {0x36,0X6B};
    app_twai_send(address<<8 | 0x00, data, sizeof(data));





}



// int32_t CAN0::location_read() 
// {
//     int i = 0;
//     uint8_t rxCmd[128] = {0};
//     uint8_t rxCount = 0;

//     uint32_t address_1 = ((int32_t)0x00 << 24) |
//                          ((int32_t)0x00 << 16) |
//                          ((int32_t)address << 8) | 
//                          (int32_t)0x00;

//     CAN.beginExtendedPacket(address_1); 
//     CAN.write(0x36);
//     CAN.write(0x6B);
//     CAN.endPacket();
//     delayMicroseconds(180);

//     if (CAN.parsePacket()) 
//     { 
//         while (CAN.available()) 
//         {
//             rxCmd[i++] = CAN.read(); 
//         }
//         rxCount = i;
//     }

//     if (rxCmd[rxCount - 1] == 0x6B) 
//     {
//         if (rxCmd[1] == 0x00) 
//         {
//             return ((int32_t)rxCmd[3] << 16) | 
//                    ((int32_t)rxCmd[4] << 8) | 
//                    (int32_t)rxCmd[5];
//         } 
//         else 
//         {
//             return -(((int32_t)rxCmd[3] << 16) | 
//                       ((int32_t)rxCmd[4] << 8) | 
//                       (int32_t)rxCmd[5]);
//         }
//     } 
//     else 
//     {
//         return -1;
//     }
    
//     delay(10);
// }