#include "Scene.h"

Scene::Scene()
{
}
Scene::Scene(GameWindow* _gameWindow, string _name)
    : gameWindow(_gameWindow), name(_name)
{
}

GameObject* Scene::FindGameObjectWithName(string _name)
{
    for (auto& go : gameObjects)
    {
        if (go.name == _name)
        {
            return &go;
        }
    }
    return nullptr;
}

GameObject* Scene::FindGameObjectWithTag(Tag _tag)
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

    currentDisplay = Display(1920, 1080, gameWindow);

    UserInit();

    currentDisplay.Setup(FindAllComponentsOfType<SpriteRenderer>(), GetMainCamera());
}

inline void Scene::UserInit()
{
    GameObject* cameraObject = CreateGameObject("Main Camera");
    cameraObject->tags.push_back(Tag::Main_Camera);
    /* Add Component should be made into a T template method, to retrieve the Component, after creating it. */
    cameraObject->AddComponent(new Camera(cameraObject, &currentDisplay, currentDisplay.resolution, 3));

    GameObject* basicSpriteObject = CreateGameObject("Basic Sprite");

    basicSpriteObject->AddComponent(new SpriteRenderer(basicSpriteObject, "Assets/1m66 gros pec.jpg", 300));
    basicSpriteObject->transform.localPosition = Vector2f(2, 1);

    GameObject* blank = CreateGameObject("Yes");
}

void Scene::Update(float _elapsedTime)
{
    for (auto& go : gameObjects)
    {
        go.Update(_elapsedTime);
    }

    /// DEBUG

    /*GameObject* so = FindGameObjectWithName("Basic Sprite");
    so->transform.localScale += Vector2f(_elapsedTime, _elapsedTime) * .5f;*/

    Camera* cam = GetMainCamera();
    if (cam != nullptr)
    {
        cam->size += _elapsedTime;
    }
}

void Scene::Render(RenderWindow* _window)
{
    Camera* cam = GetMainCamera();
    if (cam == nullptr) return;

    currentDisplay.Render();
}

void Scene::DrawGrid()
{
}
