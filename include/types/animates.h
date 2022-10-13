#pragma once

// types/animate.h

#include "types/base.h"

class Barbecue : public Animate
{
public:
	Barbecue(RoomID room);

	bool progress_status(CoreData& core) override;
};

class Computer: public Animate
{
public:
	Computer(RoomID room);

	bool progress_status(CoreData& core) override;
};

class Door: public Animate
{
public:
	Door(RoomID room);

	bool progress_status(CoreData& core) override;
};

class Dragon: public Animate
{
public:
	Dragon(RoomID room);

	bool progress_status(CoreData& core) override;
};

class DragonHead: public Animate
{
public:
	DragonHead(RoomID room);

	bool progress_status(CoreData& core) override;
};

class Gnu: public Animate
{
public:
	Gnu(RoomID room);

	bool progress_status(CoreData& core) override;
};

class GreenCrystal: public Animate
{
public:
	GreenCrystal(RoomID room);

	bool progress_status(CoreData& core) override;
};

class Hatch: public Animate
{
public:
	Hatch(RoomID room);

	bool progress_status(CoreData& core) override;
};

class HellHound: public Animate
{
public:
	HellHound(RoomID room, int strikes_to_kill);

	bool progress_status(CoreData& core) override;
};

class Lava: public Animate
{
public:
	Lava(RoomID room);

	bool progress_status(CoreData& core) override;
};

class Swamp: public Animate
{
public:
	Swamp(RoomID room);

	bool progress_status(CoreData& core) override;
};

class Mist: public Animate
{
public:
	Mist(RoomID room);

	bool progress_status(CoreData& core) override;
};

class Plant: public Animate
{
public:
	Plant(RoomID room, int strikes_to_kill);

	bool progress_status(CoreData& core) override;
};

class RedTroll: public Animate
{
public:
	RedTroll(RoomID room);

	bool progress_status(CoreData& core) override;
};

class Swelling: public Animate
{
public:
	Swelling(RoomID room);

	bool progress_status(CoreData& core) override;
};

class Teleporter: public Animate
{
public:
	Teleporter(RoomID room);

	bool progress_status(CoreData& core) override;
};

class Tree: public Animate
{
public:
	Tree(RoomID room);

	bool progress_status(CoreData& core) override;
};

class Vacuum: public Animate
{
public:
	Vacuum(RoomID room);

	bool progress_status(CoreData& core) override;
};

class Voices: public Animate
{
public:
	Voices(RoomID room);

	bool progress_status(CoreData& core) override;
};