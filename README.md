# MD_Rev_November

<img src="https://user-images.githubusercontent.com/37872526/74939357-132cf480-5433-11ea-84d2-1860790c5b7a.jpg" width="400">

# How to Use
C620 like  
1系統につきID=1~8の範囲を使用可能

## 制御
電流int16_t(max0x7fff)で50[A]max  

ID:0x200  
DATA[0]=目標電流[1]上位8bits  
DATA[1]=目標電流[1]下位8bits  
DATA[2]=目標電流[2]上位8bits  
DATA[3]=目標電流[2]下位8bits  
DATA[4]=目標電流[3]上位8bits  
DATA[5]=目標電流[3]下位8bits  
DATA[6]=目標電流[4]上位8bits  
DATA[7]=目標電流[4]下位8bits  

ID:0x1FF  
DATA[0]=目標電流[5]上位8bits  
DATA[1]=目標電流[5]下位8bits  
DATA[2]=目標電流[6]上位8bits  
DATA[3]=目標電流[6]下位8bits  
DATA[4]=目標電流[7]上位8bits  
DATA[5]=目標電流[7]下位8bits  
DATA[6]=目標電流[8]上位8bits  
DATA[7]=目標電流[8]下位8bits  

## 返り値
ID:0x200+ID  
DATA[0]=位置 32 ~ 25bit  
DATA[1]=位置 24 ~ 17bit  
DATA[2]=位置 16 ~ 09bit  
DATA[3]=位置 08 ~ 01bit  
位置＝一周で72増加  
  
DATA[4]=現在電流上位8bits  
DATA[5]=現在電流下位8bits  
電流=12bit_maxが66[A]相当  

DATA[6]=現在電圧上位8bits  
DATA[7]=現在電圧下位8bits 
電圧＝12bit_maxが36.3[V]  

<img src="https://user-images.githubusercontent.com/37872526/75523596-aa0b3980-5a4f-11ea-9f1d-0c62c94a52ee.png" width="400">

## 実行の様子
<img src="https://user-images.githubusercontent.com/37872526/75524790-f0fa2e80-5a51-11ea-8b41-1e1c1295196d.png" width="400">  
