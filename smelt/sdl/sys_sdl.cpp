// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * SMELT system implementation
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
#include "smelt_internal.hpp"
static const char* SYS_SDL_SRCFN="smelt/sdl/sys_sdl.cpp";
int refcnt=0;
SMELT_IMPL *pSM=0;

SMELT* smGetInterface(int apilevel)
{
	if(apilevel==SMELT_APILEVEL)
	return(SMELT*)SMELT_IMPL::getInterface();
	else return 0;
}

SMELT_IMPL* SMELT_IMPL::getInterface()
{
	if(!pSM)pSM=new SMELT_IMPL();
	++refcnt;return pSM;
}

void SMELT_IMPL::smRelease()
{
	--refcnt;
	if(!refcnt)
	{
		if(pSM->hwnd)pSM->smFinale();
		delete pSM;pSM=0;
	}
}

bool SMELT_IMPL::smInit()
{
	smLog("%s:"SLINE": Initalizing SMELT...\n",SYS_SDL_SRCFN);
	smLog("%s:"SLINE": SMELT api version %d\n",SYS_SDL_SRCFN,SMELT_APILEVEL);
	time_t t=time(NULL);
	smLog("%s:"SLINE": Date %s",SYS_SDL_SRCFN,asctime(localtime(&t)));
#ifdef WIN32
	OSVERSIONINFO os_ver; MEMORYSTATUS mem_st;
	os_ver.dwOSVersionInfoSize=sizeof(os_ver);
	GetVersionEx(&os_ver);
	smLog("%s:"SLINE": OS: Windows %ld.%ld.%ld\n", SYS_SDL_SRCFN,os_ver.dwMajorVersion,os_ver.dwMinorVersion,os_ver.dwBuildNumber);

	int CPUInfo[4]={-1};
	__cpuid(CPUInfo,0x80000000);
	unsigned int nExIds=CPUInfo[0];
	char *cpuName,*loced;cpuName=calloc(0x40,sizeof(char));loced=cpuName;
	for(unsigned int i=0x80000000;i<=nExIds;++i)
    {
		__cpuid(CPUInfo, i);
		if(i==0x80000002)
			memcpy(cpuName,CPUInfo,sizeof(CPUInfo));
		else if(i==0x80000003)
			memcpy(cpuName+16,CPUInfo,sizeof(CPUInfo));
		else if(i==0x80000004)
		memcpy(cpuName+32, CPUInfo, sizeof(CPUInfo));
	}
	while(*cpuName=' ')++cpuName;
	smLog("%s:"SLINE": CPU: %s\n", SYS_SDL_SRCFN,cpuName);
	free(loced);

	GlobalMemoryStatus(&mem_st);
	smLog("%s:"SLINE": Memory: %ldK total, %ldK free\n", SYS_SDL_SRCFN,mem_st.dwTotalPhys/1024L,mem_st.dwAvailPhys/1024L);
#else
	system("uname -svm > os.out");
	char osv[100];FILE* a=fopen("os.out","r");fgets(osv,100,a);fclose(a);
	osv[strlen(osv)-1]='\0';
	smLog("%s:"SLINE": OS: %s\n",SYS_SDL_SRCFN,osv);
	system("rm os.out");

	system("cat /proc/cpuinfo | grep name -m 1 > cpu.out");
	a=fopen("cpu.out","r");fgets(osv,100,a);fclose(a);
	osv[strlen(osv)-1]='\0';char *ptr=osv;while(*ptr!=':')++ptr;ptr+=2;
	smLog("%s:"SLINE": CPU: %s\n",SYS_SDL_SRCFN,osv);
	system("rm cpu.out");

	a=fopen("/proc/meminfo","r");
	unsigned totalm,freem;
	fscanf(a,"MemTotal: %u kB\n",&totalm);
	fscanf(a,"MemFree: %u kB\n",&freem);
	smLog("%s:"SLINE": RAM: %ukB installed, %ukB free\n",SYS_SDL_SRCFN,totalm,freem);
	fclose(a);
#endif
	if(SDL_Init(SDL_INIT_VIDEO)==-1)
	{
		smLog("%s:"SLINE": SDL_Init() failed with error %s\n",SYS_SDL_SRCFN,SDL_GetError());
		return false;
	}
	if(SDL_GL_LoadLibrary(NULL)==-1)
	{
		smLog("%s:"SLINE": SDL_GL_LoadLibrary() failed with error %s\n",SYS_SDL_SRCFN,SDL_GetError());
		return false;
	}
	SDL_DisplayMode vidinfo;
	if(SDL_GetDesktopDisplayMode(0,&vidinfo))
	{
		smLog("%s:"SLINE": SDL_GetDesktopDisplayMode() failed with error %s\n",SYS_SDL_SRCFN,SDL_GetError());
		SDL_Quit();
		return false;
	}
	dispw=vidinfo.w;disph=vidinfo.h;
	smLog("%s:"SLINE": Screen: %d x %d\n",SYS_SDL_SRCFN,dispw,disph);
	Uint32 flags=SDL_WINDOW_OPENGL;
	if(!windowed)flags|=SDL_WINDOW_FULLSCREEN;
	SDL_Window *screen=SDL_CreateWindow(winTitle,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,scrw,scrh,flags);
	hwnd=(void*)screen;
	glContext=SDL_GL_CreateContext(screen);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetSwapInterval(vsync?1:0);
	if(!hwnd)
	{
		smLog("%s:"SLINE": SDL_CreateWindow() failed with error %s\n",SYS_SDL_SRCFN,SDL_GetError());
		SDL_Quit();
		return false;
	}
	if(!windowed)
	{
		mouseOver=true;
		if(!pSM->Active)pSM->focusChange(true);
	}
	SDL_ShowCursor(hideMouse?SDL_DISABLE:SDL_ENABLE);
	initInput();
	if(!initOGL()){smFinale();return false;}
	if(!initOAL()){smFinale();return false;}
	t0=SDL_GetTicks();dt=fcnt=0;fps=.0;
	updateFPSDelay=.0;
	return true;
}

void SMELT_IMPL::smFinale()
{
	smLog("%s:"SLINE": Cleaning up...\n",SYS_SDL_SRCFN);
	clearQueue();finiOAL();finiOGL();
	SDL_Quit();hwnd=0;
}

void SMELT_IMPL::smMainLoop()
{
	if(!hwnd)return smLog("%s:"SLINE": Error: SMELT is not initialized.\n",SYS_SDL_SRCFN);
	if(!pUpdateFunc) return smLog("%s:"SLINE": UpdateFunc is not defined.\n",SYS_SDL_SRCFN);
	Active=true;
	for(;;)
	{
		SDL_Event e;
		bool loopcont=true;
		while(SDL_PollEvent(&e)&&loopcont)loopcont=procSDLEvent(e);
		if(!loopcont)break;
		if(Active||noSuspend)
		{
			Uint32 sdlticks;
			do{sdlticks=SDL_GetTicks();dt=sdlticks-t0;}while(dt<1);
			if(dt>=fixDelta)
			{
				timeDelta=dt/1000.;
				if(timeDelta>0.2)timeDelta=fixDelta?fixDelta/1000.:.01;
				++fcnt;updateFPSDelay+=timeDelta;t0=sdlticks;timeS+=timeDelta;
				if(updateFPSDelay>1){fps=fcnt/updateFPSDelay;updateFPSDelay=.0;fcnt=0;}
				if(pUpdateFunc())break;
				for(int i=1;i<=255;++i)keylst[i]=((keyz[i]&4)!=0);
				clearQueue();
			}
			else
			if(fixDelta&&dt+3<fixDelta)SDL_Delay(1);
		}else SDL_Delay(1);
	}
	clearQueue();Active=false;
}
void SMELT_IMPL::smUpdateFunc(smHook func){pUpdateFunc=func;}
void SMELT_IMPL::smUnFocFunc(smHook func){pUnFocFunc=func;}
void SMELT_IMPL::smFocFunc(smHook func){pFocFunc=func;}
void SMELT_IMPL::smQuitFunc(smHook func){pQuitFunc=func;}
void SMELT_IMPL::smWinTitle(const char *title){strcpy(winTitle,title);}
bool SMELT_IMPL::smIsActive(){return Active;}
void SMELT_IMPL::smNoSuspend(bool para){noSuspend=para;}
void SMELT_IMPL::smVidMode(int resX,int resY,bool _windowed)
{
	if(vertexArray)return;
	if(!pOpenGLDevice)scrw=resX,scrh=resY,windowed=_windowed;
	else if(windowed!=_windowed)
	{
		windowed=_windowed;
		Uint32 flags=SDL_WINDOW_OPENGL;
		if(!windowed)flags|=SDL_WINDOW_FULLSCREEN;
		SDL_SetWindowFullscreen((SDL_Window*)hwnd,flags);
		restOGL();
		if(!windowed){mouseOver=true;if(!pSM->Active)pSM->focusChange(true);}
	}
}
void SMELT_IMPL::smLogFile(const char* path)
{
	strcpy(logFile,path);
	FILE *tf=fopen(logFile,"w");
	if(!tf)*logFile=0;else fclose(tf);
}
void SMELT_IMPL::smLog(const char* format,...)
{
	va_list ap;
	va_start(ap,format);vfprintf(stderr,format,ap);va_end(ap);
	FILE *logf=fopen(logFile,"a");if(!logf)return;
	va_start(ap,format);vfprintf(logf,format,ap);va_end(ap);
	fclose(logf);
}
void SMELT_IMPL::smScreenShot(const char* path)
{
	if(pOpenGLDevice)
	{
		#if SDL_BYTEORDER==SDL_BIG_ENDIAN
		const Uint32 rmask=0xFF0000;
		const Uint32 gmask=0x00FF00;
		const Uint32 bmask=0x0000FF;
		#else
		const Uint32 rmask=0x0000FF;
		const Uint32 gmask=0x00FF00;
		const Uint32 bmask=0xFF0000;
		#endif
		pOpenGLDevice->glFinish();
		SDL_Surface *screen=SDL_GetWindowSurface((SDL_Window*)hwnd);
		SDL_Surface *surface=SDL_CreateRGBSurface(SDL_SWSURFACE,screen->w,screen->h,24,rmask,gmask,bmask,0);
		pOpenGLDevice->glReadPixels(0,0,screen->w,screen->h,GL_RGB,GL_UNSIGNED_BYTE,surface->pixels);
		flipSDLSurface(surface->pitch,surface->h,surface->pixels);
		SDL_SaveBMP(surface,path);
		SDL_FreeSurface(surface);
	}
}
void SMELT_IMPL::smSetFPS(int fps)
{
	vsync=(fps==FPS_VSYNC);
	if(pOpenGLDevice)SDL_GL_SetSwapInterval(vsync?1:0);
	if(fps>0)fixDelta=1000./fps;else fixDelta=0;
}
float SMELT_IMPL::smGetFPS(){return fps;}
float SMELT_IMPL::smGetDelta(){return timeDelta;}
float SMELT_IMPL::smGetTime(){return timeS;}

SMELT_IMPL::SMELT_IMPL()
{
	hwnd=NULL;Active=false;memset(curError,0,sizeof(curError));
	pUpdateFunc=pUnFocFunc=pFocFunc=pQuitFunc=NULL;
	Icon=NULL;strcpy(winTitle,"untitled");scrw=dispw=800;scrh=disph=600;
	windowed=vsync=false;memset(logFile,0,sizeof(logFile));
	limfps=0;hideMouse=true;noSuspend=false;
	pOpenGLDevice=NULL;targets=NULL;curTarget=NULL;
	textures=NULL;vertexArray=NULL;vertexBuf=NULL;indexBuf=NULL;primTex=0;
	pOpenALDevice=NULL;mute=false;inpQueue=NULL;posz=0;posx=posy=.0;
	mouseOver=true;captured=false;keymods=KMOD_NONE;zbufenabled=false;
	timeDelta=updateFPSDelay=fps=.0;fcnt=dt=fixDelta=0;
}
void SMELT_IMPL::focusChange(bool actif)
{
	Active=actif;
	if(actif)pFocFunc?pFocFunc():0;
	else pUnFocFunc?pUnFocFunc():0;
}
bool SMELT_IMPL::procSDLEvent(const SDL_Event &e)
{
	switch(e.type)
	{
		case SDL_WINDOWEVENT:
			switch(e.window.event)
			{
				case SDL_WINDOWEVENT_EXPOSED:
					//redraw, omitted.
				break;
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					pSM->focusChange(true);
				break;
				case SDL_WINDOWEVENT_FOCUS_LOST:
					pSM->focusChange(false);
				break;
				case SDL_WINDOWEVENT_ENTER:
					mouseOver=true;
				break;
				case SDL_WINDOWEVENT_LEAVE:
					mouseOver=false;
				break;
			}
		break;
		case SDL_QUIT:
			if(pSM->pQuitFunc&&!pSM->pQuitFunc())break;
		return false;
		case SDL_KEYDOWN:
			keymods=(SDL_Keymod)e.key.keysym.mod;
			if((keymods&KMOD_ALT)&&((e.key.keysym.sym==SDLK_RETURN)||(e.key.keysym.sym==SDLK_KP_ENTER)))
			{smVidMode(scrw,scrh,!windowed);break;}
			pSM->buildEvent(INPUT_KEYDOWN,e.key.keysym.scancode,0,0,-1,-1);
		break;
		case SDL_KEYUP:
			keymods=(SDL_Keymod)e.key.keysym.mod;
			pSM->buildEvent(INPUT_KEYUP,e.key.keysym.scancode,0,0,-1,-1);
		break;
		case SDL_MOUSEBUTTONDOWN:
			if(e.button.button==SDL_BUTTON_LEFT)
			pSM->buildEvent(INPUT_MBUTTONDOWN,SMK_LBUTTON,0,0,e.button.x,e.button.y);
			if(e.button.button==SDL_BUTTON_RIGHT)
			pSM->buildEvent(INPUT_MBUTTONDOWN,SMK_RBUTTON,0,0,e.button.x,e.button.y);
			if(e.button.button==SDL_BUTTON_MIDDLE)
			pSM->buildEvent(INPUT_MBUTTONDOWN,SMK_MBUTTON,0,0,e.button.x,e.button.y);
		break;
		case SDL_MOUSEBUTTONUP:
			if(e.button.button==SDL_BUTTON_LEFT)
			pSM->buildEvent(INPUT_MBUTTONUP,SMK_LBUTTON,0,0,e.button.x,e.button.y);
			if(e.button.button==SDL_BUTTON_RIGHT)
			pSM->buildEvent(INPUT_MBUTTONUP,SMK_RBUTTON,0,0,e.button.x,e.button.y);
			if(e.button.button==SDL_BUTTON_MIDDLE)
			pSM->buildEvent(INPUT_MBUTTONUP,SMK_MBUTTON,0,0,e.button.x,e.button.y);
		break;
		case SDL_MOUSEWHEEL:
			if(e.wheel.y>0)pSM->buildEvent(INPUT_MOUSEWHEEL,1,0,0,e.button.x,e.button.y);
			if(e.wheel.y<0)pSM->buildEvent(INPUT_MOUSEWHEEL,-1,0,0,e.button.x,e.button.y);
		break;
		case SDL_MOUSEMOTION:
			pSM->buildEvent(INPUT_MOUSEMOVE,0,0,0,e.motion.x,e.motion.y);
		break;
	}
	return true;
}
void SMELT_IMPL::flipSDLSurface(int p,int h,void* px)
{
	void* temp_row;
	int height_div_2;
	temp_row=(void*)malloc(p);
	//assert(temp_row);
	height_div_2=(int)(h*.5);
	for(int i=0;i<height_div_2;++i)
	{
		memcpy((Uint8*)temp_row,(Uint8*)(px)+p*i,p);
		memcpy((Uint8*)(px)+p*i,(Uint8*)(px)+p*(h-i-1),p);
		memcpy((Uint8*)(px)+p*(h-i-1),temp_row,p);
	}
	free(temp_row);
}
