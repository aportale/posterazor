#ifndef DistanceUnits_h
#define DistanceUnits_h

class DistanceUnits
{
public:
	typedef enum eDistanceUnits
	{
		eDistanceUnitCm,
		eDistanceUnitMm,
		eDistanceUnitInch
	};

	static const int buibui = 5;

	static int GetDistanceUnitsCount(void);

	static double ConvertBetweenDistancUnits(double distance, enum eDistanceUnits sourceUnit, enum eDistanceUnits targetUnit);
	static int GetDistanceUnitIndex(enum eDistanceUnits unit);
	static const char* GetDistanceUnitName(enum eDistanceUnits unit);
	static enum eDistanceUnits GetDistanceUnitForName(const char* name);
};

#endif