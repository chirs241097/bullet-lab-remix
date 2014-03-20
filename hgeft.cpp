#include "hgeft.h"
void hgeTTChar::Free(){if(quad.tex)hge->Texture_Free(quad.tex),quad.tex=0;}
bool hgeTTChar::SetChar(wchar_t ch,FT_Face ttfface)
{
	FT_GlyphSlot slot=ttfface->glyph;
	FT_UInt glyph_index=FT_Get_Char_Index(ttfface,ch);
	FT_Error err=FT_Load_Glyph(ttfface,glyph_index,FT_LOAD_DEFAULT);
	if(err)return false;
	err=FT_Render_Glyph(ttfface->glyph,FT_RENDER_MODE_NORMAL);
	if(err)return false;
	_w=slot->advance.x>>6;_h=slot->bitmap.rows;//we are one line only.
	rw=slot->bitmap.width;rh=slot->bitmap.rows;
	quad.tex=hge->Texture_Create(
	slot->bitmap.width?slot->bitmap.width:1,
	slot->bitmap.rows?slot->bitmap.rows:1);
	DWORD* tx=hge->Texture_Lock(quad.tex,false,0,0,
	slot->bitmap.width?slot->bitmap.width:1,
	slot->bitmap.rows?slot->bitmap.rows:1);
	memset(tx,0,sizeof(DWORD)*(slot->bitmap.width?slot->bitmap.width:1)*(slot->bitmap.rows?slot->bitmap.rows:1));
	int ptr=0;
	for(int i=0;i<slot->bitmap.rows;++i)
	for(int j=0;j<slot->bitmap.width;++j)
	{
#ifdef WIN32
		tx[i*slot->bitmap.width+j]=ARGB(slot->bitmap.buffer[ptr],255,255,255);
#else
		tx[(slot->bitmap.rows-i-1)*slot->bitmap.width+j]=ARGB(slot->bitmap.buffer[ptr],255,255,255);
		//In OpenGL, textures are locked upside down...
#endif
		ptr++;
	}
	hge->Texture_Unlock(quad.tex);
	quad.v[0].tx=0;quad.v[0].ty=0;quad.v[1].tx=1;quad.v[1].ty=0;
	quad.v[2].tx=1;quad.v[2].ty=1;quad.v[3].tx=0;quad.v[3].ty=1;
	return true;
}
void hgeTTChar::Render(double x,double y,DWORD col)
{
	for(int i=0;i<4;++i)quad.v[i].col=col;
	quad.v[0].x=x;quad.v[0].y=y-rh;
	quad.v[1].x=x+rw;quad.v[1].y=y-rh;
	quad.v[2].x=x+rw;quad.v[2].y=y;
	quad.v[3].x=x;quad.v[3].y=y;
	hge->Gfx_RenderQuad(&quad);
}
bool hgeTTFont::Init(const char *ttf,int size)
{
	FT_Error err=FT_Init_FreeType(&libft);
	if(err)return false;
	err=FT_New_Face(libft,ttf,0,&ttfface);
	if(err)return false;
	err=FT_Set_Char_Size(ttfface,0,size*64,96,96);
	return true;
}
void hgeTTFont::UpdateString(const wchar_t *format, ...)
{
	for(int i=0;buf[i]!='\0';++i)chars[i].Free();
	memset(buf,0,sizeof(buf));memset(chars,0,sizeof(chars));
	va_list vl;
	va_start(vl,format);
	vswprintf(buf,1024,format,vl);
	va_end(vl);
	buf[1024]='\0';
	w=h=0;
	for(int i=0;buf[i]!='\0';++i)
	{
		chars[i].SetChar(buf[i],ttfface);
		w+=chars[i].w();
		if(chars[i].h()>h)h=chars[i].h();
	}
}
void hgeTTFont::Render(double x,double y,DWORD color,int align)
{
	int cur;
	if(align==0)
	{
		cur=x;
		for(int i=0;buf[i]!='\0';++i)
		{
			chars[i].Render(cur,y,color);
			cur+=chars[i].w();
		}
	}
	if(align==1)
	{
		cur=x;
		for(int i=wcslen(buf)-1;i>=0;--i)
		{
			chars[i].Render(cur,y,color);
			cur-=chars[i].w();
		}
	}
}
