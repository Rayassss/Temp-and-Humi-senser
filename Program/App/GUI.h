#ifndef _GUI_H_
#define _GUI_H_
#define FONT_HUGE 1
#define FONT_MEDIUM 0
#define Red      0xf800	//红
#define Yellow   0xffe0	//黄
#define Green    0x07e0	//绿
#define Cyan     0x07ff	//青
#define Blue     0x001f	//蓝
#define Purple   0xf81f	//紫
#define Black    0x0000	//黑
#define White    0xffff	//白
#define Gray     0x7bef	//灰
#define Blue1    0xa5ff //淡蓝
#define Blue2	   0x7cdf
#define Purple1  0x8a9e //淡紫
#define Green1   0x0410 //墨绿
#define Green2   0x2616
#define Blue3	   0x751E
#define Purple2  0xcd9e //淡紫
#define Red2	   0XF260	//淡红
#define Red3	   0X8000	//棕红
void General_Display_Font(unsigned char x, unsigned int  y, unsigned int dcolor,unsigned int bgcolor,
	unsigned char *str,unsigned char Num,unsigned char Length,unsigned char Height);
void Display_Num(unsigned char Font_Size,unsigned char x,unsigned int  y,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);
unsigned int TranColor(unsigned int color);
//void GUI_sprintf_hz1212(unsigned char x, unsigned int  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor,unsigned char mode);
//void GUI_sprintf_hzstr12x(unsigned char x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);
void Draw_Frame();
//清屏
//color是背景颜色。
//说明：使用背景颜色清除TFT模块屏幕的全部显示内容。
void GUI_Clear(unsigned int color);

//画点
//(x，y)是点的坐标
//color 是点的颜色。
//说明：用指定的颜色在指定的坐标位置上画出一个点。
void GUI_Point(unsigned char x, unsigned int y, unsigned int color);

//在指定位置画一个指定大小的圆
//(rx,ry):圆心
//r    :半径
//color:颜色
//mode :0,不填充;1,填充
void GUI_arc(unsigned int rx,unsigned int ry,unsigned int r,unsigned int color,unsigned char mode);

//画实心矩形
//(sx,sy)左上角顶点坐标, 
//(ex,ey)右下角顶点坐标, color颜色
//返回: 无
//说明：在指定位置上画出实心矩形。
void GUI_box(unsigned char sx,unsigned int sy,unsigned char ex,unsigned int ey,unsigned int color);

//显示汉字字符串 纵向显示
//x1 y1 显示的初始位置
//*str 要显示的数据
//dcolor 显示字符的颜色
//bgcolor 显示字符的背景颜色  
void GUI_sprintf_hzstr16x(unsigned char x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);
void GUI_sprintf_char(unsigned char x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor,unsigned char mode);
void GUI_sprintf_hzstr8x(unsigned char x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);
void GUI_sprintf_Asc_8_16(unsigned char x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor,unsigned char mode)	;




#endif