//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <mmsystem.h>
#pragma hdrstop
#include <stdlib.h>
#include "war.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;
float p1X,p1Y,p2X,p2Y;
float X,Y,V,B;
int m=20,Aw=0,h=1;
int C=0,C1=0,C2=0,d=50,z=3,l1=35,l2=55,m1=35,m2=55;
int k=2;
int XY[7][2];
float g=9.81,T=0.2;
float Vx,Vy,Ax=0,Ay=0,Acx=0,Acy=0;
float Lv1=130,Lv2=130,Lb1=45,Lb2=45;
//----------------------------------------------------------------------------
float land(float x){
 float y;
  y=200+100/((x-800)/50);
  if(x<646)y=130+(x-570)/2;
  if(x<570)y=270-2*(x-500);
  if(x<500)y=320-x/10;
  if(x<400)y=sin((x-330)/57)*100+186;
  if(x<330)y=156+x-300;
  if(x<300)y=156;
  if(x<260)y=286-x/2;
  if(x<230)y=400-x;
  if(x<200)y=sin((x-20)/57)*100+200;
  return y;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)
{
Canvas->MoveTo(0,50);
Canvas->Pen->Color=clBlue;
float x,y;
for(x=0;x<ClientWidth;x++){
Canvas->Pixels[x][land(x)]=clTeal;
Canvas->Pixels[x][land(x)-1]=clTeal;
Canvas->MoveTo(x,land(x)-2);
Canvas->LineTo(x,0);
}
randomize();
p1X=random(350);
p1Y=land(p1X);
p2X=random(300);
p2X+=450;
p2Y=land(p2X);
Canvas->Pen->Color=clFuchsia;
Canvas->Brush->Color=clRed;
Canvas->Pen->Width=2;
Canvas->Rectangle(p1X-5,p1Y-3,p1X+5,p1Y+3);
Canvas->MoveTo(p1X,p1Y);
Canvas->Pen->Color=clRed;
Canvas->LineTo(p1X+7,p1Y-7);
Canvas->Pen->Color=clGray;
Canvas->Brush->Color=clWhite;
Canvas->Rectangle(p2X-5,p2Y-3,p2X+5,p2Y+3);
Canvas->MoveTo(p2X,p2Y);
Canvas->Pen->Color=clWhite;
Canvas->LineTo(p2X-7,p2Y-7);
Canvas->Pen->Width=1;
Canvas->Pen->Color=clBlack;
Canvas->MoveTo(X,Y);

if(p1X>100 && p1X<230){l1=75;l2=85;Lb1=80;}
if(p2X>300 && p2X<450){m1=70;m2=80;Lb2=75;}
if(p2X>700){m1=20;m2=40;Lb2=30;}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
h=1;
Acx=Vx*Vx/(m*m);
Acy=Vy*Vy/(m*m);
if(Vx<0)Acx*=-1;
Ax=Aw/4-Acx;
Ay=-g-Acy;
Vx+=Ax*T;
Vy+=Ay*T;
X+=Vx*T;
Y-=Vy*T;
XY[0][0]=XY[1][0];
XY[1][0]=XY[2][0];
XY[2][0]=XY[3][0];
XY[3][0]=XY[4][0];
XY[4][0]=XY[5][0];
XY[5][0]=XY[6][0];
XY[6][0]=X;
XY[0][1]=XY[1][1];
XY[1][1]=XY[2][1];
XY[2][1]=XY[3][1];
XY[3][1]=XY[4][1];
XY[4][1]=XY[5][1];
XY[5][1]=XY[6][1];
XY[6][1]=Y;
Canvas->Pen->Color=clBlue;
Canvas->MoveTo(XY[0][0],XY[0][1]);
Canvas->LineTo(XY[1][0],XY[1][1]);
Canvas->LineTo(XY[2][0],XY[2][1]);
Canvas->LineTo(XY[3][0],XY[3][1]);
Canvas->Pen->Color=clBlack;
Canvas->LineTo(XY[4][0],XY[4][1]);
Canvas->LineTo(XY[5][0],XY[5][1]);
Canvas->LineTo(XY[6][0],XY[6][1]);
if(X<0 || X>800 || land(X)<Y){
Canvas->Pen->Color=clBlue;
Canvas->MoveTo(XY[3][0],XY[3][1]);
Canvas->LineTo(XY[4][0],XY[4][1]);
//-----------------------------------------------------------------
PlaySound("002.wav",0,SND_SYNC);
Canvas->LineTo(XY[5][0],XY[5][1]);
Canvas->LineTo(XY[6][0],XY[6][1]);
if(p1X>X-8 && p1X<X+8){Panel9->Visible=true;h=0;}
if(p2X>X-8 && p2X<X+8){Panel8->Visible=true;h=0;}
if(N2->Checked==true)Aw=random(30)-16;
else Aw=0;
if(Aw>=-15 && Aw<-9)Panel3->Color=clRed;
else Panel3->Color=clGray;
if(Aw>=-15 && Aw<-3)Panel4->Color=clYellow;
else Panel4->Color=clGray;
if(Aw>=-15 && Aw<=15)Panel5->Color=clLime;
if(Aw==0)Panel5->Color=clGray;
if(Aw>3 && Aw<=15)Panel6->Color=clYellow;
else Panel6->Color=clGray;
if(Aw>9 && Aw<=15)Panel7->Color=clRed;
else Panel7->Color=clGray;

if(k==1){
  Lb1+=(random(100)%3-1)*z;
  if(Lb1<l1)Lb1+=(random(100)%4)*z;
  if(Lb1>l2)Lb1-=(random(100)%4)*z;
  if(X>p2X)Lv1-=random(d);
  if(X<p2X)Lv1+=random(d);}

if(k==2){
  Lb2+=(random(100)%3-1)*z;
  if(Lb2<m1)Lb2+=(random(100)%4)*z;
  if(Lb2>m2)Lb2-=(random(100)%4)*z;
  if(X<p1X)Lv2-=random(d);
  if(X>p1X)Lv2+=random(d);}

if(h!=0){Button1->Enabled=True;
CSpinEdit1->Enabled=true;
CSpinEdit2->Enabled=true;}

if(k==1 && C2==1){
CSpinEdit1->Enabled=false;
CSpinEdit2->Enabled=false;}
if(k==2 && C1==1){
CSpinEdit1->Enabled=false;
CSpinEdit2->Enabled=false;}
Timer1->Enabled=False;

if(k==1 && C2==1 && h!=0){
//----------------
PlaySound("001.wav",0,SND_ASYNC);
Panel1->Color=clRed;
Panel2->Color=clRed;
X=p2X;
Y=p2Y;
k=2;
B=Lb2;
B=(180-B)/57;
V=Lv2;
Vx=V*cos(B);
Vy=V*sin(B);
Canvas->MoveTo(X,Y);
Button1->Enabled=false;
CSpinEdit1->Enabled=false;
CSpinEdit2->Enabled=false;
XY[0][0]=XY[1][0]=XY[2][0]=XY[3][0]=XY[4][0]=XY[5][0]=XY[6][0]=X;
XY[0][1]=XY[1][1]=XY[2][1]=XY[3][1]=XY[4][1]=XY[5][1]=XY[6][1]=Y;
Timer1->Enabled=true;
//----------------
}
else{if(k==2 && C1==1 && h!=0){
//----------------
PlaySound("001.wav",0,SND_ASYNC);
Panel1->Color=clWhite;
Panel2->Color=clWhite;
X=p1X;
Y=p1Y;
k=1;
B=Lb1;
B/=57;
V=Lv1;
Vx=V*cos(B);
Vy=V*sin(B);
Canvas->MoveTo(X,Y);
Button1->Enabled=false;
CSpinEdit1->Enabled=false;
CSpinEdit2->Enabled=false;
XY[0][0]=XY[1][0]=XY[2][0]=XY[3][0]=XY[4][0]=XY[5][0]=XY[6][0]=X;
XY[0][1]=XY[1][1]=XY[2][1]=XY[3][1]=XY[4][1]=XY[5][1]=XY[6][1]=Y;
Timer1->Enabled=true;
//----------------
}}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
PlaySound("001.wav",0,SND_ASYNC);
if(k==2){
Panel1->Color=clWhite;
Panel2->Color=clWhite;
X=p1X;
Y=p1Y;
k=1;
}
else {
Panel1->Color=clRed;
Panel2->Color=clRed;
X=p2X;
Y=p2Y;
k=2;
}
if((k==1 && C1==0) || (k==2 && C2==0))B=StrToFloat(CSpinEdit2->Text);
else {
 if(k==1)B=Lb1;
 else B=Lb2;
}
if(k==1)B/=57;
else B=(180-B)/57;
if((k==1 && C1==0) || (k==2 && C2==0))V=StrToFloat(CSpinEdit1->Text);
else {
 if(k==1)V=Lv1;
 else V=Lv2;
}
Vx=V*cos(B);
Vy=V*sin(B);
Canvas->MoveTo(X,Y);
Button1->Enabled=false;
CSpinEdit1->Enabled=false;
CSpinEdit2->Enabled=false;
XY[0][0]=XY[1][0]=XY[2][0]=XY[3][0]=XY[4][0]=XY[5][0]=XY[6][0]=X;
XY[0][1]=XY[1][1]=XY[2][1]=XY[3][1]=XY[4][1]=XY[5][1]=XY[6][1]=Y;
Timer1->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CSpinEdit1KeyPress(TObject *Sender, char &Key)
{
PlaySound("003.wav",0,SND_ASYNC);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CSpinEdit2KeyPress(TObject *Sender, char &Key)
{
PlaySound("003.wav",0,SND_ASYNC);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N11Click(TObject *Sender)
{
N11->Checked=!N11->Checked;
if(N11->Checked==true){
C1=1;
if(k==2){CSpinEdit1->Enabled=false;
CSpinEdit2->Enabled=false;
}}
else {
C1=0;
if(k==2){CSpinEdit1->Enabled=true;
CSpinEdit2->Enabled=true;}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N21Click(TObject *Sender)
{
N21->Checked=!N21->Checked;
if(N21->Checked==true){
C2=1;
if(k==1){CSpinEdit1->Enabled=false;
CSpinEdit2->Enabled=false;
}}
else {
C2=0;
if(k==1){CSpinEdit1->Enabled=true;
CSpinEdit2->Enabled=true;}
}
}
//---------------------------------------------------------------------------




void __fastcall TForm1::N2Click(TObject *Sender)
{
N2->Checked=!N2->Checked;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N4Click(TObject *Sender)
{
RichEdit1->Visible=true;
Button2->Visible=true;
RichEdit1->Lines->LoadFromFile("004.rtf");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
RichEdit1->Visible=false;
Button2->Visible=false;
}
//---------------------------------------------------------------------------

