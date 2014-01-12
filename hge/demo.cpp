/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: HGE splash screen
*/


#include "hge_impl.h"
#include "../loading.h"
#include "hgesprite.h"
//#ifdef DEMO
hgeSprite *SprLoad,*SprRot;
HTEXTURE TLoad,TRot;
int px,py;
float dtime,rot;
void DInit()
{
	px=pHGE->System_GetState(HGE_SCREENWIDTH)/2;
	py=pHGE->System_GetState(HGE_SCREENHEIGHT)/2;
	TLoad=pHGE->Texture_Load((char *)Loading,sizeof(Loading));
	TRot=pHGE->Texture_Load((char *)LoadCircle,sizeof(LoadCircle));
	SprLoad=new hgeSprite(TLoad,0,0,96,32);
	SprRot=new hgeSprite(TRot,0,0,48,46);
	SprLoad->SetHotSpot(48,16);SprRot->SetHotSpot(24,23);
	dtime=0.0f;rot=0.0f;
}
void DDone()
{
	delete SprLoad;delete SprRot;
	pHGE->Texture_Free(TLoad);pHGE->Texture_Free(TRot);
}
bool DFrame()
{
	BYTE alpha;
	DWORD col=0x00FFFFFF;
	dtime+=pHGE->Timer_GetDelta();
	if (dtime<=0.5)alpha=(BYTE)(dtime/0.5f*255.0f);else alpha=255;
	if (dtime<=1.5)rot+=((pHGE->Timer_GetDelta())/0.1f)*M_PI*0.3f;
	else rot+=((pHGE->Timer_GetDelta())/0.1f)*M_PI*0.3f*((2.0f-dtime)/0.5f);
	SprRot->SetColor(SETA(col,alpha));
	if (dtime>=2)return true;
	pHGE->Gfx_BeginScene();
	pHGE->Gfx_Clear(0);
	SprLoad->Render(px,py);
	SprRot->RenderEx(px-75,py,rot);
	pHGE->Gfx_EndScene();
	return false;
}
//#endif
