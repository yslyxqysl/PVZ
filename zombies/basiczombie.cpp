#include "basiczombie.h"

BasicZombie::BasicZombie(QObject *parent) :
	Zombie(parent)
{
	mMoveSpeed = 1. / 4700.;
}

QString BasicZombie::imgSrc() const
{
	if (mHealthPoint <= 70)
		return QStringLiteral(":/zombies/images/Zombies/Zombie/ZombieLostHead.gif");
	else if (property("state").toString() == "attacking")
		return QStringLiteral(":/zombies/images/Zombies/Zombie/ZombieAttack.gif");
	else
		return QStringLiteral(":/zombies/images/Zombies/Zombie/Zombie.gif");
}
