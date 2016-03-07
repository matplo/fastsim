/// this is from the main event loop pythia_run - demo of possibilities

	GenerUtil::pythia_fj_record pyrecord;

		// particles into vectors
		pyrecord.clear();
		pyrecord.fill_event(pythia);

		// py8 particles into TParticles
		// std::vector<TParticle> v = GenerUtil::py8_event_to_vector(ppythia, true); //only final
		// for (unsigned int i = 0; i < v.size(); i++) std::cout << v[i].GetName() << endl;
    	std::vector<TParticle> tpevent = GenerUtil::py8_event_to_vector(ppythia);
    	revent.FillBranch("parts", tpevent);
    	std::vector<TParticle> alicharged = aliresp(tpevent);
    	revent.FillBranch("aliparts", alicharged);

	    std::vector<fastjet::PseudoJet> pyfr = resp(pyrecord.f);

		// run jet finders
	    FJWrapper w;
	    //Wrapper *jf = w.run( pyrecord.f );
	    Wrapper *jf = w.run( pyfr, jetR );
	    std::vector<fj::PseudoJet> j = jf->get<fj::ClusterSequence>()->inclusive_jets();

	    resp.SetEtaAbsCut(1. - jetR);
	    std::vector<fj::PseudoJet> jcut = resp(j);
	    // std::cout << "before: " << j.size() << " after: " << jcut.size() << std::endl;
    	// std::cout << " event #" << iEvent << " => #jets: " << v.size() << endl;
    	revent.FillBranch("j", fj::sorted_by_pt(j));
    	revent.FillBranch("jcut", fj::sorted_by_pt(jcut));

		std::vector<fj::PseudoJet> sjets;
	    for (unsigned int i = 0; i < j.size(); i++)
	    {
	    	std::vector<fj::PseudoJet> cons = j[i].constituents();
		    Wrapper *sj = w.run(cons, 0.1);
		    std::vector<fj::PseudoJet> v = fj::sorted_by_pt(sj->get<fj::ClusterSequence>()->inclusive_jets());
		    sjets.insert(sjets.end(), v.begin(), v.end());
	    }
    	revent.FillBranch("sjs", sjets);

	    Wrapper *jfr = w.run(pyrecord.f, 0.1);
    	revent.FillBranch("jr", fj::sorted_by_pt(jfr->get<fj::ClusterSequence>()->inclusive_jets()));

	    Wrapper *jfvc = w.run(pyrecord.fv_charged);
	    std::vector<fj::PseudoJet> jvc = jfvc->get<fj::ClusterSequence>()->inclusive_jets();
    	revent.FillBranch("jvc", fj::sorted_by_pt(jvc));




#include <typeinfo>

			std::string s = typeid(*p).name();
			std::cout << "[i] add pointer type: " << s << std::endl;

#include "tests.h"
#ifndef __TESTS_HH
#define __TESTS_HH


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

void test_wrapp0()
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

void test_wrapp()
{
    std::vector <fj::PseudoJet> py_hard_event; // signal from pythia
    fj::PseudoJet v(10,0,0,10);
    py_hard_event.push_back(v);

    Wrapper *w = jet_finder(py_hard_event);
    Wrapper &wr = *w;
    wr.list();

    fj::ClusterSequence *cs = wr.get<fj::ClusterSequence>();
    std::vector <fj::PseudoJet> jets = cs->inclusive_jets();
    std::cout << "jet 0 perp = " << jets[0].perp() << std::endl;
}

Wrapper *jet_finder( std::vector<fastjet::PseudoJet> in, 
					double R = 0.4, double etamax = 2, double jetPtmin = 0., 
					fastjet::JetAlgorithm algor = fastjet::genkt_algorithm, double power = -1);


Wrapper *jet_finder( std::vector<fj::PseudoJet> in, 
                    double R /*= 0.4*/, double etamax /*= 2*/, double jetPtmin /*= 0.*/, 
                    fj::JetAlgorithm algor /*= fj::genkt_algorithm */, double power /*= -1*/)
{
    fj::JetDefinition *jet_def  = new fj::JetDefinition(algor, R, power); // this is for signal - anti-kT
    fj::ClusterSequence *cs     = new fj::ClusterSequence(in, *jet_def);

    Wrapper *w = new Wrapper();
    w->add(jet_def);
    w->add(cs);
    return w;
}


#include "fjwrapper.h"

class Wrapp
{
	public:
		Wrapp()
		{
			;
		}

		virtual 		~Wrapp()
		{
			for (unsigned int i = 0; i < fPointers.size(); i++)
			{
				std::cout << "Deleting " << fPointers[i]->get_name() << std::endl;
				delete fPointers[i];
			}
		}

		template <class T>
		unsigned int 	add(T *p)
		{
			unsigned int id = fPointers.size();
			std::string name = std::type_index(typeid(p)).name();
			Container<T> *c = new Container<T>(p, id, name.c_str());
			c->take_ownership();
			fPointers.push_back(c);
			return id;
		}

		template <class T>
		T* get(T **p)
		{
			*p = 0x0;
			for (unsigned int i = 0; i < fPointers.size(); i++)
			{
				Container<T> *c = (Container<T>*)(fPointers[i]);
				if (c == 0x0)
					continue;
				bool has_hash = c->HasHash(*p);
				std::cout << "---> is of the same type?:" << has_hash << std::endl;
				if (has_hash)
				{
					std::cout << i << " c is: " << c << " " << typeid(c).name() << std::endl;
					T *tmp = (T*)c->get();
					if (tmp != 0x0)
					{
						std::cout << "    " << " cast to " << typeid(T).name() << " " << typeid(c->get()).name() << " ok " << std::endl;
					}
					*p = c->get();
					return c->get();
				}
			}
			return 0x0;
		}

		template <class T>
		T* get(T *)
		{
			for (unsigned int i = 0; i < fPointers.size(); i++)
			{
				Container<T> *c = (Container<T>*)(fPointers[i]);
				if (c == 0x0)
					continue;
				T *p = 0;
				bool has_hash = c->HasHash(p);
				std::cout << "---> is of the same type?:" << has_hash << std::endl;
				if (has_hash)
				{
					std::cout << i << " c is: " << c << " " << typeid(c).name() << std::endl;
					T *tmp = (T*)c->get();
					if (tmp != 0x0)
					{
						std::cout << "    " << " cast to " << typeid(T).name() << " " << typeid(c->get()).name() << " ok " << std::endl;
					}
					return c->get();
				}
			}
			return 0x0;
		}

	protected:

		std::vector< VoidType* >		fPointers;

	private:

};

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

#endif