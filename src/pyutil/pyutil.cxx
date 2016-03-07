#include "pyutil.h"

#include <Pythia8/Pythia.h>
#include <iostream>

namespace PyUtil
{
	void PrintParticle(const Pythia8::Particle &p)
	{
		std::cout << " | id: "; std::cout.flush();
		std::cout << std::setfill(' ') << std::setw(10) << std::right << std::showpos;
		std::cout << p.id(); std::cout.flush();
		std::cout << " | name: "; std::cout.flush();
		std::cout << std::setfill(' ') << std::setw(10) << std::right << std::noshowpos;
		std::cout << p.name(); std::cout.flush();
		std::cout << " | pT: "; std::cout.flush();
		std::cout << std::setfill(' ') << std::setw(10) << std::right << std::noshowpos;
		std::cout << p.pT(); std::cout.flush();
		std::cout << " | y: "; std::cout.flush();
		std::cout << std::setfill(' ') << std::setw(10) << std::right << std::noshowpos;
		std::cout << p.y(); std::cout.flush();
		std::cout << std::endl;
	}

	void PrintParticle(const Pythia8::Event &event, int idx)
	{
		Pythia8::Particle p = event[idx];

		std::cout << "    p index: "; std::cout.flush();	
		std::cout << std::setfill(' ') << std::setw(7) << std::right << std::noshowpos;
		std::cout << idx; std::cout.flush();
		PrintParticle(event[idx]);
	}

	void PrintParticle(const Pythia8::Pythia &pythia, int idx)
	{
		Pythia8::Event event = pythia.event;
		PrintParticle(event, idx);
	}

	void PrintEventInfo(const Pythia8::Pythia &pythia)
	{
		Pythia8::Event event = pythia.event;
		event.list();
		// Also  junctions.
		//	event.listJunctions();
	}

	std::vector<int> GetDaughters(const Pythia8::Event &event, int idx, int minID, int maxID, bool quiet)
	{
		int pDaughter1 = event[idx].daughter1();
		int pDaughter2 = event[idx].daughter2();
		std::vector<int> retval;
		for (int idxd = pDaughter1; idxd <= pDaughter2; idxd++)
		{
			int id = event[idxd].id(); 
			if (quiet == false)
				PrintParticle(idxd);
			if (abs(id) >= minID && abs(id) <= maxID)
			{
				if (quiet == false)
				{
					std::cout << "    -> selected daughter" << std::endl;
				}
				retval.push_back(idxd);
			}
		}
		return retval;
	}

	std::vector<int> FollowDaughters(const Pythia8::Event &event, int idx, int minID, int maxID, bool quiet)
	{
		std::vector<int> retval;
		std::vector<int> daughters  = GetDaughters(event, idx, minID, maxID, quiet);
		for (unsigned int i = 0; i < daughters.size(); i++)
		{
			if (quiet == false) 
				PrintParticle(event, daughters[i]);
			retval.push_back(daughters[i]);
			std::vector<int> subds = FollowDaughters(event, daughters[i], minID, maxID, quiet);
			for (unsigned int id = 0; id < subds.size(); id++)
			{
				retval.push_back(subds[id]);
			}
		}
		return retval;
	}

};