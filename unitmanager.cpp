#include "unitmanager.h"

UnitManager::UnitManager(QObject *parent) : QObject(parent)
{
    QVector<Unit> length_units;
    Unit len_base = Unit(tr("meter"), tr("m"));
    length_units << len_base << Unit(tr("decimetre"), tr("dm"), 10)
                 << Unit(tr("centimeter"), tr("cm"), 100) << Unit(tr("kilometer"), tr("km"), 1e-3)
                 << Unit(tr("minimeter"), tr("mm"), 1e3) << Unit(tr("micrometer"), tr("μm"), 1e6)
                 << Unit(tr("nanometer"), tr("nm"), 1e9) << Unit(tr("inch"), tr("in"), 39.3700787)
                 << Unit(tr("yard"), tr("yd"), 1.0936133) << Unit(tr("foot"), tr("ft"), 3.2808399)
                 << Unit(tr("Chi"), tr("尺"), 3) << Unit(tr("Cun"), tr("寸"), 30)
                 << Unit(tr("Zhang"), tr("丈"), 0.3) << Unit(tr("Li"), tr("里"), 1 / 500)
                 << Unit(tr("mile"), tr("mi"), 0.00062137)
                 << Unit(tr("nautical mile"), tr("n mile"), 0.00053996);
    UnitCategory *len_cat = new UnitCategory(tr("length"), len_base, length_units, this);
    cm[tr("length")] = len_cat;

    QVector<Unit> mass_units;
    Unit mass_base = Unit(tr("kilogram"), tr("kg"));
    mass_units << mass_base << Unit(tr("gram"), tr("g"), 1e3) << Unit(tr("minigram"), tr("mg"), 1e6)
               << Unit(tr("microgram"), tr("μg"), 1e9) << Unit(tr("tonne"), tr("t"), 1e-3);
    UnitCategory *mass_cat = new UnitCategory(tr("mass"), mass_base, mass_units, this);
    cm[tr("mass")] = mass_cat;

    QVector<Unit> temp_units;
    Unit temp_base = Unit(tr("degree celsius"), tr("℃"));
    temp_units << temp_base << Unit(tr("degree fahrenheit"), tr("℉"), 1.8, 32)
               << Unit(tr("kelvin"), tr("K"), 1, -273.15);
    UnitCategory *temp_cat = new UnitCategory(tr("temperature"), temp_base, temp_units, this);
    cm[tr("temperature")] = temp_cat;
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
