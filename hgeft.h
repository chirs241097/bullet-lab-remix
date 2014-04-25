// Freetype2 ext4hge header  -*- C++ -*-
/*
 * Freetype2 extention for hge
 * by Chris Xiong
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Note: freetype 2.5.2 or newer is required.
 * This library is somehow buggy, known bugs:
 * * blinking charcter...
 * * segmentation fault(fixed now)
 * * Slow... but it's hard to improve...
 * * Only support a single line...
 *
 */
#ifndef HGEEFT_H
#define HGEEFT_H
#include <cstring>
#include <cwchar>
#include <hge.h>
#include <ft2build.h>
#include FT_FREETYPE_H
extern HGE* hge;
class hgeTTChar
{
private:
	hgeQuad quad;
	int rw,rh,_w,_h;
public:
	double w(){return _w;}
	double h(){return _h;}
	void Free();
	bool SetChar(wchar_t ch,FT_Face ttfface);
	void Render(double x,double y,DWORD col);
};
class hgeTTFont
{
protected:
	FT_Library libft;
	FT_Face ttfface;
	wchar_t buf[1025];
	hgeTTChar chars[1024];
	double w,h;
public:
	bool Init(const char *ttf,int size);
	double GetWidth(){return w;}
	double GetHeight(){return h;}
	void UpdateString(const wchar_t *format, ...);
	void Render(double x,double y,DWORD color,int align);
};
#endif
