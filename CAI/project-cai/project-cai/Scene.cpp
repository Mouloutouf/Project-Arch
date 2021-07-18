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
}

GameObject* Scene::CreateGameObject(string _name, Transform2D _transform, GameObject* _parent, int _layer, int _tags[])
{
    GameObject newGameObject = GameObject(_transform, _parent, _name, _layer, _tags);
    gameObjects.push_back(newGameObject);

    return &newGameObject;
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
    GameObject* basicSprite = CreateGameObject("Basic Sprite");

    basicSprite->AddComponent(SpriteRenderer(basicSprite, "D:\Documents\__PROG\_C++\Project-Arch\CAI\project-cai\project-cai\Assets\1m66 gros pec.jpg"));

    basicSprite->transform.localPosition = Vector2f(184, 257);
}

void Scene::Update(float _elapsedTime)
{
    for (auto& go : gameObjects)
    {
        go.Update(_elapsedTime);

        go.Draw(gameWindow->window);
    }
}