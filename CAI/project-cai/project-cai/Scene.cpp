#include "Scene.h"

Scene::Scene()
{
}
Scene::Scene(GameWindow* _gameWindow, string _name)
    : gameWindow(_gameWindow), name(_name)
{
}

#pragma region Core Methods
GameObject* Scene::CreateGameObject(string _name, Transform2D _transform, GameObject* _parent, Layer _layer, vector<Tag> _tags)
{
    GameObject newGameObject = GameObject(_transform, _parent, _name, _layer, _tags);
    gameObjects.push_back(newGameObject);

    mainCamera = GetMainCamera(); // I don't like this, should find another solution

    return &gameObjects.back();
}

void Scene::DestroyGameObject(GameObject* _gameObject)
{
    delete _gameObject;
}
#pragma endregion

#pragma region Initialization
void Scene::Init()
{
    currentDisplay = Display(gameWindow->width, gameWindow->height, gameWindow);

    UserInit();

    currentDisplay.Setup(FindAllComponentsOfType<SpriteRenderer>(), mainCamera);
}

inline void Scene::UserInit()
{
    GameObject* cameraObject = CreateGameObject("Main Camera");
    cameraObject->tags.push_back(Tag::Main_Camera);
    /* Add Component should be made into a T template method, to retrieve the Component, after creating it. */
    cameraObject->AddComponent(new Camera(cameraObject, &currentDisplay, currentDisplay.resolution, 1));
    //cameraObject->transform.localPosition = Vector2f(3, 1);

    CreateSpriteObject("Fire Orb", "Assets/Fire Orb.png", 24, Vector2f(-2.5, 0.5));
    CreateSpriteObject("Robot", "Assets/Kastelan Robot.png", 24, Vector2f(3, 1));
    CreateSpriteObject("Dummy", "Assets/Dummy Sized.png", 24, Vector2f(-1.5, -0.5));

    GameObject* blank = CreateGameObject("Yes");
}
#pragma endregion

#pragma region Core Loop
void Scene::Update(float _elapsedTime)
{
    for (auto& go : gameObjects)
        go.Update(_elapsedTime);

    /// DEBUG
    ///
    if (mainCamera != nullptr)
    {
        mainCamera->Input(_elapsedTime, *gameWindow->window);
    }
    ///
}

void Scene::E_Update(Event& _event, float _elapsedTime)
{
    /// DEBUG
    ///
    if (mainCamera != nullptr)
    {
        mainCamera->E_Input(_elapsedTime, _event, *gameWindow->window);
    }
    ///
}

void Scene::Render(RenderWindow* _window)
{
    if (mainCamera == nullptr) return;
    currentDisplay.Render();
}
#pragma endregion

#pragma region Utility Methods
GameObject* Scene::FindGameObjectWithName(string _name)
{
    for (auto& go : gameObjects) {
        if (go.name == _name) {
            return &go;
        }
    } return nullptr;
}

GameObject* Scene::FindGameObjectWithTag(Tag _tag)
{
    for (auto& go : gameObjects) {
        for (int i = 0; i < go.tags.size(); ++i) {
            if (go.tags[i] == _tag)
                return &go;
        }
    } return nullptr;
}
#pragma endregion

#pragma region Shortcut Methods
void Scene::CreateSpriteObject(string _name, string _sprite, int _ppu, Vector2f _position)
{
    GameObject* sp = CreateGameObject(_name);
    sp->AddComponent(new SpriteRenderer(sp, _sprite, _ppu));
    sp->transform.localPosition = _position;
}
#pragma endregion
