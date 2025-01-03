#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "RGB.h"
#include "task.h"
/////////////////////////////////////////////////////////////////LVGL必加库
#include <SPI.h>
#include <TFT_eSPI.h>
#include "demos\lv_demos.h"
#include "lvgl_all.h"
/////////////////////////////////////////////////////////////////CAN通信必加库
#include "CAN.h"
///////////////////////////////////////////////////////////
#include "ui_page1.h"
/////////////////////////////////////////////////////////////////SD卡
#include "SD.h"
#include <ArduinoJson.h>
//////////////////////////////////////////////////////////////

#include <esp_now.h>
#include <WiFi.h>
////////////////////////////
#include "ui_page3.h"
////////////////////////////////////////
#include <ArduinoEigen.h>
#include <ArduinoEigenDense.h>
#include <ArduinoEigenSparse.h>
//#include <Eigen/Geometry>

CAN0 J1(1);
CAN0 J2(2);
CAN0 J3(3);
CAN0 J4(4);
CAN0 J5(5);
CAN0 J6(6);

File myFile;
bool recording =0; 
bool replaying =0;
 String mid_file;
extern lv_group_t* g2;
extern lv_obj_t* list;




 float pitch,roll,yaw;
   float Q=0;



// 创建一个结构体接收数据
typedef struct struct_message {
    char a[10];
    int id;
    float Q[3];
    float b;
    float c;
    float d;
    
} struct_message;


// 创建一个结构体变量
struct_message myData;

struct_message Data[5];









void RGB_task(void *pvParams)
{

    while(1){

        greed();
        vTaskDelay(1500 / portTICK_PERIOD_MS);
        red();
        vTaskDelay(1500 / portTICK_PERIOD_MS);
        greed();
    
    }
   
}

void ROBOT_loction_task(void *pvParams)
{



      J1.enable(1,0);
      J2.enable(1,0);   
      J3.enable(1,0);
      J4.enable(1,0);
      J5.enable(1,0);   
      J6.enable(1,0);
    while(1){

      
    

    J1.location_trapezoidal_mode(1,5000,500,5000,lv_slider_get_value(slider1)*10*60,1,0);
    J2.location_trapezoidal_mode(1,5000,500,5000,lv_slider_get_value(slider2)*10*60,1,0);
    J3.location_trapezoidal_mode(0,5000,500,5000,lv_slider_get_value(slider3)*10*60,1,0);
    J4.location_trapezoidal_mode(0,5000,500,5000,lv_slider_get_value(slider4)*10*60,1,0);
    J5.location_trapezoidal_mode(0,5000,500,5000,lv_slider_get_value(slider5)*10*60,1,0);
    J6.location_trapezoidal_mode(0,5000,500,5000,lv_slider_get_value(slider6)*10*60,1,0);



    
    }
   
}

// callback when data is recv from Master
static void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  memcpy(&myData, data, sizeof(myData));
  if(myData.id==1){
   Data[1].b=myData.b;
   Data[1].c= myData.c;
   Data[1].d=myData.d;
  }
    if(myData.id==2){
   Data[2].b=myData.b;
   Data[2].c= myData.c;
   Data[2].d=myData.d;

   Data[2].Q[0]=myData.Q[0];
   Data[2].Q[1]=myData.Q[1];
   Data[2].Q[2]=myData.Q[2];
   Data[2].Q[3]=myData.Q[3];
  }
 // char macStr[18];
//  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
    //       mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    
     
}

Eigen::Quaternionf q1(1,0,0,0);
Eigen::Quaternionf q2(0,0,1,0);
Eigen::Quaternionf q3(sqrt(2)/2,sqrt(2)/2,0,0);
Eigen::Quaternionf q4;
Eigen::Vector3f euler ;

float X,Y,Z,Q1,Q2;
void esp_now_task(void *pvParams)
{

   

      
    WiFi.softAP("Slave_1", "Slave_1_Password", 1, 0);
    WiFi.disconnect();
    esp_now_init();
    esp_now_register_recv_cb(OnDataRecv);
   while (1)
   {
     q1.coeffs()<< Data[2].Q[1],Data[2].Q[2],Data[2].Q[3],Data[2].Q[0];
     X = 25*(1-2*q1.x()*q1.x()-2*q1.z()*q1.z());
     Y =25*(2*q1.x()*q1.y()-2*q1.z()*q1.w());    
     Z =25*(2*q1.y()*q1.z()+2*q1.x()*q1.w());
     Q1=  atan2(X,-Z)*(180.0/M_PI);
     Q2=  atan2(Y,sqrt(X*X+Z*Z))*(180.0/M_PI);
    J1.location_trapezoidal_mode(1,6000,1000,6000,Q1*10*50,1,0);
    J2.location_trapezoidal_mode(1,6000,2000,6000,Q2*10*50,1,0);
    //J3.location_trapezoidal_mode(0,20000,2000,20000,Data[2].b*10*30,1,0);
  //  J4.location_trapezoidal_mode(0,20000,2000,20000,Data[2].c*10*30,1,0);
   }
   
}





void esp_now_task_show()
{

  
  // q4=q1*q2*q3;
   //euler=q4.toRotationMatrix().eulerAngles(2,1,0);
    char buf[32];
    snprintf(buf,sizeof(buf),"J1:%.2f",Q1);
    lv_label_set_text_fmt(text1_3,buf);
    snprintf(buf,sizeof(buf),"J2:%.2f",Q2);
    lv_label_set_text_fmt(text2_3,buf);
    snprintf(buf,sizeof(buf),"J3:%.4f",q1.x());
    lv_label_set_text_fmt(text3_3,buf);
   // snprintf(buf,sizeof(buf),"J4:%.4f",q1.z());
  //  lv_label_set_text_fmt(text4_3,buf);
   
    
   
}


void ROBOT_record_enable_task()
{


      if(!recording){





      /* int fileNumber =  1;
        String fileName;
        while(1){
            fileName = "/test"+String(fileNumber)+".txt";
            if(!SD.exists(fileName.c_str())){
                break;
            }
            fileNumber++;
        }
        
         myFile =SD.open(fileName.c_str(),FILE_APPEND);
            */ 
          File rootDir = SD.open("/"); // 打开SD卡根目录
          if (!rootDir) {
              Serial.println("无法打开SD卡根目录！");
              return; // 如果无法打开，返回
          }

          int fileNumber = 1;
          String fileName;

          while (1) {
              fileName = "/test" + String(fileNumber) + ".txt"; // 创建文件名
              if (!SD.exists(fileName.c_str())) { // 检查文件是否存在
                  break; // 如果文件不存在，跳出循环
              }
              fileNumber++; // 文件已存在，尝试下一个数字
          }
          mid_file = fileName.c_str();
          myFile = SD.open(mid_file, FILE_APPEND); // 打开找到的文件，并以追加方式写入
          if (!myFile) {
              Serial.println("无法打开文件进行写入！");
              return; // 如果无法打开文件，返回
          }

          recording = 1; // 设置录音状态为1
          red(); // 调用red函数（假设用于指示录音开始）
          J1.enable(0, 0); // 启动J1电机
          J2.enable(0, 0); // 启动J2电机
          J3.enable(0, 0); // 启动J3电机
          J4.enable(0, 0); // 启动J4电机
          J5.enable(0, 0); // 启动J5电机
          J6.enable(0, 0); // 启动J5电机

          rootDir.close(); // 关闭根目录的文件句柄（可选，通常不是必须的）
      }

         StaticJsonDocument<200> doc;

         doc["J1"]=J1.location_read();
         doc["J2"]=J2.location_read();
         doc["J3"]=J3.location_read();
         doc["J4"]=J4.location_read();
         doc["J5"]=J5.location_read();
         doc["J6"]=J6.location_read();
      //     doc["J7"]=J3.location_read();
      //   doc["J8"]=J4.location_read();
       //  doc["J9"]=J5.location_read();
        //  doc["J10"]=J6.location_read();
         // work();
         // doc["work"]=working;
          serializeJson(doc,myFile);
          myFile.println();
    
   
}






void ROBOT_record_disable_task(){



  if(recording){
           myFile.close();
           greed();
           recording=0; 
        }

}


void ROBOT_replay_enable_task(uint8_t time){


   if(!replaying){
        myFile = SD.open(mid_file, FILE_READ);
        replaying=1;
        J1.enable(1,0);
        J2.enable(1,0);
        J3.enable(1,0);
        J4.enable(1,0);
        J5.enable(1,0);
        J6.enable(1,0);
        red();
    }



        
    if (myFile.available()) {

        
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, myFile);
        if (error){
        //  Serial.print("deserializeJson() 失败: ");
        //  Serial.println(error.c_str());
        return; 
        } 
        int32_t j1Pos = doc["J1"];
        int32_t j2Pos = doc["J2"]; 
        int32_t j3Pos = doc["J3"];
        int32_t j4Pos = doc["J4"];
        int32_t j5Pos = doc["J5"];
        int32_t j6Pos = doc["J6"];
        /* bool worked =   doc["work"];


        if(worked==0){
        myservo1.write(120); 
        myservo2.write(10);
        }

        if(worked==1){
        myservo1.write(10); 
        myservo2.write(120); 
        }
        */

        


        //work_run();


            
        
        
        
        // 将字符串转换为数值 // 控制电机 
        J1.location_trapezoidal_mode(0,20000,4000,20000,j1Pos,1,0);
        J2.location_trapezoidal_mode(0,20000,4000,20000,j2Pos,1,0);
        J3.location_trapezoidal_mode(0,20000,4000,20000,j3Pos,1,0);
        J4.location_trapezoidal_mode(0,20000,4000,20000,j4Pos,1,0);
        J5.location_trapezoidal_mode(0,20000,4000,20000,j5Pos,1,0);
        J6.location_trapezoidal_mode(0,20000,4000,20000,j6Pos,1,0);

        // 每秒执行一次 
        delay(time);


    }




}





void ROBOT_replay_disable_task(){


    if(replaying){
    // oled.println("ON4");
        myFile.close();
        replaying =0;

        greed();
        
    
    }




}


void ROBOT_replay_delete_task(){


 

   // myFile = SD.open("mid_file", FILE_WRITE);
   // if(myFile){

      //  myFile.close();
   //  const char* fileName= mid_file;
     if(SD.exists(mid_file.c_str())){
        SD.remove(mid_file.c_str());
        blue();
        }
    
 //   }

}