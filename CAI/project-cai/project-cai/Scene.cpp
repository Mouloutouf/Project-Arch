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

GameObject* Scene::FindWithTag(Tag _tag)
{
    for (auto& go : gameObjects)
    {
        for (int i = 0; i < go.tags.size(); i++)
        {
            if (go.tags[i] == _tag)
            {
                return &go;
            }
        }
    }
}

void Scene::Init()
{
    // Base Initialization

    currentDisplay = Display(1920, 1080);

    GameObject* cameraObject = CreateGameObject("Main Camera");
    cameraObject->tags.push_back(Tag::Main_Camera);
    /* Add Component should be made into a T template method, to retrieve the Component, after creating it. */
    cameraObject->AddComponent(new Camera(&currentDisplay, currentDisplay.resolution));

    UserInit();

    //GameObject* cameraObject = FindWithTag(Tag::Main_Camera);
    mainCamera = cameraObject->GetComponent<Camera>();

    currentDisplay.Setup(FindAllComponentsOfType<SpriteRenderer>(), mainCamera);
}

void Scene::UserInit()
{
    GameObject* basicSpriteObject = CreateGameObject("Basic Sprite");

    basicSpriteObject->AddComponent(new SpriteRenderer(basicSpriteObject, "Assets/1m66 gros pec.jpg"));
    basicSpriteObject->transform.localPosition = Vector2f(2, 1);
}

void Scene::Update(float _elapsedTime)
{
    for (auto& go : gameObjects)
    {
        go.Update(_elapsedTime);
    }
}

void Scene::Render(RenderWindow* _window)
{
    if (mainCamera == nullptr) return;

    currentDisplay.Render();
}
