#include "bucketheadzombie.h"

BucketheadZombie::BucketheadZombie(QObject *parent) :
	Zombie(parent)
{
	mHealthPoint = 1370;
	mMoveSpeed = 1. / 5000.;
}

QString BucketheadZombie::imgSrc() const
{
	if(property("state").toString() == "bombed")
		return QStringLiteral(":/zombies/images/Zombies/Zombie/BoomDie.gif");
	else if (mHealthPoint <= 70)
		return QStringLiteral(":/zombies/images/Zombies/Zombie/ZombieLostHead.gif");
	else if (mHealthPoint > 270)
	{
		if (property("state").toString() == "attacking")
			return QStringLiteral(":/zombies/images/Zombies/BucketheadZombie/BucketheadZombieAttack.gif");
		else
			return QStringLiteral(":/zombies/images/Zombies/BucketheadZombie/BucketheadZombie.gif");
	}
	else
	{
		if (property("state").toString() == "attacking")
			return QStringLiteral(":/zombies/images/Zombies/Zombie/ZombieAttack.gif");
		else
			return QStringLiteral(":/zombies/images/Zombies/Zombie/Zombie.gif");
	}
}
