#ifndef DElightManagerF_hh_INCLUDED
#define DElightManagerF_hh_INCLUDED

// ObjexxFCL Headers
#include <ObjexxFCL/Fstring.hh>

// EnergyPlus Headers
#include <EnergyPlus.hh>

namespace EnergyPlus {

namespace DElightManagerF {

	// Functions

	void
	GenerateDElightDaylightCoefficients(
		Real64 & dBldgLat,
		int & iErrorFlag
	);

	void
	DElightDaylightCoefficients(
		Real64 & dBldgLat,
		int & iErrorFlag
	);

	void
	DElightElecLtgCtrl(
		int const iNameLength,
		Fstring const & cZoneName,
		Real64 const dBldgLat,
		Real64 const dHISKF,
		Real64 const dHISUNF,
		Real64 const dCloudFraction,
		Real64 const dSOLCOSX,
		Real64 const dSOLCOSY,
		Real64 const dSOLCOSZ,
		Real64 const pdPowerReducFac,
		int const iErrorFlag
	);

	void
	DElightFreeMemory();

	void
	DElightOutputGenerator( int & iOutputFlag );

	void
	DElightInputGenerator();

	void
	SetupDElightOutput4EPlus();

	Fstring
	ReplaceBlanksWithUnderscores( Fstring const & InputString ); // Input String

	//     NOTICE

	//     Copyright � 1996-2014 The Board of Trustees of the University of Illinois
	//     and The Regents of the University of California through Ernest Orlando Lawrence
	//     Berkeley National Laboratory.  All rights reserved.

	//     Portions of the EnergyPlus software package have been developed and copyrighted
	//     by other individuals, companies and institutions.  These portions have been
	//     incorporated into the EnergyPlus software package under license.   For a complete
	//     list of contributors, see "Notice" located in EnergyPlus.f90.

	//     NOTICE: The U.S. Government is granted for itself and others acting on its
	//     behalf a paid-up, nonexclusive, irrevocable, worldwide license in this data to
	//     reproduce, prepare derivative works, and perform publicly and display publicly.
	//     Beginning five (5) years after permission to assert copyright is granted,
	//     subject to two possible five year renewals, the U.S. Government is granted for
	//     itself and others acting on its behalf a paid-up, non-exclusive, irrevocable
	//     worldwide license in this data to reproduce, prepare derivative works,
	//     distribute copies to the public, perform publicly and display publicly, and to
	//     permit others to do so.

	//     TRADEMARKS: EnergyPlus is a trademark of the US Department of Energy.

} // DElightManagerF

} // EnergyPlus

#endif