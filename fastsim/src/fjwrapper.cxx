#include "fjwrapper.h"
#include "tests.h"

namespace fj = fastjet;

#include <iostream>
using namespace std;

Wrapper::~Wrapper()
{
	;
}

unsigned int Wrapper::addCS(fastjet::ClusterSequence *cs, const char *name /*= "ClusterSequence"*/)
{
	unsigned int uid = fUniqueIDs.size();
	fCSv.push_back(Container<fj::ClusterSequence>(cs, name, uid));
	fUniqueIDs.push_back(uid);
	return uid;
}

fastjet::ClusterSequence * Wrapper::getCS(const char *name /*= "ClusterSequence"*/)
{
	for (unsigned int i = 0; i < fCSv.size(); i++)
	{
		if (fCSv[i].IsNamed(name))
			return fCSv[i].get();
	}
	return 0x0;
}

unsigned int Wrapper::addJD(fastjet::JetDefinition *JD, const char *name /*= "JetDefinition"*/)
{
	unsigned int uid = fUniqueIDs.size();
	fJDv.push_back(Container<fj::JetDefinition>(JD, name, uid));
	fUniqueIDs.push_back(uid);
	return uid;
}

fastjet::JetDefinition * Wrapper::getJD(const char *name /*= "JetDefinition"*/)
{
	for (unsigned int i = 0; i < fJDv.size(); i++)
	{
		if (fJDv[i].IsNamed(name))
			return fJDv[i].get();
	}
	return 0x0;
}

Wrapper *default_wrapper()
{
	Wrapper *fjw = new Wrapper("fastjet");
	double R = 1.0;
	double power = -1;
    fj::JetDefinition *jet_def_hard = new fj::JetDefinition(fj::genkt_algorithm, R, power); // this is for signal - anti-kT
    fjw->addJD(jet_def_hard, "JetDefinition");
    return fjw;
}

void test_fj_wrapper()
{
	Wrapper *w = default_wrapper();

	std::vector <fj::PseudoJet> py_hard_event; // signal from pythia

	fj::JetDefinition *jd = w->getJD("JetDefinition");

    fj::ClusterSequence *cs_hard = new fj::ClusterSequence(py_hard_event, *jd);

    w->addCS(cs_hard, "ClusterSequence");

    std::cout << w->getCS() << std::endl;

   	TestGC *t = new TestGC();
    std::vector< Container<TestGC> > v;
    v.push_back(Container<TestGC>(t, "test container", 0));

	delete w;
}

void test_wrapp()
{
	double R = 1.0;
	double power = -1;
    fj::JetDefinition *jd = new fj::JetDefinition(fj::genkt_algorithm, R, power); // this is for signal - anti-kT

	Wrapp wr;
	wr.add(new TestGC());
	//wr.add(jd);

	TestGC *x = 0;
	wr.get(&x);
	std::cout << "x pointer is:" << x << std::endl;
	x->test_call();
	std::cout << "x pointer is:" << x << std::endl;

	wr.get(&jd);
	std::cout << "jd pointer is:" << jd << std::endl;
}
