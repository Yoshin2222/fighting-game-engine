#include "actions.hpp"

//SET METER: Set a character's meter to a value
Act_setMeter::Act_setMeter()
{
	ASSERT(false);
}

Act_setMeter::Act_setMeter( Character* target, Meter meter, int value)
: m_meter(meter), m_value(value)
{
	Action::m_target = target;
}

void Act_setMeter::perform()
{
	((Character*)m_target)->setMeter(m_meter, m_value);
}

Act_setMeter* Act_setMeter::clone()
{
	return new Act_setMeter(*this);
}

//MOD METER: Modify a character's meter by a value
Act_modMeter::Act_modMeter()
{
	ASSERT(false);
}

Act_modMeter::Act_modMeter( Character* target, Meter meter, int change)
: m_meter(meter), m_change(change)
{
	Action::m_target = target;
}

void Act_modMeter::perform()
{
	//meter = current meter + change
	((Character*)m_target)->setMeter(m_meter, 
		( ((Character*)m_target)->getMeter(m_meter) + m_change) );
}

Act_modMeter* Act_modMeter::clone()
{
	return new Act_modMeter(*this);
}

//SET MOVE: Modify a character's current move
Act_setMove::Act_setMove()
{
	ASSERT(false);
}
Act_setMove::Act_setMove( GameObject* target, Move* newMove )
: m_newMove(newMove)
{
	Action::m_target = target;
}

void Act_setMove::perform()
{
	m_target->setMove(m_newMove);
}

Act_setMove* Act_setMove::clone()
{
	return new Act_setMove(*this);
}

//ADD CHILD: Creates a child object and adds it to the
//target's children. This is for use with projectiles,
//or other things like that.
Act_addChild::Act_addChild()
{
	ASSERT(false);
}

Act_addChild::Act_addChild(Character* target, Projectile* baseObj)
: m_baseObj(baseObj)
{
	Action::m_target = target;
}

void Act_addChild::perform()
{
//	GameObject* newChild = m_baseObj->clone();
//	((Projectile*)newChild)->setParent( ((Character*)m_target) );	//set the parent of newChild to m_target
//																	//cast is ok, since baseObj must be a Projectile* anyways; likewise with m_target
	((Character*)m_target)->addChild( (Projectile*)m_baseObj->clone() );	//addChild automatically sets parent
																			//cast is ok because m_baseObj must be a Projectile* anyways
}

Act_addChild* Act_addChild::clone()
{
	return new Act_addChild(*this);
}

//REMOVE CHILD: Removes a child. Uses string or Object*.
Act_removeChild::Act_removeChild()
{
	ASSERT(false);
}

Act_removeChild::Act_removeChild(Character* target, Projectile* obj)
: m_obj(obj), m_name("")
{
	ASSERT(false);
	Action::m_target = target;
}

void Act_removeChild::perform()
{
	ASSERT(false);
}

Act_removeChild* Act_removeChild::clone()
{
	ASSERT(false);
	return new Act_removeChild(*this);
}

//REMOVE SELF: A child removes it self. Suicide or something.
Act_removeSelf::Act_removeSelf()
{
	ASSERT(false);
}

Act_removeSelf::Act_removeSelf(Projectile* target)
{
	Action::m_target = target;
}

void Act_removeSelf::perform()
{
	((Projectile*)Action::m_target)->getParent()->removeChild( (Projectile*)Action::m_target );
}

Act_removeSelf* Act_removeSelf::clone()
{
	return new Act_removeSelf(*this);
}