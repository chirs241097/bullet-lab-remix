// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Input manager implementation
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
#include "smelt_internal.hpp"
static const char* INP_SDL_SRCFN="smelt/sdl/inp_sdl.cpp";
bool SMELT_IMPL::smGetInpEvent(smInpEvent *e)
{
	TInputEventList *eptr;
	if(inpQueue)
	{
		eptr=inpQueue;memcpy(e,&eptr->e,sizeof(smInpEvent));
		inpQueue=inpQueue->next;delete eptr;return true;
	}
	return false;
}
void SMELT_IMPL::smGetMouse2f(float *x,float *y){*x=posx,*y=posy;}
void SMELT_IMPL::smSetMouse2f(float x,float y){SDL_WarpMouseInWindow((SDL_Window*)hwnd,x,y);}
int SMELT_IMPL::smGetWheel(){return posz;}
bool SMELT_IMPL::smIsMouseOver(){return mouseOver;}
int SMELT_IMPL::smGetKey(){return lkey;}
int SMELT_IMPL::smGetKeyState(int key)
{
	if(!(keyz[key]&4)&&keylst[key])return SMKST_RELEASE;
	if(!(keyz[key]&4))return SMKST_NONE;
	if((keyz[key]&4)&&!keylst[key])return SMKST_HIT;
	return SMKST_KEEP;
}

void SMELT_IMPL::buildEvent(int type,int k,int scan,int flags,int x,int y)
{
	TInputEventList *last,*eptr=new TInputEventList;
	eptr->e.type=type;eptr->e.chcode=0;
	int ptx=x,pty=y;
	if(type==INPUT_KEYDOWN)
	{
		k=SDLKeyToSMKey(k);
		if((k<0)||(k>(int)(sizeof(keyz)/sizeof(keyz[0]))))return;
		keyz[k]|=4;if(!(flags&SMINP_REPEAT))keyz[k]|=1;
		eptr->e.chcode=(k>=32&&k<=127)?k:0;
	}
	if(type==INPUT_KEYUP)
	{
		k=SDLKeyToSMKey(k);
		if((k<0)||(k>(int)(sizeof(keyz)/sizeof(keyz[0]))))return;
		keyz[k]&=~4;keyz[k]|=2;
		eptr->e.chcode=(k>=32&&k<=127)?k:0;
	}
	if(type==INPUT_MOUSEWHEEL)
	{eptr->e.sccode=0;eptr->e.wheel=k;}
	else{eptr->e.sccode=k;eptr->e.wheel=0;}
	if(type==INPUT_MBUTTONDOWN){keyz[k]|=1|4;captured=true;}
	if(type==INPUT_MBUTTONUP){keyz[k]|=2;keyz[k]&=~4;ptx=(int)posx;pty=(int)posy;captured=false;}
	if(keymods&KMOD_SHIFT)flags|=SMINP_SHIFT;
	if(keymods&KMOD_CTRL)flags|=SMINP_CTRL;
	if(keymods&KMOD_ALT)flags|=SMINP_ALT;
	if(keymods&KMOD_CAPS)flags|=SMINP_CAPSLOCK;
	if(keymods&KMOD_MODE)flags|=SMINP_SCROLLLOCK;
	if(keymods&KMOD_NUM)flags|=SMINP_NUMLOCK;
	eptr->e.flag=flags;
	if(ptx==-1){eptr->e.x=posx;eptr->e.y=posy;}
	else
	{
		ptx<0?ptx=0:0;pty<0?pty=0:0;
		ptx>=scrw?ptx=scrw-1:0;pty>=scrh?pty=scrh-1:0;
		eptr->e.x=(float)ptx;eptr->e.y=(float)pty;
	}
	eptr->next=0;
	if(!inpQueue)inpQueue=eptr;
	else
	{
		last=inpQueue;
		while(last->next)last=last->next;
		last->next=eptr;
	}
	if(eptr->e.type==INPUT_KEYDOWN||eptr->e.type==INPUT_MBUTTONDOWN)
	lkey=eptr->e.sccode;
	if(eptr->e.type==INPUT_MOUSEMOVE)posx=eptr->e.x,posy=eptr->e.y;
	if(eptr->e.type==INPUT_MOUSEWHEEL)posz=eptr->e.wheel;
}
void SMELT_IMPL::initInput(){posx=posy=.0;memset(keyz,0,sizeof(keyz));}
void SMELT_IMPL::clearQueue()
{
	TInputEventList *nxt,*eptr=inpQueue;
	for(unsigned i=0;i<sizeof(keyz)/sizeof(keyz[0]);++i)keyz[i]&=~3;
	while(eptr){nxt=eptr->next;delete eptr;eptr=nxt;}
	inpQueue=NULL;posz=0;lkey=0;
}
int SMELT_IMPL::SDLKeyToSMKey(int sdlkey)
{
	switch (sdlkey)
	{
		case SDL_SCANCODE_ESCAPE: return SMK_ESCAPE;
		case SDL_SCANCODE_BACKSPACE: return SMK_BACKSPACE;
		case SDL_SCANCODE_TAB: return SMK_TAB;
		case SDL_SCANCODE_RETURN: return SMK_ENTER;
		case SDL_SCANCODE_SPACE: return SMK_SPACE;
		case SDL_SCANCODE_LSHIFT: return SMK_SHIFT;
		case SDL_SCANCODE_RSHIFT: return SMK_SHIFT;
		case SDL_SCANCODE_LCTRL: return SMK_CTRL;
		case SDL_SCANCODE_RCTRL: return SMK_CTRL;
		case SDL_SCANCODE_LALT: return SMK_ALT;
		case SDL_SCANCODE_RALT: return SMK_ALT;
		case SDL_SCANCODE_LGUI: return SMK_LWIN;
		case SDL_SCANCODE_RGUI: return SMK_RWIN;
		case SDL_SCANCODE_PAUSE: return SMK_PAUSE;
		case SDL_SCANCODE_CAPSLOCK: return SMK_CAPSLOCK;
		case SDL_SCANCODE_NUMLOCKCLEAR: return SMK_NUMLOCK;
		case SDL_SCANCODE_SCROLLLOCK: return SMK_SCROLLLOCK;
		case SDL_SCANCODE_PAGEUP: return SMK_PGUP;
		case SDL_SCANCODE_PAGEDOWN: return SMK_PGDN;
		case SDL_SCANCODE_HOME: return SMK_HOME;
		case SDL_SCANCODE_END: return SMK_END;
		case SDL_SCANCODE_INSERT: return SMK_INSERT;
		case SDL_SCANCODE_DELETE: return SMK_DELETE;
		case SDL_SCANCODE_LEFT: return SMK_LEFT;
		case SDL_SCANCODE_UP: return SMK_UP;
		case SDL_SCANCODE_RIGHT: return SMK_RIGHT;
		case SDL_SCANCODE_DOWN: return SMK_DOWN;
		case SDL_SCANCODE_0: return SMK_0;
		case SDL_SCANCODE_1: return SMK_1;
		case SDL_SCANCODE_2: return SMK_2;
		case SDL_SCANCODE_3: return SMK_3;
		case SDL_SCANCODE_4: return SMK_4;
		case SDL_SCANCODE_5: return SMK_5;
		case SDL_SCANCODE_6: return SMK_6;
		case SDL_SCANCODE_7: return SMK_7;
		case SDL_SCANCODE_8: return SMK_8;
		case SDL_SCANCODE_9: return SMK_9;
		case SDL_SCANCODE_A: return SMK_A;
		case SDL_SCANCODE_B: return SMK_B;
		case SDL_SCANCODE_C: return SMK_C;
		case SDL_SCANCODE_D: return SMK_D;
		case SDL_SCANCODE_E: return SMK_E;
		case SDL_SCANCODE_F: return SMK_F;
		case SDL_SCANCODE_G: return SMK_G;
		case SDL_SCANCODE_H: return SMK_H;
		case SDL_SCANCODE_I: return SMK_I;
		case SDL_SCANCODE_J: return SMK_J;
		case SDL_SCANCODE_K: return SMK_K;
		case SDL_SCANCODE_L: return SMK_L;
		case SDL_SCANCODE_M: return SMK_M;
		case SDL_SCANCODE_N: return SMK_N;
		case SDL_SCANCODE_O: return SMK_O;
		case SDL_SCANCODE_P: return SMK_P;
		case SDL_SCANCODE_Q: return SMK_Q;
		case SDL_SCANCODE_R: return SMK_R;
		case SDL_SCANCODE_S: return SMK_S;
		case SDL_SCANCODE_T: return SMK_T;
		case SDL_SCANCODE_U: return SMK_U;
		case SDL_SCANCODE_V: return SMK_V;
		case SDL_SCANCODE_W: return SMK_W;
		case SDL_SCANCODE_X: return SMK_X;
		case SDL_SCANCODE_Y: return SMK_Y;
		case SDL_SCANCODE_Z: return SMK_Z;
		case SDL_SCANCODE_MINUS: return SMK_MINUS;
		case SDL_SCANCODE_EQUALS: return SMK_EQUALS;
		case SDL_SCANCODE_BACKSLASH: return SMK_BACKSLASH;
		case SDL_SCANCODE_LEFTBRACKET: return SMK_LBRACKET;
		case SDL_SCANCODE_RIGHTBRACKET: return SMK_RBRACKET;
		case SDL_SCANCODE_SEMICOLON: return SMK_SEMICOLON;
		case SDL_SCANCODE_APOSTROPHE: return SMK_APOSTROPHE;
		case SDL_SCANCODE_COMMA: return SMK_COMMA;
		case SDL_SCANCODE_PERIOD: return SMK_PERIOD;
		case SDL_SCANCODE_SLASH: return SMK_SLASH;
		case SDL_SCANCODE_KP_0: return SMK_NUMPAD0;
		case SDL_SCANCODE_KP_1: return SMK_NUMPAD1;
		case SDL_SCANCODE_KP_2: return SMK_NUMPAD2;
		case SDL_SCANCODE_KP_3: return SMK_NUMPAD3;
		case SDL_SCANCODE_KP_4: return SMK_NUMPAD4;
		case SDL_SCANCODE_KP_5: return SMK_NUMPAD5;
		case SDL_SCANCODE_KP_6: return SMK_NUMPAD6;
		case SDL_SCANCODE_KP_7: return SMK_NUMPAD7;
		case SDL_SCANCODE_KP_8: return SMK_NUMPAD8;
		case SDL_SCANCODE_KP_9: return SMK_NUMPAD9;
		case SDL_SCANCODE_KP_MULTIPLY: return SMK_MULTIPLY;
		case SDL_SCANCODE_KP_DIVIDE: return SMK_DIVIDE;
		case SDL_SCANCODE_KP_PLUS: return SMK_ADD;
		case SDL_SCANCODE_KP_MINUS: return SMK_SUBTRACT;
		case SDL_SCANCODE_KP_PERIOD: return SMK_DECIMAL;
		case SDL_SCANCODE_F1: return SMK_F1;
		case SDL_SCANCODE_F2: return SMK_F2;
		case SDL_SCANCODE_F3: return SMK_F3;
		case SDL_SCANCODE_F4: return SMK_F4;
		case SDL_SCANCODE_F5: return SMK_F5;
		case SDL_SCANCODE_F6: return SMK_F6;
		case SDL_SCANCODE_F7: return SMK_F7;
		case SDL_SCANCODE_F8: return SMK_F8;
		case SDL_SCANCODE_F9: return SMK_F9;
		case SDL_SCANCODE_F10: return SMK_F10;
		case SDL_SCANCODE_F11: return SMK_F11;
		case SDL_SCANCODE_F12: return SMK_F12;
		default: return -1;
	}
	return -1;
}
