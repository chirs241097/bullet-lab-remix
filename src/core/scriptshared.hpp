#ifndef SCRIPTSHARED_H
#define SCRIPTSHARED_H
#include <cmath>
#define eps 1e-6
typedef union _Udata{//data union
	int i;float r;unsigned long d;
	_Udata(){d=0;}
}Udata;
typedef struct _Idata{//data union, with type tag and operators
	_Udata D;
	int type;//0=int, 1=float
	_Idata(){D.d=0;type=0;}
	_Idata(int _type,int _data)
	{type=_type;if(type==0)D.i=_data;else D.r=(float)_data;}
	float &r(){return D.r;}
	int &i(){return D.i;}
	unsigned long &d(){return D.d;}
	_Idata operator =(_Idata r)
	{
		if(type==1&&r.type==0)this->r()=(float)r.i();
		else if(type==0&&r.type==1)this->i()=(int)r.r();
		else this->d()=r.d();
		return *this;
	}
	_Idata operator +=(_Idata r)
	{
		if(type==1&&r.type==0)this->r()+=(float)r.i();
		if(type==0&&r.type==1)this->i()+=(int)r.r();
		if(type==0&&r.type==0)this->i()+=r.i();
		if(type==1&&r.type==1)this->r()+=r.r();
		return *this;
	}
	_Idata operator -=(_Idata r)
	{
		if(type==1&&r.type==0)this->r()-=(float)r.i();
		if(type==0&&r.type==1)this->i()-=(int)r.r();
		if(type==0&&r.type==0)this->i()-=r.i();
		if(type==1&&r.type==1)this->r()-=r.r();
		return *this;
	}
	_Idata operator *=(_Idata r)
	{
		if(type==1&&r.type==0)this->r()*=(float)r.i();
		if(type==0&&r.type==1)this->i()*=(int)r.r();
		if(type==0&&r.type==0)this->i()*=r.i();
		if(type==1&&r.type==1)this->r()*=r.r();
		return *this;
	}
	_Idata operator /=(_Idata r)
	{
		if(type==1&&r.type==0)this->r()/=(float)r.i();
		if(type==0&&r.type==1)this->i()/=(int)r.r();
		if(type==0&&r.type==0)this->i()/=r.i();
		if(type==1&&r.type==1)this->r()/=r.r();
		return *this;
	}
	_Idata operator %=(_Idata r)
	{
		if(type==1&&r.type==0)throw;
		if(type==0&&r.type==1)throw;
		if(type==0&&r.type==0)this->i()%=r.i();
		if(type==1&&r.type==1)throw;
		return *this;
	}
	_Idata operator &=(_Idata r)
	{
		if(type==1&&r.type==0)throw;
		if(type==0&&r.type==1)throw;
		if(type==0&&r.type==0)this->i()&=r.i();
		if(type==1&&r.type==1)throw;
		return *this;
	}
	_Idata operator |=(_Idata r)
	{
		if(type==1&&r.type==0)throw;
		if(type==0&&r.type==1)throw;
		if(type==0&&r.type==0)this->i()|=r.i();
		if(type==1&&r.type==1)throw;
		return *this;
	}
	_Idata operator ^=(_Idata r)
	{
		if(type==1&&r.type==0)throw;
		if(type==0&&r.type==1)throw;
		if(type==0&&r.type==0)this->i()^=r.i();
		if(type==1&&r.type==1)throw;
		return *this;
	}
	_Idata operator ~()
	{
		if(type==1)throw;
		if(type==0)i()=~i();
		return *this;
	}
	_Idata operator ++()
	{
		if(type==1)throw;
		if(type==0)i()=i()+1;
		return *this;
	}
	_Idata operator --()
	{
		if(type==1)throw;
		if(type==0)i()=i()-1;
		return *this;
	}
	bool ltz()
	{
		if(type==0)return i()<0;
		if(type==1)return fabs(r())>eps&&r()<0;
		throw;
	}
	bool elz()
	{
		if(type==0)return i()<=0;
		if(type==1)return fabs(r())<eps||(fabs(r())>eps&&r()<0);
		throw;
	}
	bool gtz()
	{
		if(type==0)return i()>0;
		if(type==1)return fabs(r())>eps&&r()>0;
		throw;
	}
	bool egz()
	{
		if(type==0)return i()>=0;
		if(type==1)return fabs(r())<eps||(fabs(r())>eps&&r()>0);
		throw;
	}
	bool eqz()
	{
		if(type==0)return i()==0;
		if(type==1)return fabs(r())<eps;
		throw;
	}
	bool nez()
	{
		if(type==0)return i()!=0;
		if(type==1)return fabs(r())>eps;
		throw;
	}
}Idata;
typedef struct _SPara{Udata data;int type;char *fnc;}SPara;//parameters
typedef struct _SInst//instructions
{
	int id;
	SPara para1,para2;
}SInst;
#endif
