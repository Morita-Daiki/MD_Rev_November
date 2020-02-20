# MD_Rev_November
 
# How to Use
C620 like  
1系統につきID=1~8の範囲を使用可能

## 制御
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
DATA[4]=現在電流上位8bits  
DATA[5]=現在電流下位8bits  
DATA[6]=現在電圧上位8bits  
DATA[7]=現在電圧下位8bits 
