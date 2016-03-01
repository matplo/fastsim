#include "fjwrapper.h"
#include <wrapper/wrapper.h>

#include <string>
#include <vector>
#include <memory>
#include <typeindex>

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/JetDefinition.hh"
#include "fastjet/AreaDefinition.hh"
#include "fastjet/RangeDefinition.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/Selector.hh"
#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
#include "fastjet/tools/Subtractor.hh"

namespace fj = fastjet;

#include <iostream>
using namespace std;

FJWrapper::FJWrapper()
    : fWrappers()
    , fInput()
    , fAlgorithm(fj::genkt_algorithm)
    , fR(0.4)
    , fPower(-1)
    , fAbsEtaMax(2.)
    , fGhostMaxRap(2.)
    , fAreaType(fj::active_area)
{
    reset();
}

FJWrapper::~FJWrapper()
{
    reset();
}

void FJWrapper::delete_wrappers()
{
    for (unsigned int i = 0; i < fWrappers.size(); i++)        
    {
        delete fWrappers[i];
    }
    fWrappers.clear();        
}

void FJWrapper::clear_input()
{
    fInput.clear();        
}

void FJWrapper::add_input(fj::PseudoJet v)
{
    fInput.push_back(v);
}

void FJWrapper::add_input(std::vector<fj::PseudoJet> vv)
{
    for (unsigned int i = 0; i < vv.size(); i++)
    {
        fInput.push_back(vv[i]);
    }
}

void FJWrapper::reset()
{
    delete_wrappers();
    clear_input();

    fAlgorithm   = fj::genkt_algorithm;
    fPower       = -1;
    fR           = 0.4;
    fAbsEtaMax   = 2.;
    fGhostMaxRap = 2.;
    fAreaType    = fj::active_area;
}

Wrapper* FJWrapper::run(double overrideR /*= 0*/)
{
    return run(fInput, overrideR);
}

Wrapper* FJWrapper::run(std::vector<fastjet::PseudoJet> &inv, double overrideR /*= 0*/)
{
    double r = fR;
    if (overrideR > 0)
        r = overrideR;
    fj::JetDefinition       *jet_def = 0;
    if (fAlgorithm == fj::genkt_algorithm)
        jet_def = new fj::JetDefinition(fAlgorithm, r, fPower);
    else
        jet_def = new fj::JetDefinition(fAlgorithm, r);
    fj::ClusterSequence *cs        = new fj::ClusterSequence(inv, *jet_def);

    Wrapper *w = new Wrapper();
    w->add(jet_def);
    w->add(cs);

    fWrappers.push_back(w);

    return w;
}

Wrapper* FJWrapper::run_warea(double overrideR /*= 0*/)
{
    return run_warea(fInput, overrideR);
}

Wrapper* FJWrapper::run_warea(std::vector<fastjet::PseudoJet> &inv, double overrideR /*= 0*/)
{
    double r = fR;
    if (overrideR > 0)
        r = overrideR;
    fj::JetDefinition       *jet_def = 0;
    if (fAlgorithm == fj::genkt_algorithm)
        jet_def = new fj::JetDefinition(fAlgorithm, r, fPower);
    else
        jet_def = new fj::JetDefinition(fAlgorithm, r);
    fj::GhostedAreaSpec     *area_spec = new fj::GhostedAreaSpec(fGhostMaxRap);
    fj::AreaDefinition      *area_def  = new fj::AreaDefinition(fAreaType, *area_spec);
    fj::ClusterSequenceArea *cs        = new fj::ClusterSequenceArea(inv, *jet_def, *area_def);

    Wrapper *w = new Wrapper();
    w->add(jet_def);
    w->add(area_spec);
    w->add(area_def);
    w->add(cs);

    fWrappers.push_back(w);

    return w;
}    

Wrapper* FJWrapper::run_bg_estimator(int nhardignore /*= 2*/, double overrideR /* = 0*/)
{
    return run_bg_estimator(fInput, nhardignore, overrideR);
}

Wrapper* FJWrapper::run_bg_estimator(std::vector<fastjet::PseudoJet> &inv, int nhardignore /*= 2*/, double overrideR /* = 0*/)
{
    double r = fR;
    if (overrideR > 0)
        r = overrideR;
    // Run the fastjet background estimation - kT
    // define the area etc... - do the same for anti-kt
    fj::JetDefinition *jet_def_bkgd                  = new fj::JetDefinition(fj::kt_algorithm, r);
    fj::AreaDefinition *area_def_bkgd                = new fj::AreaDefinition(fj::active_area_explicit_ghosts, fj::GhostedAreaSpec(fGhostMaxRap));
    fj::Selector selector                            = fj::SelectorAbsRapMax(fGhostMaxRap) * (!fj::SelectorNHardest(nhardignore));
    fj::JetMedianBackgroundEstimator *bkgd_estimator = new fj::JetMedianBackgroundEstimator(selector, *jet_def_bkgd, *area_def_bkgd);

    // To help manipulate the background estimator, we also provide a
    // transformer that allows to apply directly the background
    // subtraction on the jets. This will use the background estimator
    // to compute rho for the jets to be subtracted.
    // ----------------------------------------------------------
    fj::Subtractor *subtractor = new fj::Subtractor(bkgd_estimator);

    // Finally, once we have an event, we can just tell the background
    // estimator to use that list of particles
    // This could be done directly when declaring the background
    // estimator but the usage below can more easily be accomodated to a
    // loop over a set of events.
    // ----------------------------------------------------------
    bkgd_estimator->set_particles(inv);

    //double rho   = bkgd_estimator.rho();
    //double sigma = bkgd_estimator.sigma();

    Wrapper *w = new Wrapper();
    w->add(jet_def_bkgd);
    w->add(area_def_bkgd);
    w->add(bkgd_estimator);
    w->add(subtractor);

    fWrappers.push_back(w);

    return w;
}

////

void test_wrapp()
{
    FJWrapper w;
    w.add_input(fj::PseudoJet(10,0,0,10));

    Wrapper *jf = w.run();
    std::vector<fj::PseudoJet> v = jf->get<fj::ClusterSequence>()->inclusive_jets();
    std::cout << "perp of a jet: " << v[0].perp() << endl;
}
