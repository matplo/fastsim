#include <TObject.h>

namespace Pythia8
{
	class Pythia;
}
class TH1;

class PGun : public TObject
{
public:
	PGun();
	virtual ~PGun();

	void SetSpectrum(TH1 *h, int id = -1);
	void SetPartonID(int id)
	{
		fPartonID = id;
	}
	int Generate(int nEvent);

private:

	void FillPartons(double ee); // ee is energy

	Pythia8::Pythia *fPythia; //!
	TH1             *fSpectrum; //!
	int              fPartonID;

	ClassDef(PGun, 0)
};