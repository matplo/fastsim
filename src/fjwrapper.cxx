#include "fjwrapper.h"

#include <fastjet/ClusterSequence.hh>

#include <iostream>
using namespace std;

Wrapper *default_wrapper()
{
	Wrapper *fjw = new Wrapper("fastjet");
	double R = 1.0;
	double power = -1;
    fj::JetDefinition *jet_def_hard = new fj::JetDefinition(fj::genkt_algorithm, R, power); // this is for signal - anti-kT
    fjw->add(jet_def_hard, "JetDefinition");
    return fjw;
}

void test_fj_wrapper()
{
	Wrapper *w = default_wrapper();

	std::vector <fj::PseudoJet> py_hard_event; // signal from pythia

	fj::JetDefinition *jd = (fj::JetDefinition*)w->get("JetDefinition");

    fj::ClusterSequence *cs_hard = new fj::ClusterSequence(py_hard_event, *jd);

    w->add(cs_hard, "ClusterSequence");

    cout << w->getCS() << endl;

	delete w;
}