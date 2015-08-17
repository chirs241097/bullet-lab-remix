// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Truetype font support implementation
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 * This library is developed for the BLR series games.
 */
#include "smttfont.hpp"

SMELT *smTTChar::sm=NULL;

void smTTChar::free(){if(quad.tex){sm->smTextureFree(quad.tex);quad.tex=0;sm->smRelease();}}
bool smTTChar::setChar(wchar_t c,FT_Face ttface)
{
	if(!sm)sm=smGetInterface(SMELT_APILEVEL);
	FT_GlyphSlot slot=ttface->glyph;
	FT_UInt glyph_index=FT_Get_Char_Index(ttface,c);
	if(FT_Load_Glyph(ttface,glyph_index,FT_LOAD_DEFAULT))return false;
	if(FT_Render_Glyph(ttface->glyph,FT_RENDER_MODE_NORMAL))return false;
	_w=slot->advance.x>>6;_h=3*slot->bitmap.rows-2*slot->bitmap_top;
	rw=slot->bitmap.width;rh=slot->bitmap.rows;
	xofs=slot->bitmap_left;yofs=slot->bitmap.rows-slot->bitmap_top;
	quad.tex=sm->smTextureCreate(rw?rw:1,rh?rh:1);
	DWORD* px=sm->smTextureLock(quad.tex,0,0,rw?rw:1,rh?rh:1,false);
	memset(px,0,sizeof(DWORD)*(rw?rw:1)*(rh?rh:1));
	int ptr=0;
	for(int i=0;i<rh;++i)
	for(int j=0;j<rw;++j)
	{
#ifdef _D3D
		px[i*rw+j]=ARGB(slot->bitmap.buffer[ptr],255,255,255);
#else
		px[(rh-i-1)*rw+j]=ARGB(slot->bitmap.buffer[ptr],255,255,255);
#endif
		++ptr;
	}
	sm->smTexutreUnlock(quad.tex);
	quad.blend=BLEND_ALPHABLEND;
	quad.v[0].tx=0;quad.v[0].ty=0;quad.v[1].tx=1;quad.v[1].ty=0;
	quad.v[2].tx=1;quad.v[2].ty=1;quad.v[3].tx=0;quad.v[3].ty=1;
	return true;
}
void smTTChar::render(float x,float y,DWORD col)
{
	for(int i=0;i<4;++i)quad.v[i].col=col,quad.v[i].z=.5;
	quad.v[0].x=x+xofs;quad.v[0].y=y-rh+yofs;
	quad.v[1].x=x+rw+xofs;quad.v[1].y=y-rh+yofs;
	quad.v[2].x=x+rw+xofs;quad.v[2].y=y+yofs;
	quad.v[3].x=x+xofs;quad.v[3].y=y+yofs;
	sm->smRenderQuad(&quad);
}

bool smTTFont::loadTTF(const char* path,int pt)
{
	if(FT_Init_FreeType(&ftlib))return false;
	if(FT_New_Face(ftlib,path,0,&ttface))return false;
	if(FT_Set_Char_Size(ttface,0,pt*64,96,96))return false;
	chars.clear();
	return true;
}
bool smTTFont::loadTTFFromMemory(char* ptr,DWORD size,int pt)
{
	if(FT_Init_FreeType(&ftlib))return false;
	if(FT_New_Memory_Face(ftlib,(const FT_Byte*)ptr,(FT_Long)size,0,&ttface))return false;
	if(FT_Set_Char_Size(ttface,0,pt*64,96,96))return false;
	chars.clear();
	return true;
}
void smTTFont::releaseTTF()
{
	FT_Done_Face(ttface);
	FT_Done_FreeType(ftlib);
}
void smTTFont::updateString(const wchar_t *format,...)
{
	memset(buf,0,sizeof(buf));
	va_list vl;
	va_start(vl,format);
	vswprintf(buf,1024,format,vl);
	va_end(vl);
	buf[1024]='\0';
	w=h=0;float lh=0;
	for(int i=0;buf[i]!='\0';++i)
	{
		if(chars.find(buf[i])==chars.end()&&buf[i]!=L'\n')
			if(!chars[buf[i]].setChar(buf[i],ttface))
			chars.erase(chars.find(buf[i]));
		if(chars.find(buf[i])!=chars.end())
		{
			w+=chars[buf[i]].w();
			if(chars[buf[i]].h()>lh)lh=chars[buf[i]].h();
		}
		if(buf[i]==L'\n')h+=lh,lh=0;
	}
	h+=lh;
}
void smTTFont::render(float x,float y,DWORD col,int align)
{
	float curx,cury,lh;
	if(align==ALIGN_LEFT)
	{
		curx=x;cury=y;lh=0;
		for(int i=0;buf[i]!=L'\0';++i)
		{
			if(buf[i]!=L'\n')
			{
				if(chars.find(buf[i])!=chars.end())
				{
					chars[buf[i]].render(curx,cury,col);
					curx+=chars[buf[i]].w();
					lh=chars[buf[i]].h()>lh?chars[buf[i]].h():lh;
				}
			}
			else cury+=lh,lh=0,curx=x;
		}
	}
	if(align==ALIGN_RIGHT)
	{
		curx=x;cury=y;lh=0;
		for(int i=wcslen(buf)-1;i>=0;--i)
		{
			if(buf[i]!=L'\n')
			{
				if(chars.find(buf[i])!=chars.end())
				{
					chars[buf[i]].render(curx,cury,col);
					curx-=chars[buf[i]].w();
					lh=chars[buf[i]].h()>lh?chars[buf[i]].h():lh;
				}
			}
			else cury-=lh,lh=0,curx=x;
		}
	}
}
DWORD smTTFont::getCacheSize(){return chars.size();}
void smTTFont::clearCache()
{
	for(std::map<wchar_t,smTTChar>::iterator i=chars.begin();i!=chars.end();++i)
	i->second.free();
	chars.clear();
}
