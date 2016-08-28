#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "plant.h"

class SunFlower : public Plant
{
	Q_OBJECT
	Q_CLASSINFO("staticImageSource", ":/plants/images/Plants/SunFlower/0.gif")

public:
	Q_INVOKABLE SunFlower(QObject *parent = 0);
	virtual QString imgSrc() const;
};

#endif // SUNFLOWER