#include "vmrunner.hpp"
#include "fncmodules.hpp"
extern callStack<Idata> callStk;
extern blrScriptVM *vm;
extern unsigned getHash(const char *s);
void callFnc(const char* fnc)
{
	if(getHash(fnc)==getHash("randi"))
	vm->vmSetRetVald(randi().i());
	if(getHash(fnc)==getHash("randr"))
	vm->vmSetRetValf(randr().r());
	if(getHash(fnc)==getHash("createBullet"))
	vm->vmSetRetValf(createBullet().i());
	if(callStk.empty())callStk.clear();
}
