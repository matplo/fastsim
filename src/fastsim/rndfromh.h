#ifndef __RANDOMFROMH__HH
#define __RANDOMFROMH__HH

class TH1;

class RndFromH
{
public:
	RndFromH(const char *fname, const char *hname);
	virtual ~RndFromH();
	bool Accept(double) const;
private:
	RndFromH() {;}
	RndFromH(const RndFromH &) {;}
	TH1 		*fH;	
};

#endif //__RANDOMFROMH__HH