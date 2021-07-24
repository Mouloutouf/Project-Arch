#include "Scene.h"

Scene::Scene()
{
}
Scene::Scene(GameWindow* _gameWindow, string _name)
: gameWindow(_gameWindow), name(_name)
{
}

GameObject* Scene::FindGameObject(string _name)
{
    for (auto &go : gameObjects)
    {
        if (go.name == _name)
        {
            return &go;
        }
    }
    return nullptr;
}

GameObject* Scene::CreateGameObject(string _name, Transform2D _transform, GameObject* _parent, Layer _layer, vector<Tag> _tags)
{
    GameObject newGameObject = GameObject(_transform, _parent, _name, _layer, _tags);
    gameObjects.push_back(newGameObject);

    return &gameObjects.back();
}

void Scene::DestroyGameObject(GameObject* _gameObject)
{
    delete _gameObject;
}

void Scene::Init()
{
    // Base Initialization

    UserInit();
}

void Scene::UserInit()
{
    GameObject* basicSpriteObject = CreateGameObject("Basic Sprite");

    basicSpriteObject->AddComponent(new SpriteRenderer(basicSpriteObject, "Assets/1m66 gros pec.jpg"));

    basicSpriteObject->transform.localPosition = Vector2f(184, 257);
}

void Scene::Update(float _elapsedTime)
{
    for (auto& go : gameObjects)
    {
        go.Update(_elapsedTime);

        go.Draw(gameWindow->window);
    }
}