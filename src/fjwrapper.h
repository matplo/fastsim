#ifndef __FJWRAPPER__HH
#define __FJWRAPPER__HH

class Wrapper;

#include <vector>
#include "fastjet/PseudoJet.hh"
#include "fastjet/AreaDefinition.hh"
#include "fastjet/JetDefinition.hh"

class FJWrapper
{
public:
    FJWrapper();
    ~FJWrapper();

    void delete_wrappers();
    void clear_input();
    void add_input(fastjet::PseudoJet v);
    void add_input(std::vector<fastjet::PseudoJet> vv);
    void reset();

    void set_algorithm(fastjet::JetAlgorithm a) {fAlgorithm = a;}
    void set_R(double r)                        {fR = r;}
    void set_power(double p)                    {fPower = p;}
    void set_abs_eta_max(double etamax)         {fAbsEtaMax = etamax;}
    void set_ghost_max_rap(double ghmaxrap)     {fGhostMaxRap = ghmaxrap;}
    void set_area_type(fastjet::AreaType at)    {fAreaType = at;}

    Wrapper* run(double overrideR = 0);
    Wrapper* run_warea(double overrideR = 0);
    Wrapper* run_bg_estimator(int nhardignore = 2, double overrideR = 0);

private:
    std::vector<Wrapper *>             fWrappers; // this is for memory management
    std::vector<fastjet::PseudoJet>     fInput;
    fastjet::JetAlgorithm               fAlgorithm;
    double                              fR;
    double                              fPower;
    double                              fAbsEtaMax;
    double                              fGhostMaxRap;
    fastjet::AreaType                   fAreaType;
};

void test_wrapp();

#endif // __FJWRAPPER__HH
