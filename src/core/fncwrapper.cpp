#include "vmrunner.hpp"
#include "fncmodules.hpp"
extern blrScriptVM *vm;
extern callStack<Idata> callStk;
extern unsigned getHash(const char *s);
void callFnc(const char* fnc)
{
	if(getHash(fnc)==getHash("randi"))
	randi(callStk.pop(),callStk.pop());
	if(getHash(fnc)==getHash("randr"))
	randr(callStk.pop(),callStk.pop());
	if(getHash(fnc)==getHash("createBullet"))
	createBullet(callStk.pop(),callStk.pop(),callStk.pop(),callStk.pop());
	if(callStk.empty())callStk.clear();
}
