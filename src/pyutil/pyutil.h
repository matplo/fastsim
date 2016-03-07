#ifndef __PYUTIL__HH
#define __PYUTIL__HH

#include <Pythia8/Pythia.h>
#include <vector>

namespace PyUtil
{
	void PrintParticle(const Pythia8::Particle &p);
	void PrintParticle(const Pythia8::Event  &event, 	int idx);
	void PrintParticle(const Pythia8::Pythia &pythia, 	int idx);

	void PrintEventInfo(const Pythia8::Pythia &pythia);

	std::vector<int> GetDaughters	(const Pythia8::Event &event, int idx, int minID = 0, int maxID = 10000, bool quiet = true);
	std::vector<int> FollowDaughters(const Pythia8::Event &event, int idx, int minID = 0, int maxID = 10000, bool quiet = true);
};

#endif // __PYUTIL__HH