// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * GFX implementation based on SDL2/OpenGL and hge-unix
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
#include "smelt_internal.hpp"
#include "CxImage/ximage.h"
#define dbg printf("%d: 0x%X\n",__LINE__,pOpenGLDevice->glGetError())
static const char* GFX_SDL_SRCFN="smelt/sdl/gfx_sdl.cpp";
struct glTexture
{
	GLuint name,rw,rh,dw,dh;
	const char *fn;
	DWORD *px,*locpx;
	bool isTarget,lost,roloc;
	GLint locx,locy,locw,loch;
};
bool SMELT_IMPL::smRenderBegin2D(bool ztest,SMTRG trg)
{
	TRenderTargetList *targ=(TRenderTargetList*)trg;
	if(vertexArray)
	{smLog("%s:"SLINE": Last frame not closed.\n",GFX_SDL_SRCFN);return false;}
	if(pOpenGLDevice->have_GL_EXT_framebuffer_object)
	pOpenGLDevice->glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,(targ)?targ->frame:0);
	pOpenGLDevice->glDepthFunc(GL_GEQUAL);
	ztest?pOpenGLDevice->glEnable(GL_DEPTH_TEST):pOpenGLDevice->glDisable(GL_DEPTH_TEST);
	zbufenabled=ztest;
	if(targ)
	{
		pOpenGLDevice->glScissor(0,0,targ->w,targ->h);
		pOpenGLDevice->glViewport(0,0,targ->w,targ->h);
		configProjectionMatrix2D(targ->w,targ->h);
	}
	else
	{
		pOpenGLDevice->glScissor(0,0,scrw,scrh);
		pOpenGLDevice->glViewport(0,0,scrw,scrh);
		configProjectionMatrix2D(scrw,scrh);
	}
	sm2DCamera5f3v(NULL,NULL,NULL);
	curTarget=targ;tdmode=0;
	vertexArray=vertexBuf;
	return true;
}
bool SMELT_IMPL::smRenderBegin3D(float fov,SMTRG trg)
{
	TRenderTargetList *targ=(TRenderTargetList*)trg;
	if(vertexArray)
	{smLog("%s:"SLINE": Last frame not closed.\n",GFX_SDL_SRCFN);return false;}
	if(pOpenGLDevice->have_GL_EXT_framebuffer_object)
	pOpenGLDevice->glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,(targ)?targ->frame:0);
	pOpenGLDevice->glDepthFunc(GL_LESS);
	pOpenGLDevice->glEnable(GL_DEPTH_TEST);
	zbufenabled=true;
	if(targ)
	{
		pOpenGLDevice->glScissor(0,0,targ->w,targ->h);
		pOpenGLDevice->glViewport(0,0,targ->w,targ->h);
		configProjectionMatrix3D(targ->w,targ->h,fov);
	}
	else
	{
		pOpenGLDevice->glScissor(0,0,scrw,scrh);
		pOpenGLDevice->glViewport(0,0,scrw,scrh);
		configProjectionMatrix3D(scrw,scrh,fov);
	}
	sm3DCamera6f2v(NULL,NULL);
	curTarget=targ;tdmode=1;
	vertexArray=vertexBuf;
	return true;
}
bool SMELT_IMPL::smRenderEnd()
{
	batchOGL(true);
	if(curTarget&&!pOpenGLDevice->have_GL_EXT_framebuffer_object)
	{
		glTexture *pTex=(glTexture*)curTarget->tex;
		if(pTex&&pTex->lost)
		configTexture(pTex,pTex->rw,pTex->rh,pTex->px);
		int w=curTarget->w,h=curTarget->h;
		pOpenGLDevice->glFinish();
		DWORD *px=new DWORD[w*h];
		pOpenGLDevice->glReadPixels(0,0,w,h,GL_RGBA,GL_UNSIGNED_BYTE,px);
		pOpenGLDevice->glBindTexture(pOpenGLDevice->TextureTarget,pTex->name);
		pOpenGLDevice->glTexSubImage2D(pOpenGLDevice->TextureTarget,0,0,0,w,h,GL_RGBA,GL_UNSIGNED_BYTE,px);
		pOpenGLDevice->glBindTexture(pOpenGLDevice->TextureTarget,primTex?(((glTexture*)primTex)->name):0);
		delete[] px;
	}
	if(!curTarget)SDL_GL_SwapWindow((SDL_Window*)hwnd);
	return true;
}
void SMELT_IMPL::smClrscr(DWORD color)
{
	GLfloat a=(GLfloat)(GETA(color))/255.f;
	GLfloat r=(GLfloat)(GETR(color))/255.f;
	GLfloat g=(GLfloat)(GETG(color))/255.f;
	GLfloat b=(GLfloat)(GETB(color))/255.f;
	pOpenGLDevice->glClearColor(r,g,b,a);
	if(tdmode)pOpenGLDevice->glClearDepth(1);
	else if(zbufenabled)pOpenGLDevice->glClearDepth(0);
	pOpenGLDevice->glClear(GL_COLOR_BUFFER_BIT|((zbufenabled||tdmode)?GL_DEPTH_BUFFER_BIT:0));
}
void SMELT_IMPL::sm3DCamera6f2v(float *pos,float *rot)
{
	batchOGL();
	pOpenGLDevice->glMatrixMode(GL_MODELVIEW);
	pOpenGLDevice->glLoadIdentity();
	if(!pos||!rot)return;
	pOpenGLDevice->glRotatef((GLfloat)-rot[0],1,0,0);
	pOpenGLDevice->glRotatef((GLfloat)-rot[1],0,1,0);
	pOpenGLDevice->glRotatef((GLfloat)-rot[2],0,0,1);
	pOpenGLDevice->glTranslatef((GLfloat)-pos[0],(GLfloat)-pos[1],(GLfloat)-pos[2]);
}
void SMELT_IMPL::smMultViewMatrix(float *mat)
{
	pOpenGLDevice->glMatrixMode(GL_MODELVIEW);
	pOpenGLDevice->glMultMatrixf(mat);
}
void SMELT_IMPL::sm2DCamera5f3v(float *pos,float *dpos,float *rot)
{
	batchOGL();
	pOpenGLDevice->glMatrixMode(GL_MODELVIEW);
	pOpenGLDevice->glLoadIdentity();
	if(!pos||!dpos||!rot)return;
	pOpenGLDevice->glTranslatef(-pos[0],-pos[1],0.0f);
	pOpenGLDevice->glRotatef(*rot,0.0f,0.0f,1.0f);
	pOpenGLDevice->glTranslatef(pos[0]+dpos[0],pos[1]+dpos[1],0.0f);
}
void SMELT_IMPL::smRenderLinefd(float x1,float y1,float z1,float x2,float y2,float z2,DWORD color)
{
	if(vertexArray)
	{
		if(primType!=PRIM_LINES||primcnt>=VERTEX_BUFFER_SIZE/PRIM_LINES||primTex||primBlend!=BLEND_ALPHABLEND)
		{
			batchOGL();
			primType=PRIM_LINES;
			if(primBlend!=BLEND_ALPHAADD)setBlend(BLEND_ALPHAADD);
			bindTexture(NULL);
		}
		int i=(primcnt++)*PRIM_LINES;
		vertexArray[i].x=x1,vertexArray[i+1].x=x2;
		vertexArray[i].y=y1,vertexArray[i+1].y=y2;
		vertexArray[i].x=z1,vertexArray[i+1].x=z2;
		vertexArray[i].col=vertexArray[i+1].col=color;
		vertexArray[i].tx=vertexArray[i+1].tx=.0;
		vertexArray[i].ty=vertexArray[i+1].ty=.0;
	}
}
void SMELT_IMPL::smRenderLinefvd(float *p1,float *p2,DWORD color)
{
	if(vertexArray&&p1&&p2)
	{
		if(primType!=PRIM_LINES||primcnt>=VERTEX_BUFFER_SIZE/PRIM_LINES||primTex||primBlend!=BLEND_ALPHABLEND)
		{
			batchOGL();
			primType=PRIM_LINES;
			if(primBlend!=BLEND_ALPHAADD)setBlend(BLEND_ALPHAADD);
			bindTexture(NULL);
		}
		int i=(primcnt++)*PRIM_LINES;
		vertexArray[i].x=p1[0],vertexArray[i+1].x=p2[0];
		vertexArray[i].y=p1[1],vertexArray[i+1].y=p2[1];
		vertexArray[i].x=p2[2],vertexArray[i+1].x=p2[2];
		vertexArray[i].col=vertexArray[i+1].col=color;
		vertexArray[i].tx=vertexArray[i+1].tx=.0;
		vertexArray[i].ty=vertexArray[i+1].ty=.0;
	}
}
void SMELT_IMPL::smRenderTriangle(smTriangle *t)
{
	if(vertexArray)
	{
		if(primType!=PRIM_TRIANGLES||primcnt>=VERTEX_BUFFER_SIZE/PRIM_TRIANGLES||
		primTex!=t->tex||primBlend!=t->blend)
		{
			batchOGL();
			primType=PRIM_TRIANGLES;
			if(primBlend!=t->blend)setBlend(t->blend);
			bindTexture((glTexture*)t->tex);
		}
		memcpy(&vertexArray[(primcnt++)*PRIM_TRIANGLES],t->v,sizeof(smVertex)*PRIM_TRIANGLES);
	}
}
void SMELT_IMPL::smRenderQuad(smQuad *q)
{
	if(vertexArray)
	{
		if(primType!=PRIM_QUADS||primcnt>=VERTEX_BUFFER_SIZE/PRIM_QUADS||
		primTex!=q->tex||primBlend!=q->blend)
		{
			batchOGL();
			primType=PRIM_QUADS;
			if(primBlend!=q->blend)setBlend(q->blend);
			bindTexture((glTexture*)q->tex);
		}
		memcpy(&vertexArray[(primcnt++)*PRIM_QUADS],q->v,sizeof(smVertex)*PRIM_QUADS);
	}
}
smVertex* SMELT_IMPL::smGetVertArray()
{
	if(vertexArray)
	{
		batchOGL();
		return vertexArray;
	}
	else return NULL;
}
void SMELT_IMPL::smDrawVertArray(int prim,SMTEX texture,int blend,int _primcnt)
{
	primType=prim;
	bindTexture((glTexture*)texture);
	if(primBlend!=blend)setBlend(blend);
	primcnt=primcnt;
}
SMTRG SMELT_IMPL::smTargetCreate(int w,int h)
{
	bool ok=false;
	TRenderTargetList *pTarget=new TRenderTargetList;
	memset(pTarget,0,sizeof(TRenderTargetList));
	pTarget->tex=buildTexture(w,h,NULL);
	glTexture *gltex=(glTexture*)pTarget->tex;
	gltex->isTarget=true;gltex->lost=false;
	configTexture(gltex,w,h,NULL,false);
	pTarget->w=w;pTarget->h=h;
	ok=buildTarget(pTarget,gltex->name,w,h);
	if(!ok)
	{
		smLog("%s:"SLINE": Failed to create render target.\n",GFX_SDL_SRCFN);
		smTextureFree(pTarget->tex);
		delete pTarget;
		return 0;
	}
	pTarget->next=targets;
	targets=pTarget;
	return (SMTRG)pTarget;
}
SMTEX SMELT_IMPL::smTargetTexture(SMTRG targ)
{
	TRenderTargetList *pTarg=(TRenderTargetList*)targ;
	return targ?pTarg->tex:0;
}
void SMELT_IMPL::smTargetFree(SMTRG targ)
{
	TRenderTargetList *pTarget=targets,*pLastTarg=NULL;
	while(pTarget)
	{
		if((TRenderTargetList*)targ==pTarget)
		{
			if(pLastTarg)pLastTarg->next=pTarget->next;
			else targets=pTarget->next;
			if(pOpenGLDevice->have_GL_EXT_framebuffer_object)
			{
				if(curTarget==(TRenderTargetList*)targ)
				pOpenGLDevice->glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
				if(pTarget->depth)
				pOpenGLDevice->glDeleteRenderbuffersEXT(1,&pTarget->depth);
				pOpenGLDevice->glDeleteFramebuffersEXT(1,&pTarget->frame);
			}
			if(curTarget==(TRenderTargetList*)targ)curTarget=0;
			smTextureFree(pTarget->tex);
			delete pTarget;
			return;
		}
		pLastTarg=pTarget;
		pTarget=pTarget->next;
	}
}
SMTEX SMELT_IMPL::smTextureCreate(int w,int h)
{
	DWORD *px=new DWORD[w*h];
	memset(px,0,sizeof(DWORD)*w*h);
	SMTEX ret=buildTexture(w,h,px);
	if(ret)
	{
		TTextureList *tex=new TTextureList;
		tex->tex=ret;
		tex->w=w;
		tex->h=h;
		tex->next=textures;
		textures=tex;
	}
	return ret;
}
SMTEX SMELT_IMPL::smTextureLoad(const char *path)
{
	FILE *pFile;DWORD size,rsize;char *buff;
	SMTEX ret=0;
	pFile=fopen(path,"rb");
	if(!pFile)return 0;
	fseek(pFile,0,SEEK_END);size=ftell(pFile);rewind(pFile);
	buff=(char*)malloc(sizeof(char)*size);
	if(!buff)return 0;
	rsize=fread(buff,1,size,pFile);
	if(rsize!=size)return 0;
	ret=smTextureLoadFromMemory(buff,size);
	glTexture *t=(glTexture*)ret;
	configTexture(t,t->rw,t->rh,t->px);
	delete[] t->px;t->px=NULL;
	t->fn=strcpy(new char[strlen(path)+1],path);
	free(buff);
	fclose(pFile);
	return ret;
}
SMTEX SMELT_IMPL::smTextureLoadFromMemory(const char *ptr,DWORD size)
{
	int w=0,h=0;SMTEX ret=0;
	DWORD *px=decodeImage((BYTE*)ptr,NULL,size,w,h);
	if(px)ret=buildTexture(w,h,px);
	if(ret)
	{
		TTextureList *tex=new TTextureList;
		tex->tex=ret;tex->w=w;tex->h=h;
		tex->next=textures;textures=tex;
	}
	return ret;
}
void SMELT_IMPL::smTextureFree(SMTEX tex)
{
	if(!pOpenGLDevice)return;
	TTextureList *ctex=textures,*lasttex=NULL;
	while(ctex)
	{
		if(ctex->tex==tex)
		{
			if(lasttex)lasttex->next=ctex->next;
			else textures=ctex->next;
			delete ctex;
			break;
		}
		lasttex=ctex;
		ctex=ctex->next;
	}
	if(tex)
	{
		glTexture *ptex=(glTexture*)tex;
		delete[] ptex->fn;delete[] ptex->locpx;delete[] ptex->px;
		pOpenGLDevice->glDeleteTextures(1,&ptex->name);
		delete ptex;
	}
}
int SMELT_IMPL::smTextureGetWidth(SMTEX tex,bool original)
{
	if(original)
	{
		TTextureList *ctex=textures;
		while(ctex){if(ctex->tex==tex)return ctex->w;ctex=ctex->next;}
	}
	else return ((glTexture*)tex)->rw;
	return 0;
}
int SMELT_IMPL::smTextureGetHeight(SMTEX tex,bool original)
{
	if(original)
	{
		TTextureList *ctex=textures;
		while(ctex){if(ctex->tex==tex)return ctex->h;ctex=ctex->next;}
	}
	else return ((glTexture*)tex)->rh;
	return 0;
}
DWORD* SMELT_IMPL::smTextureLock(SMTEX tex,int l,int t,int w,int h,bool ro)
{
	glTexture *ptex=(glTexture*)tex;
	if(ptex->locpx)return NULL;
	bool fromfile=(ptex->px==NULL&&ptex->fn);
	if(fromfile)
	{
		FILE *pFile;DWORD size,rsize;char *buff;
		pFile=fopen(ptex->fn,"rb");
		if(!pFile)return 0;
		fseek(pFile,0,SEEK_END);size=ftell(pFile);rewind(pFile);
		buff=(char*)malloc(sizeof(char)*size);
		if(!buff)return 0;
		rsize=fread(buff,1,size,pFile);
		if(rsize!=size)return 0;
		int _w,_h;
		ptex->px=decodeImage((BYTE*)buff,ptex->fn,size,_w,_h);
		if(_w!=(int)ptex->rw||_h!=(int)ptex->rh)
		{delete[] ptex->px;ptex->px=NULL;}
		free(buff);
		fclose(pFile);
		if(ptex->px&&!ro){delete[] ptex->fn;ptex->fn=NULL;}
	}
	if(!ptex->px&&!ptex->isTarget)return 0;
	if(!w)w=ptex->rw;if(!h)h=ptex->rh;
	//asserts...
	ptex->roloc=ro;ptex->locx=l;ptex->locy=t;ptex->locw=w;ptex->loch=h;
	ptex->locpx=new DWORD[w*h];
	if(!ptex->isTarget)
	{
		DWORD *dst=ptex->locpx,*src=ptex->px+((t*ptex->rw)+l);
		for(int i=0;i<h;++i)//TODO: flip it...
		{
			memcpy(dst,src,w*sizeof(DWORD));
			dst+=w;src+=ptex->rw;
		}
	}
	else return 0;
	return ptex->locpx;
}
void SMELT_IMPL::smTexutreUnlock(SMTEX tex)
{
	glTexture *ptex=(glTexture*)tex;
	if(!ptex->locpx)return;
	if(!ptex->roloc)
	{
		DWORD *src=ptex->locpx,*dst=ptex->px+((ptex->locy*ptex->rw)+ptex->locx);
		for(int i=0;i<ptex->loch;++i)//TODO: flip it...
		{
			memcpy(dst,src,ptex->locw*sizeof(DWORD));
			dst+=ptex->rw;src+=ptex->locw;
		}
		if(ptex->lost)configTexture(ptex,ptex->rw,ptex->rh,ptex->px);
		else
		{
			pOpenGLDevice->glBindTexture(pOpenGLDevice->TextureTarget,ptex->name);
			pOpenGLDevice->glTexSubImage2D(pOpenGLDevice->TextureTarget,0,ptex->locx,
										  (ptex->rh-ptex->locy)-ptex->loch,ptex->locw,ptex->loch,GL_RGBA,
										  GL_UNSIGNED_BYTE,ptex->locpx);
			pOpenGLDevice->glBindTexture(pOpenGLDevice->TextureTarget,primTex?(((glTexture*)primTex)->name):0);
		}
	}
	if(ptex->fn&&ptex->roloc){delete[] ptex->px;ptex->px=NULL;}
	delete[] ptex->locpx;ptex->locpx=NULL;
	ptex->roloc=false;
	ptex->locx=ptex->locy=ptex->locw=ptex->loch=-1;
}

inline bool ispot(GLuint x){return((x&(x-1))==0);}
inline GLuint npot(GLuint x)
{
	--x;
	for(unsigned i=1;i<sizeof(GLuint)*8;i<<=1)x|=x>>i;
	return x+1;
}
DWORD* SMELT_IMPL::decodeImage(BYTE *data,const char *fn,DWORD size,int &w,int &h)
{
	w=h=0;
	DWORD *px=NULL;
	int fnlen=fn?strlen(fn):0;
	if((fnlen>5)&&(strcasecmp((fn+fnlen)-5,".rgba"))==0)//raw image... pending remove
	{
		DWORD *ptr=(DWORD*)data;
		DWORD _w=ptr[0],_h=ptr[1];
		if(((_w*_h*4)+8)==size)
		{
			w=_w;h=_h;
			px=new DWORD[w*h];
			memcpy(px,ptr+2,w*h*4);
		}
		return px;
	}
	CxImage img;
	img.Decode(data,size,CXIMAGE_FORMAT_UNKNOWN);
	if(img.IsValid())
	{
		w=img.GetWidth();h=img.GetHeight();
		px=new DWORD[w*h];
		BYTE *sptr=(BYTE*)px;
		bool atunnel=img.AlphaIsValid();
		for(int i=0;i<h;++i)
		for(int j=0;j<w;++j)
		{
			RGBQUAD rgb=img.GetPixelColor(j,i,true);
			*(sptr++)=rgb.rgbRed;
			*(sptr++)=rgb.rgbGreen;
			*(sptr++)=rgb.rgbBlue;
			*(sptr++)=atunnel?rgb.rgbReserved:0xFF;
		}
	}
	return px;
}
void SMELT_IMPL::bindTexture(glTexture *t)
{
	if(t&&t->lost)
	configTexture(t,t->rw,t->rh,t->px);
	if(((SMTEX)t)!=primTex)
	{
		pOpenGLDevice->glBindTexture(pOpenGLDevice->TextureTarget,t?t->name:0);
		primTex=(SMTEX)t;
	}
}
bool SMELT_IMPL::buildTarget(TRenderTargetList *pTarget,GLuint texid,int w,int h)
{
	bool ok=true;
	if(pOpenGLDevice->have_GL_EXT_framebuffer_object)
	{
		pOpenGLDevice->glGenFramebuffersEXT(1,&pTarget->frame);
		pOpenGLDevice->glGenRenderbuffersEXT(1,&pTarget->depth);
		pOpenGLDevice->glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,pTarget->frame);
		pOpenGLDevice->glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,pOpenGLDevice->TextureTarget,texid,0);
		pOpenGLDevice->glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,pTarget->depth);
		pOpenGLDevice->glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT,GL_DEPTH_COMPONENT24,w,h);
		pOpenGLDevice->glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,GL_DEPTH_ATTACHMENT_EXT,GL_RENDERBUFFER_EXT,pTarget->depth);
		GLenum rc=pOpenGLDevice->glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		if((rc==GL_FRAMEBUFFER_COMPLETE_EXT)&&(pOpenGLDevice->glGetError()==GL_NO_ERROR))
		{
			pOpenGLDevice->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			ok=true;
		}
		else
		{
			pOpenGLDevice->glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
			pOpenGLDevice->glDeleteRenderbuffersEXT(1,&pTarget->depth);
			pOpenGLDevice->glDeleteFramebuffersEXT(1,&pTarget->frame);
		}
		pOpenGLDevice->glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,curTarget?curTarget->frame:0);
	}
	return ok;
}
void SMELT_IMPL::configTexture(glTexture *t,int w,int h,DWORD *px,bool compressed)
{
	GLuint tex=0;
	pOpenGLDevice->glGenTextures(1,&tex);
	t->lost=false;t->name=tex;t->rw=w;t->rh=h;t->px=px;
	t->dw=t->dh=0;
	bool fromfile=(!px&&(t->fn));
	if(fromfile)
	{
		FILE *pFile;DWORD size,rsize;char *buff;
		pFile=fopen(t->fn,"rb");
		if(!pFile)return;
		fseek(pFile,0,SEEK_END);size=ftell(pFile);rewind(pFile);
		buff=(char*)malloc(sizeof(char)*size);
		if(!buff)return;
		rsize=fread(buff,1,size,pFile);
		if(rsize!=size)return;
		int _w,_h;
		px=decodeImage((BYTE*)buff,t->fn,size,_w,_h);
		if(_w!=w||_h!=h){delete[] px;px=NULL;}
		free(buff);
		fclose(pFile);
	}
	pOpenGLDevice->glBindTexture(pOpenGLDevice->TextureTarget,tex);
	if(pOpenGLDevice->TextureTarget!=GL_TEXTURE_RECTANGLE_ARB)
	{
		pOpenGLDevice->glTexParameterf(pOpenGLDevice->TextureTarget,GL_TEXTURE_MIN_LOD,0.0f);
		pOpenGLDevice->glTexParameterf(pOpenGLDevice->TextureTarget,GL_TEXTURE_MAX_LOD,0.0f);
		pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget,GL_TEXTURE_BASE_LEVEL,0);
		pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget,GL_TEXTURE_MAX_LEVEL,0);
	}
	const GLenum fmt=pOpenGLDevice->have_GL_EXT_texture_compression_s3tc&&compressed?/*GL_COMPRESSED_RGBA_S3TC_DXT5_EXT*/GL_COMPRESSED_RGBA_ARB:GL_RGBA8;
	if((pOpenGLDevice->have_GL_ARB_texture_rectangle)||(pOpenGLDevice->have_GL_ARB_texture_non_power_of_two)||(ispot(w)&&ispot(h)))
	{
		pOpenGLDevice->glTexImage2D(pOpenGLDevice->TextureTarget,0,fmt,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,px);
	}
	else
	{
		t->dw=npot(w);
		t->dh=npot(h);
		pOpenGLDevice->glTexImage2D(pOpenGLDevice->TextureTarget,0,fmt,t->dw,t->dh,0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
		pOpenGLDevice->glTexSubImage2D(pOpenGLDevice->TextureTarget,0,0,0,w,h,GL_RGBA,GL_UNSIGNED_BYTE,px);
	}
	pOpenGLDevice->glBindTexture(pOpenGLDevice->TextureTarget,primTex?(((glTexture*)primTex)->name):0);
	if (fromfile)delete[] px;
}
SMTEX SMELT_IMPL::buildTexture(int w,int h,DWORD *px)
{
	glTexture *ret=new glTexture;
	memset(ret,0,sizeof(glTexture));
	ret->lost=true;
	ret->rw=w;ret->rh=h;ret->px=px;
	return (SMTEX)ret;
}
void SMELT_IMPL::configProjectionMatrix2D(int w,int h)
{
	pOpenGLDevice->glMatrixMode(GL_PROJECTION);
	pOpenGLDevice->glLoadIdentity();
	pOpenGLDevice->glOrtho(0,(float)w,0,(float)h,0.0f,1.0f);
}
void SMELT_IMPL::configProjectionMatrix3D(int w,int h,float fov)
{
	pOpenGLDevice->glMatrixMode(GL_PROJECTION);
	pOpenGLDevice->glLoadIdentity();

	GLfloat matrix[16]={0.0f};
	float f=1./tanf(M_PI*fov/360.);
	float ar=(float)w/(float)h;
	float Near=0.1,Far=1000.;
	matrix[0]=f/ar;matrix[5]=f;
	matrix[10]=(Far+Near)/(Near-Far);matrix[11]=-1.0f;
	matrix[14]=(2*Far*Near)/(Near-Far);
	pOpenGLDevice->glMultMatrixf(matrix);
}
void SMELT_IMPL::batchOGL(bool endScene)
{
	if(vertexArray&&primcnt)
	{
		float twm=1.,thm=1.;
		if(primTex)
		{
			pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexture *ptex=(glTexture*)primTex;
			if(pOpenGLDevice->TextureTarget==GL_TEXTURE_RECTANGLE_ARB)
			{twm=ptex->rw;thm=ptex->rh;}
			else if(ptex->dw&&ptex->dh)
			{
				twm=(ptex->rw)/(float)(ptex->dw);
				thm=(ptex->rh)/(float)(ptex->dh);
			}
		}
		if(!tdmode)
		{
			float h=curTarget?curTarget->h:scrh;
			for(int i=0;i<primcnt*primType;++i)
			{
				vertexArray[i].y=h-vertexArray[i].y;
				vertexArray[i].z=-vertexArray[i].z;
			}
		}
		for(int i=0;i<primcnt*primType;++i)
		{
			vertexArray[i].tx*=twm;
			vertexArray[i].ty=(1.-vertexArray[i].ty)*thm;
			DWORD color=vertexArray[i].col;
			BYTE *col=(BYTE*)&vertexArray[i].col;
			BYTE a=((color>>24)&0xFF);
			BYTE r=((color>>16)&0xFF);
			BYTE g=((color>> 8)&0xFF);
			BYTE b=((color>> 0)&0xFF);
			col[0]=r;col[1]=g;
			col[2]=b;col[3]=a;
		}
		switch(primType)
		{
			case PRIM_LINES:
				pOpenGLDevice->glDrawArrays(GL_LINES,0,2*primcnt);
			break;
			case PRIM_TRIANGLES:
				pOpenGLDevice->glDrawArrays(GL_TRIANGLES,0,3*primcnt);
			break;
			case PRIM_QUADS:
				pOpenGLDevice->glDrawElements(GL_TRIANGLES,6*primcnt,GL_UNSIGNED_SHORT,indexBuf);
				if(false)
				for (int i=0;i<primcnt*6;i+=3)
				{
					printf("idxbuf:%d\n",indexBuf[i]);
					printf("QUAD'S TRIANGLE:\n");
#define printVertex(a) printf("(%.2f,%.2f,%.2f),0x%lX,(%.2f,%.2f)\n",a.x,a.y,a.z,a.col,a.tx,a.ty);
					printf("#%d: ",indexBuf[i+0]);printVertex(vertexBuf[indexBuf[i+0]]);
					printf("#%d: ",indexBuf[i+1]);printVertex(vertexBuf[indexBuf[i+1]]);
					printf("#%d: ",indexBuf[i+2]);printVertex(vertexBuf[indexBuf[i+2]]);
#undef printVertex
				}
			break;
		}
		primcnt=0;
	}
	if(vertexArray)vertexArray=endScene?0:vertexBuf;
}
void SMELT_IMPL::setBlend(int blend)
{
	if((blend&BLEND_ALPHABLEND)!=(primBlend&BLEND_ALPHABLEND))
	{
		if(blend&BLEND_ALPHABLEND)pOpenGLDevice->glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		else pOpenGLDevice->glBlendFunc(blend&BLEND_COLORINV?GL_ONE_MINUS_DST_COLOR:GL_SRC_ALPHA,blend&BLEND_COLORINV?GL_ZERO:GL_ONE);
	}
	if((blend&BLEND_ZWRITE)!=(primBlend&BLEND_ZWRITE))
	{
		if(blend&BLEND_ZWRITE||tdmode)pOpenGLDevice->glDepthMask(GL_TRUE);
		else pOpenGLDevice->glDepthMask(GL_FALSE);
	}
	if((blend&BLEND_COLORADD)!=(primBlend&BLEND_COLORADD))
	{
		if(blend&BLEND_COLORADD)pOpenGLDevice->glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_ADD);
		else pOpenGLDevice->glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	}
	if((blend&BLEND_COLORINV)!=(primBlend&BLEND_COLORINV))
	{
		if(blend&BLEND_COLORINV)pOpenGLDevice->glBlendFunc(GL_ONE_MINUS_DST_COLOR,GL_ZERO);
		else pOpenGLDevice->glBlendFunc(GL_SRC_ALPHA,blend&BLEND_ALPHABLEND?GL_ONE_MINUS_SRC_ALPHA:GL_ONE);
	}
	primBlend=blend;
}
void SMELT_IMPL::unloadGLEntryPoints()
{
	#define GL_PROC(ext,fn,call,ret,params) pOpenGLDevice->fn=NULL;
	#include "glimports.hpp"
	#undef GL_PROC
}
bool SMELT_IMPL::checkGLExtension(const char *extlist,const char *ext)
{
	const char *ptr=strstr(extlist,ext);
	if(ptr==NULL)return false;
	const char endchar=ptr[strlen(ext)];
	if((endchar=='\0')||(endchar==' '))return true;
	return false;
}
bool SMELT_IMPL::loadGLEntryPoints()
{
	smLog("%s:"SLINE": OpenGL: loading entry points and examining extensions...\n",GFX_SDL_SRCFN);
	pOpenGLDevice->have_base_opengl=true;
	pOpenGLDevice->have_GL_ARB_texture_rectangle=true;
	pOpenGLDevice->have_GL_ARB_texture_non_power_of_two=true;
	pOpenGLDevice->have_GL_EXT_framebuffer_object=true;
	pOpenGLDevice->have_GL_EXT_texture_compression_s3tc=false;
	pOpenGLDevice->have_GL_ARB_vertex_buffer_object=true;
	#define GL_PROC(ext,fn,call,ret,params) \
		if(pOpenGLDevice->have_##ext) \
		{ \
			if((pOpenGLDevice->fn=(_PFN_##fn) SDL_GL_GetProcAddress(#fn))==NULL) \
			{ \
				smLog("%s: Failed to load OpenGL entry point '" #fn "'\n",GFX_SDL_SRCFN); \
				pOpenGLDevice->have_##ext = false; \
			} \
		} else {}
	#include "glimports.hpp"
	#undef GL_PROC
	if (!pOpenGLDevice->have_base_opengl)
	{
		unloadGLEntryPoints();
		return false;
	}
	smLog("%s:"SLINE": GL_RENDERER: %s\n",GFX_SDL_SRCFN,(const char *)pOpenGLDevice->glGetString(GL_RENDERER));
	smLog("%s:"SLINE": GL_VENDOR: %s\n",GFX_SDL_SRCFN,(const char *)pOpenGLDevice->glGetString(GL_VENDOR));
	smLog("%s:"SLINE": GL_VERSION: %s\n",GFX_SDL_SRCFN,(const char *)pOpenGLDevice->glGetString(GL_VERSION));
	const char *verstr=(const char*)pOpenGLDevice->glGetString(GL_VERSION);
	int maj=0,min=0;
	sscanf(verstr,"%d.%d",&maj,&min);
	if((maj<1)||((maj==1)&&(min<2)))
	{
		smLog("%s:"SLINE": OpenGL implementation must be at least version 1.2.\n",GFX_SDL_SRCFN);
		unloadGLEntryPoints();
		return false;
	}
	const char *exts=(const char*)pOpenGLDevice->glGetString(GL_EXTENSIONS);
	pOpenGLDevice->have_GL_ARB_texture_rectangle=
		checkGLExtension(exts,"GL_ARB_texture_rectangle")||
		checkGLExtension(exts,"GL_EXT_texture_rectangle")||
		checkGLExtension(exts, "GL_NV_texture_rectangle");
	pOpenGLDevice->have_GL_ARB_texture_non_power_of_two=
		maj>=2||checkGLExtension(exts,"GL_ARB_texture_non_power_of_two");
	if(pOpenGLDevice->have_GL_ARB_texture_rectangle)
	{
		smLog("%s:"SLINE": OpenGL: Using GL_ARB_texture_rectangle.\n",GFX_SDL_SRCFN);
		pOpenGLDevice->TextureTarget=GL_TEXTURE_RECTANGLE_ARB;
	}
	else if(pOpenGLDevice->have_GL_ARB_texture_non_power_of_two)
	{
		smLog("%s:"SLINE": OpenGL: Using GL_ARB_texture_non_power_of_two.\n",GFX_SDL_SRCFN);
		pOpenGLDevice->TextureTarget=GL_TEXTURE_2D;
	}
	else
	{
		smLog("%s:"SLINE": OpenGL: Using power-of-two textures. This costs more memory!\n",GFX_SDL_SRCFN);
		pOpenGLDevice->TextureTarget=GL_TEXTURE_2D;
	}
	if(pOpenGLDevice->have_GL_EXT_framebuffer_object)
		pOpenGLDevice->have_GL_EXT_framebuffer_object=
		checkGLExtension(exts, "GL_EXT_framebuffer_object");
	if(pOpenGLDevice->have_GL_EXT_framebuffer_object)
		smLog("%s:"SLINE": OpenGL: Using GL_EXT_framebuffer_object.\n",GFX_SDL_SRCFN);
	else
		smLog("%s:"SLINE": OpenGL: WARNING! No render-to-texture support. Things may render badly.\n",GFX_SDL_SRCFN);
	if(pOpenGLDevice->have_GL_EXT_texture_compression_s3tc)
		pOpenGLDevice->have_GL_EXT_texture_compression_s3tc=
		checkGLExtension(exts,"GL_ARB_texture_compression")&&
	    checkGLExtension(exts,"GL_EXT_texture_compression_s3tc");
	if(pOpenGLDevice->have_GL_EXT_texture_compression_s3tc)
		smLog("%s:"SLINE": OpenGL: Using GL_EXT_texture_compression_s3tc.\n",GFX_SDL_SRCFN);
	else if (true)
	{
		smLog("%s:"SLINE": OpenGL: Texture compression disabled!\n",GFX_SDL_SRCFN);
	}
	if(pOpenGLDevice->have_GL_ARB_vertex_buffer_object)
	{
		pOpenGLDevice->have_GL_ARB_vertex_buffer_object=
		checkGLExtension(exts,"GL_ARB_vertex_buffer_object");
	}
	if(pOpenGLDevice->have_GL_ARB_vertex_buffer_object)
		smLog("%s:"SLINE": OpenGL: Using GL_ARB_vertex_buffer_object.\n",GFX_SDL_SRCFN);
	else
		smLog("%s:"SLINE": OpenGL: WARNING! No VBO support; performance may suffer.\n",GFX_SDL_SRCFN);
	return true;
}
bool SMELT_IMPL::initOGL()
{
	primTex=0;
	if(pOpenGLDevice){smLog("%s:"SLINE": Multiple initialization!\n",GFX_SDL_SRCFN);return false;}
	pOpenGLDevice=new TOpenGLDevice;
	if(!loadGLEntryPoints())return false;
	smLog("%s:"SLINE": Mode: %d x %d\n",GFX_SDL_SRCFN,scrw,scrh);
	vertexArray=NULL;textures=NULL;IndexBufferObject=0;
	if(!confOGL())return false;
	pOpenGLDevice->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if(!curTarget)SDL_GL_SwapWindow((SDL_Window*)hwnd);
	pOpenGLDevice->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if(!curTarget)SDL_GL_SwapWindow((SDL_Window*)hwnd);
	return true;
}
void SMELT_IMPL::finiOGL()
{
	while(textures)smTextureFree(textures->tex);
	while(targets)smTargetFree((SMTRG)targets);
	textures=NULL;targets=NULL;vertexArray=NULL;
	delete[] vertexBuf;vertexBuf=NULL;
	delete[] indexBuf;indexBuf=NULL;
	if(pOpenGLDevice)
	{
		if (pOpenGLDevice->have_GL_ARB_vertex_buffer_object)
		{
			if (IndexBufferObject!=0)
			{
				pOpenGLDevice->glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER,0);
				pOpenGLDevice->glDeleteBuffersARB(1,&IndexBufferObject);
				IndexBufferObject=0;
			}
		}
		delete pOpenGLDevice;
		pOpenGLDevice=NULL;
	}
}
bool SMELT_IMPL::restOGL()
{
	if(!pOpenGLDevice)return false;
	delete[] vertexBuf;vertexBuf=NULL;
	delete[] indexBuf;indexBuf=NULL;
	unloadGLEntryPoints();
	if(!loadGLEntryPoints())return false;
	if(!confOGL())return false;
	//if()return();//TODO: rest func
	return true;
}
bool SMELT_IMPL::confOGL()
{
	bindTexture(NULL);
	for(TTextureList *i=textures;i;i=i->next)
	{
		glTexture *t=(glTexture*)i->tex;
		if(!t)continue;t->lost=true;t->name=0;
	}
	TRenderTargetList *target=targets;
	while(target)
	{
		glTexture *tex=(glTexture*)target->tex;
		bindTexture(tex);bindTexture(NULL);
		buildTarget(target,tex?tex->name:0,target->w,target->h);
		target=target->next;
	}
	vertexBuf=new smVertex[VERTEX_BUFFER_SIZE];
	indexBuf=new GLushort[VERTEX_BUFFER_SIZE*6/4];
	GLushort* indices=indexBuf;
	for(int i=0,n=0;i<VERTEX_BUFFER_SIZE/4;++i)
	{
		*indices++=n;*indices++=n+1;
		*indices++=n+2;*indices++=n+2;
		*indices++=n+3;*indices++=n;
		n+=4;
	}
	if(pOpenGLDevice->have_GL_ARB_vertex_buffer_object)
	{
		pOpenGLDevice->glGenBuffersARB(1,&IndexBufferObject);
		pOpenGLDevice->glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER,IndexBufferObject);
		pOpenGLDevice->glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort)*((VERTEX_BUFFER_SIZE*6)/4),indexBuf,GL_STATIC_DRAW);
		delete[] indexBuf;indexBuf=NULL;
	}
	pOpenGLDevice->glVertexPointer(3,GL_FLOAT,sizeof(smVertex),&vertexBuf[0].x);
	pOpenGLDevice->glColorPointer(4,GL_UNSIGNED_BYTE,sizeof(smVertex),&vertexBuf[0].col);
	pOpenGLDevice->glTexCoordPointer(2,GL_FLOAT,sizeof(smVertex),&vertexBuf[0].tx);
	pOpenGLDevice->glEnableClientState(GL_VERTEX_ARRAY);
	pOpenGLDevice->glEnableClientState(GL_COLOR_ARRAY);
	pOpenGLDevice->glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	pOpenGLDevice->glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	pOpenGLDevice->glPixelStorei(GL_PACK_ALIGNMENT,1);
	pOpenGLDevice->glDisable(GL_TEXTURE_2D);
	if(pOpenGLDevice->have_GL_ARB_texture_rectangle)pOpenGLDevice->glDisable(GL_TEXTURE_RECTANGLE_ARB);
	pOpenGLDevice->glEnable(pOpenGLDevice->TextureTarget);
	pOpenGLDevice->glEnable(GL_SCISSOR_TEST);
	pOpenGLDevice->glDisable(GL_CULL_FACE);
	pOpenGLDevice->glDisable(GL_LIGHTING);
	pOpenGLDevice->glDepthFunc(GL_GEQUAL);
	pOpenGLDevice->glEnable(GL_DEPTH_TEST);
	pOpenGLDevice->glEnable(GL_BLEND);
	pOpenGLDevice->glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	pOpenGLDevice->glEnable(GL_ALPHA_TEST);
	pOpenGLDevice->glAlphaFunc(GL_GEQUAL,1.0f/255.0f);
	pOpenGLDevice->glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	//GL_REPEAT doesn't work with non-pot textures...
	pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
	primcnt=0;primType=PRIM_QUADS;primBlend=BLEND_ALPHABLEND;primTex=0;
	pOpenGLDevice->glScissor(0,0,scrw,scrh);
	pOpenGLDevice->glViewport(0,0,scrw,scrh);
	pOpenGLDevice->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	configProjectionMatrix2D(scrw,scrh);
	pOpenGLDevice->glMatrixMode(GL_MODELVIEW);
	pOpenGLDevice->glLoadIdentity();
	return true;
}
