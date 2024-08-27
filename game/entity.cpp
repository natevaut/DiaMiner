// COMP710 GP Framework 2022
// Local includes:
#include "entity.h"
Entity::Entity(): m_bAlive(true) {}
Entity::~Entity() {}
	//bool Entity::Initialise(Renderer& renderer) {}
	void Entity::Process(float deltaTime) {}
	void Entity::Draw(Renderer& renderer) {}
	void Entity::Rotate(float direction) {}
	bool Entity::IsAlive() const {
		return m_bAlive;
	}
	void Entity::SetDead() {
		m_bAlive = false;
	}
	float Entity::GetRadius() {
		return 0.0f;
	}
	/*
	Vector2 Entity::GetFacingDirection() {}
	Vector2& Entity::GetPosition() {}
	Vector2& Entity::GetVelocity() {}
	bool Entity::IsCollidingWith(Entity& toCheck) {}
	*/

	/*Member data :
	Sprite* m_pSprite;
	Vector2 m_position;
	Vector2 m_velocity;
	bool m_bAlive;*/
