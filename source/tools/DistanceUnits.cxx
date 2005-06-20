#include "DistanceUnits.h"
#include <string.h>

typedef struct
{
	enum DistanceUnits::eDistanceUnits unit;
	char *name;
	double multipleOfCm;
} distanceUnits;

static const distanceUnits g_distanceUnits[] =
{
	{DistanceUnits::eDistanceUnitCm, "cm", 1.0},
	{DistanceUnits::eDistanceUnitMm, "mm", 0.1},
	{DistanceUnits::eDistanceUnitInch, "inch", 2.54}
};

static const g_distanceUnitsCount = sizeof(g_distanceUnits)/sizeof(g_distanceUnits[0]);

int DistanceUnits::GetDistanceUnitsCount(void)
{
	return g_distanceUnitsCount;
}

int DistanceUnits::GetDistanceUnitIndex(enum eDistanceUnits unit)
{
	int index = 0;

	for (int i = 0; i < g_distanceUnitsCount; i++)
	{
		if (unit == g_distanceUnits[i].unit)
		{
			index = i;
			break;
		}
	}

	return index;
}

const char* DistanceUnits::GetDistanceUnitName(enum eDistanceUnits unit)
{
	int distanceUnitIndex = GetDistanceUnitIndex(unit);

	return g_distanceUnits[distanceUnitIndex].name;
}

enum DistanceUnits::eDistanceUnits DistanceUnits::GetDistanceUnitForName(const char* name)
{
	enum eDistanceUnits distanceUnit = eDistanceUnitCm;

	for (int i = 0; i < g_distanceUnitsCount; i++)
	{
		if (0 == strcmp(name, g_distanceUnits[i].name))
		{
			distanceUnit = g_distanceUnits[i].unit;
			break;
		}
	}

	return distanceUnit;
}

double CmToDistanceUnit(double cm, enum DistanceUnits::eDistanceUnits unit)
{
	if (unit == DistanceUnits::eDistanceUnitInch)
		cm /= 2.54;
	return cm;
}

double DistanceUnitToCm(double distance, enum DistanceUnits::eDistanceUnits unit)
{
	if (unit == DistanceUnits::eDistanceUnitInch)
		distance *= 2.54;
	return distance;
}

double DistanceUnits::ConvertBetweenDistancUnits(double distance, enum eDistanceUnits sourceUnit, enum eDistanceUnits targetUnit)
{
	double convertedDistance = distance;

	if (sourceUnit != targetUnit)
	{
		if (sourceUnit != eDistanceUnitCm)
			convertedDistance = DistanceUnitToCm(convertedDistance, sourceUnit);

		if (targetUnit != eDistanceUnitCm)
			convertedDistance = CmToDistanceUnit(convertedDistance, targetUnit);
	}

	return convertedDistance;
}
