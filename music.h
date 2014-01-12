//Chrisoft Bullet Lab Remix HGE
//In Game Music Implementations
//"Copyleft" Chrisoft 2013
HEFFECT Mus;
HCHANNEL Muc;
int lpst,lped;
static const char* MUSIC_H_FN="music.h";

void Music_Init(char* file)
{
	Mus=hge->Effect_Load(file);
}
void Music_Play()
{
	Muc=hge->Effect_PlayEx(Mus,100,0,1.0,true);
}
void Music_Update()
{
	if (!lpst||!lped)return;
	int Mucpos=hge->Channel_GetPos_BySample(Muc);
	if (Mucpos>=lped)hge->Channel_SetPos_BySample(Muc,lpst);
}
void Music_Stop()
{
	hge->Channel_Stop(Muc);
}
void Music_Pause()
{
	hge->Channel_Pause(Muc);
}
void Music_Resume()
{
	hge->Channel_Resume(Muc);
}
