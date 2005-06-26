#include "DistanceUnits.h"
#include <string.h>

typedef struct
{
	enum DistanceUnits::eDistanceUnits unit;
	char *name;
	double multipleOfCentimeter;
} distanceUnits;

static const distanceUnits g_distanceUnits[] =
{
	{DistanceUnits::eDistanceUnitMeter, "m", 100},
	{DistanceUnits::eDistanceUnitMillimeter, "mm", 0.1},
	{DistanceUnits::eDistanceUnitCentimeter, "cm", 1.0},
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
	enum eDistanceUnits distanceUnit = eDistanceUnitCentimeter;

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

double CentimeterToDistanceUnit(double cm, enum DistanceUnits::eDistanceUnits unit)
{
	cm /= g_distanceUnits[DistanceUnits::GetDistanceUnitIndex(unit)].multipleOfCentimeter;
	return cm;
}

double DistanceUnitToCentimeter(double distance, enum DistanceUnits::eDistanceUnits unit)
{
	distance *= g_distanceUnits[DistanceUnits::GetDistanceUnitIndex(unit)].multipleOfCentimeter;
	return distance;
}

double DistanceUnits::ConvertBetweenDistanceUnits(double distance, enum eDistanceUnits sourceUnit, enum eDistanceUnits targetUnit)
{
	double convertedDistance = distance;

	if (sourceUnit != targetUnit)
	{
		if (sourceUnit != eDistanceUnitCentimeter)
			convertedDistance = DistanceUnitToCentimeter(convertedDistance, sourceUnit);

		if (targetUnit != eDistanceUnitCentimeter)
			convertedDistance = CentimeterToDistanceUnit(convertedDistance, targetUnit);
	}

	return convertedDistance;
}
