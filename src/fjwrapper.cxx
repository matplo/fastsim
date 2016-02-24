#include "fjwrapper.h"
#include <wrapper.h>

#include <string>
#include <vector>
#include <memory>
#include <typeindex>

#include "fastjet/ClusterSequence.hh"
#include "fastjet/JetDefinition.hh"
#include "fastjet/AreaDefinition.hh"
#include "fastjet/RangeDefinition.hh"
#include "fastjet/PseudoJet.hh"

namespace fj = fastjet;

#include <iostream>
using namespace std;

Wrapper *default_wrapper()
{
	Wrapper *fjw = new Wrapper();
	double R = 1.0;
	double power = -1;
    //fj::JetDefinition *jet_def_hard = new fj::JetDefinition(fj::genkt_algorithm, R, power); // this is for signal - anti-kT
    //fjw->add(jet_def_hard);

    fj::JetDefinition jet_def_hard(fj::genkt_algorithm, R, power); // this is for signal - anti-kT
    fjw->add(jet_def_hard);

    return fjw;
}

void test_fj_wrapper()
{
	Wrapper *w = default_wrapper();
	std::vector <fj::PseudoJet> py_hard_event; // signal from pythia
	fj::JetDefinition *jd = w->get<fj::JetDefinition>();
    fj::ClusterSequence *cs_hard = new fj::ClusterSequence(py_hard_event, *jd);
    w->add(cs_hard);

    std::cout << w->get<fj::ClusterSequence>() << std::endl;

   	WrapTestClass *t = new WrapTestClass();
    std::vector< WrapContainer<WrapTestClass> > v;
    v.push_back(WrapContainer<WrapTestClass>(t, 0, "test WrapContainer"));

    w->list();

	delete w;
}

void test_wrapp()
{
	Wrapper *w = default_wrapper();
	Wrapper &wr = *w;

	fj::JetDefinition *jd = wr.get<fj::JetDefinition>();

	std::vector <fj::PseudoJet> py_hard_event; // signal from pythia
	fj::PseudoJet v(10,0,0,10);
	py_hard_event.push_back(v);
	wr.add(py_hard_event);

    fj::ClusterSequence *cs_hard = new fj::ClusterSequence(py_hard_event, *jd);
    wr.add(cs_hard);

    fj::ClusterSequence *cs = wr.get<fj::ClusterSequence>();

    std::vector <fj::PseudoJet> jets = cs->inclusive_jets();

    std::cout << "jet 0 perp = " << jets[0].perp() << std::endl;

}

