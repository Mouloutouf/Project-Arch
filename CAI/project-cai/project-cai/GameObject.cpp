#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(SpriteRenderer * newSpriteRenderer, float scale)
{
	spriteRenderer = newSpriteRenderer;
	spriteRenderer->SetScale(scale);
}

GameObject::GameObject(SpriteRenderer * newSpriteRenderer, float scale, vector<Behaviour*> attachedBehaviours)
: GameObject::GameObject(newSpriteRenderer, scale)
{
	behaviours = attachedBehaviours;
}

GameObject::~GameObject()
{
	delete spriteRenderer;

	for (Behaviour * behaviour : behaviours)
	{
		delete behaviour;
	}
}

void GameObject::Start()
{
	spriteRenderer->SetPosition(position);

	for (Behaviour * behaviour : behaviours)
	{
		behaviour->Start();
	}
}

void GameObject::Update(float elapsedTime)
{
	spriteRenderer->SetPosition(position);

	for (Behaviour * behaviour : behaviours)
	{
		behaviour->Update(elapsedTime);
	}
}

void GameObject::Render(RenderWindow * window)
{
	spriteRenderer->Render(window);
}
