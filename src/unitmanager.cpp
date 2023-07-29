#include "unitmanager.h"
#include <cmath>

UnitManager::UnitManager(QObject *parent) : QObject(parent)
{
    QVector<Unit> length_units;
    Unit len_base = Unit(tr("meter"), tr("m"));
    length_units << len_base << Unit(tr("decimeter"), tr("dm"), 10)
                 << Unit(tr("centimeter"), tr("cm"), 100) << Unit(tr("kilometer"), tr("km"), 1e-3)
                 << Unit(tr("minimeter"), tr("mm"), 1e3) << Unit(tr("micrometer"), tr("μm"), 1e6)
                 << Unit(tr("nanometer"), tr("nm"), 1e9) << Unit(tr("inch"), tr("in"), 39.3700787)
                 << Unit(tr("yard"), tr("yd"), 1.0936133) << Unit(tr("foot"), tr("ft"), 3.2808399)
                 << Unit(tr("Chi"), tr("尺"), 3) << Unit(tr("Cun"), tr("寸"), 30)
                 << Unit(tr("Zhang"), tr("丈"), 0.3) << Unit(tr("Li"), tr("里"), 1 / 500)
                 << Unit(tr("mile"), tr("mi"), 0.00062137)
                 << Unit(tr("nautical mile"), tr("nmi"), 0.00053996)
                 << Unit(tr("angstrom"), tr("A"), 1e10) << Unit(tr("femtometer"), tr("fm"), 1e15)
                 << Unit(tr("picometer"), tr("pm"), 1e-12);
    UnitCategory *len_cat = new UnitCategory(tr("length"), len_base, length_units, this);
    cm[tr("length")] = len_cat;

    QVector<Unit> mass_units;
    Unit mass_base = Unit(tr("kilogram"), tr("kg"));
    mass_units << mass_base << Unit(tr("gram"), tr("g"), 1e3) << Unit(tr("minigram"), tr("mg"), 1e6)
               << Unit(tr("microgram"), tr("μg"), 1e9) << Unit(tr("tonne"), tr("t"), 1e-3)
               << Unit(tr("ounce"), tr("oz"), 35.2739619)
               << Unit(tr("pound"), tr("pd"), 2.20462262);
    UnitCategory *mass_cat = new UnitCategory(tr("mass"), mass_base, mass_units, this);
    cm[tr("mass")] = mass_cat;

    QVector<Unit> temp_units;
    Unit temp_base = Unit(tr("degree celsius"), tr("℃"));
    temp_units << temp_base << Unit(tr("degree fahrenheit"), tr("℉"), 1.8, 32)
               << Unit(tr("kelvin"), tr("K"), 1, -273.15);
    UnitCategory *temp_cat = new UnitCategory(tr("temperature"), temp_base, temp_units, this);
    cm[tr("temperature")] = temp_cat;

    QVector<Unit> area_units;
    Unit area_base = Unit(tr("square meter"), tr("m²"));
    area_units << area_base << Unit(tr("square centimeter"), tr("cm²"), 1e4)
               << Unit(tr("square decimeter"), tr("dm²"), 1e2)
               << Unit(tr("square minimeter"), tr("mm²"), 1e6)
               << Unit(tr("square micrometer"), tr("μm²"), 1e12)
               << Unit(tr("square nanometer"), tr("nm²"), 1e18)
               << Unit(tr("square kilometer"), tr("km²"), 1e-6)
               << Unit(tr("hectare"), tr("hm²"), 1e-4)
               << Unit(tr("square inch"), tr("in²"), 1550.0031)
               << Unit(tr("square foot"), tr("ft²"), 10.7639104)
               << Unit(tr("square yard"), tr("yd²"), 1.19599005) << Unit(tr("Mu"), tr("亩"), 0.0015)
               << Unit(tr("acre"), tr("acre"), 0.00024711)
               << Unit(tr("square mile"), tr("mi²"), 3.861e-07)
               << Unit(tr("square Chi"), tr("尺²"), 9) << Unit(tr("square Cun"), tr("寸²"), 900)
               << Unit(tr("square Zhang"), tr("丈²"), 0.09)
               << Unit(tr("square nautical mile"), tr("nmi²"), 2.915533496e-7);
    UnitCategory *area_cat = new UnitCategory(tr("area"), area_base, area_units, this);
    cm[tr("area")] = area_cat;

    QVector<Unit> volume_units;
    Unit volume_base = Unit(tr("cubic meter"), tr("m³"));
    volume_units << volume_base << Unit(tr("cubic centimeter/minilitre"), tr("cm³|cc|mL"), 1e6)
                 << Unit(tr("cubic decimeter/litre"), tr("dm³|L"), 1e3)
                 << Unit(tr("cubic minimeter"), tr("mm³"), 1e9)
                 << Unit(tr("cubic micrometer"), tr("μm³"), 1e18)
                 << Unit(tr("cubic nanometer"), tr("nm³"), 1e27)
                 << Unit(tr("cubic kilometer"), tr("km³"), 1e-9)
                 << Unit(tr("US. gallon"), tr("gal"), 264.172052)
                 << Unit(tr("US. pint"), tr("pt"), 2113.37642);
    UnitCategory *volume_cat = new UnitCategory(tr("area"), volume_base, volume_units, this);
    cm[tr("volume")] = volume_cat;

    QVector<Unit> duration_units;
    Unit dura_base = Unit(tr("second"), tr("s"));
    duration_units << dura_base << Unit(tr("minisecond"), tr("ms"), 1e3)
                   << Unit(tr("microsecond"), tr("μs"), 1e6)
                   << Unit(tr("minute"), tr("min"), 1 / 60)
                   << Unit(tr("hour"), tr("h"), 1 / 60 / 60)
                   << Unit(tr("nanosecond"), tr("ns"), 1e9)
                   << Unit(tr("day"), tr("d"), 1 / 60 / 60 / 24)
                   << Unit(tr("week"), tr("week"), 1 / 60 / 60 / 24 / 7);
    UnitCategory *dura_cat = new UnitCategory(tr("duration"), dura_base, duration_units, this);
    cm[tr("duration")] = dura_cat;

    QVector<Unit> speed_units;
    Unit speed_base = Unit(tr("meters per second"), tr("m/s"));
    speed_units << speed_base << Unit(tr("kilometers per hour"), tr("km/h"), 3.6)
                << Unit(tr("miles per hour"), tr("mph"), 2.23693629)
                << Unit(tr("yards per miniut"), tr("yd/min"), 65.6167979)
                << Unit(tr("knot"), tr("knot"), 1.94384449);
    UnitCategory *speed_cat = new UnitCategory(tr("speed"), speed_base, speed_units, this);
    cm[tr("speed")] = speed_cat;

    QVector<Unit> energy_units;
    Unit energy_base = Unit(tr("joule"), tr("J"));
    energy_units << energy_base << Unit(tr("kilojoule"), tr("kJ"), 1e-3)
                 << Unit(tr("electron volt"), tr("eV"), 6.2415E+18)
                 << Unit(tr("kilowatt hour"), tr("kWh"), 2.7777777777778E-7)
                 << Unit(tr("calorie"), tr("cal"), 0.23900574);
    UnitCategory *energy_cat = new UnitCategory(tr("energy"), energy_base, energy_units, this);
    cm[tr("energy")] = energy_cat;

    QVector<Unit> angle_units;
    Unit angle_base = Unit(tr("radian"), tr("rad"));
    angle_units << angle_base << Unit(tr("degree"), tr("deg"), 180 / (M_PI));
    UnitCategory *angle_cat = new UnitCategory(tr("angle"), angle_base, angle_units, this);
    cm[tr("angle")] = angle_cat;
}

const UnitCategory *UnitManager::getCategory(const QString &name)
{
    if (cm.find(name) == cm.end()) {
        return nullptr;
    }
    return cm[name];
}

QList<QString> UnitManager::getCategoryList() const
{
    return cm.keys();
}
