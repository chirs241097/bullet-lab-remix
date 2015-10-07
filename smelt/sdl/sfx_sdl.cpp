// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * GFX implementation based on OpenAL
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
#include "smelt_internal.hpp"

static const char* SFX_SDL_SRCFN="smelt/sdl/sfx_sdl.cpp";
struct oggdata{const BYTE *data;DWORD size,pos;};
static void* readVorbis(const BYTE *data,const DWORD size, ALsizei *decomp_size,ALenum *fmt,ALsizei *freq);
SMSFX SMELT_IMPL::smSFXLoad(const char *path)
{
	FILE *pFile;DWORD size,rsize; char *buff;
	pFile=fopen(path,"rb");
	if(!pFile)return 0;
	fseek(pFile,0,SEEK_END);size=ftell(pFile);rewind(pFile);
	buff=(char*)malloc(sizeof(char)*size);
	if(!buff)return 0;
	rsize=fread(buff,1,size,pFile);
	if(rsize!=size)return 0;
	SMSFX ret=smSFXLoadFromMemory(buff,size);
	free(buff);
	fclose(pFile);
	return ret;
}
SMSFX SMELT_IMPL::smSFXLoadFromMemory(const char *ptr,DWORD size)
{
	if(pOpenALDevice&&!mute)
	{
		bool isOgg=size>4&&ptr[0]=='O'&&ptr[1]=='g'&&ptr[2]=='g'&&ptr[3]=='S';
		if(!isOgg)return 0;
		void *decompdata=NULL,*decomp=NULL;
		ALsizei decompsize=0,freq=0;
		ALenum fmt=AL_FORMAT_STEREO16;
		decompdata=readVorbis((const BYTE*)ptr,size,&decompsize,&fmt,&freq);
		decomp=decompdata;
		ALuint buff=0;alGenBuffers(1,&buff);
		alBufferData(buff,fmt,decomp,decompsize,freq);
		free(decompdata);return (SMSFX)buff;
	}
	return 0;
}
SMCHN SMELT_IMPL::smSFXPlay(SMSFX fx,int vol,int pan,float pitch,bool loop)
{
	if(pOpenALDevice)
	{
		ALuint src=getSource();
		if(src)
		{
			if(vol<0)vol=0;if(vol>100)vol=100;
			if(pan<-100)pan=-100;if(pan>100)pan=100;
			alSourceStop(src);
			alSourcei(src,AL_BUFFER,(ALint)fx);
			alSourcef(src,AL_GAIN,((ALfloat)vol)/100.);
			alSourcef(src,AL_PITCH,pitch);
			alSource3f(src,AL_POSITION,((ALfloat)pan)/100.,.0,.0);
			alSourcei(src,AL_LOOPING,loop?AL_TRUE:AL_FALSE);
			alSourcePlay(src);
		}
		return src;
	}
	return 0;
}
float SMELT_IMPL::smSFXGetLengthf(SMSFX fx)
{
	ALuint buff=(ALuint)fx;
	ALint freq;
	DWORD lend=smSFXGetLengthd(fx);
	alGetBufferi(buff,AL_FREQUENCY,&freq);
	float ret=lend/(float)freq;
	return ret;
}
DWORD SMELT_IMPL::smSFXGetLengthd(SMSFX fx)
{
	if(pOpenALDevice)
	{
		ALint size_b,chnc,bit;
		ALuint buff=(ALuint)fx;
		alGetBufferi(buff,AL_SIZE,&size_b);
		alGetBufferi(buff,AL_CHANNELS,&chnc);
		alGetBufferi(buff,AL_BITS,&bit);
		DWORD ret=size_b*8/(chnc*bit);
		return ret;
	}
	return -1;
}
void SMELT_IMPL::smSFXSetLoopPoint(SMSFX fx,DWORD l,DWORD r)
{
	if(pOpenALDevice)
	{
		ALint pt[2];pt[0]=l;pt[1]=r;
		alBufferiv((ALuint)fx,AL_LOOP_POINTS_SOFT,pt);
	}
}
void SMELT_IMPL::smSFXFree(SMSFX fx)
{
	if(pOpenALDevice)
	{
		ALuint buff=(ALuint)fx;
		alDeleteBuffers(1,&buff);
	}
}
void SMELT_IMPL::smChannelVol(SMCHN chn,int vol)
{
	if(pOpenALDevice)
	{
		if(vol<0)vol=0;if(vol>100)vol=100;
		alSourcef((ALuint)chn,AL_GAIN,((ALfloat)vol)/100.);
	}
}
void SMELT_IMPL::smChannelPan(SMCHN chn,int pan)
{
	if(pOpenALDevice)
	{
		if(pan<-100)pan=-100;if(pan>100)pan=100;
		alSource3f((ALuint)chn,AL_POSITION,((ALfloat)pan)/100.,.0,.0);
	}
}
void SMELT_IMPL::smChannelPitch(SMCHN chn,float pitch)
{
	if(pOpenALDevice)alSourcef((ALuint)chn,AL_PITCH,pitch);
}
void SMELT_IMPL::smChannelPause(SMCHN chn)
{
	if(pOpenALDevice)alSourcePause((ALuint)chn);
}
void SMELT_IMPL::smChannelResume(SMCHN chn)
{
	if(pOpenALDevice)alSourcePlay((ALuint)chn);
}
void SMELT_IMPL::smChannelStop(SMCHN chn)
{
	if(pOpenALDevice)alSourceStop((ALuint)chn);
}
void SMELT_IMPL::smChannelPauseAll()
{
	if(pOpenALDevice)
	{
		ALCcontext *ctx=alcGetCurrentContext();
		alcSuspendContext(ctx);
	}
}
void SMELT_IMPL::smChannelResumeAll()
{
	if(pOpenALDevice)
	{
		ALCcontext *ctx=alcGetCurrentContext();
		alcProcessContext(ctx);
	}
}
void SMELT_IMPL::smChannelStopAll()
{
	if(pOpenALDevice)
	{
		for(int i=0;i<scnt;++i)alSourceStop(src[i]);
	}
}
bool SMELT_IMPL::smChannelIsPlaying(SMCHN chn)
{
	if(pOpenALDevice)
	{
		ALint state=AL_STOPPED;
		alGetSourceiv((ALuint)chn,AL_SOURCE_STATE,&state);
		return state==AL_PLAYING;
	}
	return false;
}
float SMELT_IMPL::smChannelGetPosf(SMCHN chn)
{
	if(pOpenALDevice)
	{
		ALfloat ret;
		alGetSourcef((ALuint)chn,AL_SEC_OFFSET,&ret);
		return (float)ret;
	}
	return -1.;
}
void SMELT_IMPL::smChannelSetPosf(SMCHN chn,float pos)
{
	if(pOpenALDevice)alSourcef((ALuint)chn,AL_SEC_OFFSET,(ALfloat)pos);
}
int SMELT_IMPL::smChannelGetPosd(SMCHN chn)
{
	if(pOpenALDevice)
	{
		ALint ret;
		alGetSourcei((ALuint)chn,AL_SAMPLE_OFFSET,&ret);
		return (int)ret;
	}
	return -1;
}
void SMELT_IMPL::smChannelSetPosd(SMCHN chn,int pos)
{
	if(pOpenALDevice)alSourcei((ALuint)chn,AL_SAMPLE_OFFSET,(ALint)pos);
}

static size_t oggRead(void *ptr,size_t size,size_t nmemb,void *ds)
{
	oggdata *data=(oggdata*)ds;
	const DWORD avail=data->size-data->pos;
	size_t want=nmemb*size;
	if(want>avail)want=avail-(avail%size);
	if(want>0)
	{
		memcpy(ptr,data->data+data->pos,want);
		data->pos+=want;
	}
	return want/size;
}
static int oggSeek(void *ds,ogg_int64_t offset,int whence)
{
	oggdata *data=(oggdata*)ds;
	ogg_int64_t pos=0;
	switch(whence)
	{
		case SEEK_SET:pos=offset;break;
		case SEEK_CUR:pos=((ogg_int64_t)data->pos)+offset;break;
		case SEEK_END:pos=((ogg_int64_t)data->size)+offset;break;
		default: return -1;
	}
	if((pos<0)||(pos>((ogg_int64_t)data->size)))return -1;
	data->pos=(DWORD)pos;
	return 0;
}
static long oggLocate(void *ds)
{
	oggdata* data=(oggdata*)ds;
	return (long)data->pos;
}
static int oggClose(void *ds){return 0;}

static ov_callbacks oggrt={oggRead,oggSeek,oggClose,oggLocate};
static void* readVorbis(const BYTE *data,const DWORD size, ALsizei *decomp_size,ALenum *fmt,ALsizei *freq)
{
	oggdata adata={data,size,0};
	OggVorbis_File vf;
	memset(&vf,0,sizeof(vf));
	if(ov_open_callbacks(&adata,&vf,NULL,0,oggrt)==0)
	{
		int bs=0;
		vorbis_info *info=ov_info(&vf,-1);
		*decomp_size=0;
		*fmt=(info->channels==1)?AL_FORMAT_MONO16:AL_FORMAT_STEREO16;
		*freq=info->rate;
		if(!(info->channels==1||info->channels==2)){ov_clear(&vf);return NULL;}
		char buf[1024*16];long rc=0;size_t allocated=1024*16;
		BYTE *ret=(ALubyte*)malloc(allocated);
		while((rc=ov_read(&vf,buf,sizeof(buf),0,2,1,&bs))!=0)
		{
			if(rc>0)
			{
				*decomp_size+=rc;
				if((unsigned)*decomp_size>=allocated)
				{
					allocated<<=1;
					ALubyte *tmp=(ALubyte*)realloc(ret,allocated);
					if(!tmp){free(ret);ret=NULL;break;}
					ret=tmp;
				}
				memcpy(ret+(*decomp_size-rc),buf,rc);
			}
		}
		ov_clear(&vf);
		return ret;
	}
	return NULL;
}
ALuint SMELT_IMPL::getSource()
{
	for(int i=0;i<scnt;++i)
	{
		ALint state=AL_PLAYING;
		alGetSourceiv(src[i],AL_SOURCE_STATE,&state);
		if(!(state==AL_PLAYING||state==AL_PAUSED))return src[i];
	}
	if(scnt>=SRC_MAX)return 0;
	ALuint ret=0;
	alGenSources(1,&ret);if(!ret)return 0;
	src[scnt++]=ret;return ret;
}
bool SMELT_IMPL::initOAL()
{
	if(pOpenALDevice)return true;
	scnt=0;memset(src,0,sizeof(src));
	smLog("%s:" SLINE ": Initializing OpenAL...\n",SFX_SDL_SRCFN);
	ALCdevice *dev=alcOpenDevice(NULL);
	if(!dev)
	{
		smLog("%s:" SLINE ": alcOpenDevice() failed.\n",SFX_SDL_SRCFN);
		return mute=true;
	}
	ALint caps[]={ALC_FREQUENCY,44100,0};
	ALCcontext *ctx=alcCreateContext(dev,caps);
	if(!ctx)
	{
		smLog("%s:" SLINE ": alcCreateContext() failed.\n",SFX_SDL_SRCFN);
		return mute=true;
	}
	alcMakeContextCurrent(ctx);alcProcessContext(ctx);
	smLog("%s:" SLINE ": Done OpenAL initialization\n",SFX_SDL_SRCFN);
	smLog("%s:" SLINE ": AL_VENDOR: %s\n",SFX_SDL_SRCFN,(char*)alGetString(AL_VENDOR));
	smLog("%s:" SLINE ": AL_RENDERER: %s\n",SFX_SDL_SRCFN,(char*)alGetString(AL_RENDERER));
	smLog("%s:" SLINE ": AL_VERSION: %s\n",SFX_SDL_SRCFN,(char*)alGetString(AL_VERSION));
	const char* ext=(const char*)alGetString(AL_EXTENSIONS);
	lpp=strstr(ext,"AL_SOFT_loop_points")!=NULL;
	if(!lpp)smLog("%s:" SLINE ": Warning: loop points not supported. Please recompile with OpenAL Soft.\n",SFX_SDL_SRCFN);
	pOpenALDevice=(void*)dev;
	return true;
}
void SMELT_IMPL::finiOAL()
{
	if(pOpenALDevice)
	{
		for(int i=0;i<scnt;++i)alSourceStop(src[i]);
		alDeleteSources(scnt,src);scnt=0;memset(src,0,sizeof(src));
		ALCcontext *ctx=alcGetCurrentContext();
		ALCdevice *dev=alcGetContextsDevice(ctx);
		alcMakeContextCurrent(NULL);
		alcSuspendContext(ctx);alcDestroyContext(ctx);
		alcCloseDevice(dev);pOpenALDevice=NULL;
	}
}
