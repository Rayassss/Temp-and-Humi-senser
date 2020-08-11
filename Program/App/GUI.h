#ifndef _GUI_H_
#define _GUI_H_
#define FONT_HUGE 1
#define FONT_MEDIUM 0
#define Red      0xf800	//��
#define Yellow   0xffe0	//��
#define Green    0x07e0	//��
#define Cyan     0x07ff	//��
#define Blue     0x001f	//��
#define Purple   0xf81f	//��
#define Black    0x0000	//��
#define White    0xffff	//��
#define Gray     0x7bef	//��
#define Blue1    0xa5ff //����
#define Blue2	   0x7cdf
#define Purple1  0x8a9e //����
#define Green1   0x0410 //ī��
#define Green2   0x2616
#define Blue3	   0x751E
#define Purple2  0xcd9e //����
#define Red2	   0XF260	//����
#define Red3	   0X8000	//�غ�
void General_Display_Font(unsigned char x, unsigned int  y, unsigned int dcolor,unsigned int bgcolor,
	unsigned char *str,unsigned char Num,unsigned char Length,unsigned char Height);
void Display_Num(unsigned char Font_Size,unsigned char x,unsigned int  y,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);
unsigned int TranColor(unsigned int color);
//void GUI_sprintf_hz1212(unsigned char x, unsigned int  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor,unsigned char mode);
//void GUI_sprintf_hzstr12x(unsigned char x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);
void Draw_Frame();
//����
//color�Ǳ�����ɫ��
//˵����ʹ�ñ�����ɫ���TFTģ����Ļ��ȫ����ʾ���ݡ�
void GUI_Clear(unsigned int color);

//����
//(x��y)�ǵ������
//color �ǵ����ɫ��
//˵������ָ������ɫ��ָ��������λ���ϻ���һ���㡣
void GUI_Point(unsigned char x, unsigned int y, unsigned int color);

//��ָ��λ�û�һ��ָ����С��Բ
//(rx,ry):Բ��
//r    :�뾶
//color:��ɫ
//mode :0,�����;1,���
void GUI_arc(unsigned int rx,unsigned int ry,unsigned int r,unsigned int color,unsigned char mode);

//��ʵ�ľ���
//(sx,sy)���ϽǶ�������, 
//(ex,ey)���½Ƕ�������, color��ɫ
//����: ��
//˵������ָ��λ���ϻ���ʵ�ľ��Ρ�
void GUI_box(unsigned char sx,unsigned int sy,unsigned char ex,unsigned int ey,unsigned int color);

//��ʾ�����ַ��� ������ʾ
//x1 y1 ��ʾ�ĳ�ʼλ��
//*str Ҫ��ʾ������
//dcolor ��ʾ�ַ�����ɫ
//bgcolor ��ʾ�ַ��ı�����ɫ  
void GUI_sprintf_hzstr16x(unsigned char x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);
void GUI_sprintf_char(unsigned char x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor,unsigned char mode);
void GUI_sprintf_hzstr8x(unsigned char x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);
void GUI_sprintf_Asc_8_16(unsigned char x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor,unsigned char mode)	;




#endif