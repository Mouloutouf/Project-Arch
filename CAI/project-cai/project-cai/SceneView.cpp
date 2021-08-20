#include "SceneView.h"

namespace alpha
{
    namespace core
    {
        SceneView::SceneView()
        {
        }
        SceneView::SceneView(GameWindow* _gameWindow, string _name)
            : gameWindow(_gameWindow), name(_name)
        {
        }

        SceneView::~SceneView()
        {
            for (auto& g : gameObjects)
                delete g;
        }

#pragma region Core Methods
        GameObject* SceneView::CreateGameObject(string _name, Transform2D _transform, GameObject* _parent, Layer _layer, vector<Tag> _tags)
        {
            gameObjects.push_back(new GameObject(_name, _transform, _parent, _layer, _tags));
            gameObjects.back()->index = gameObjects.size() - 1;

            return gameObjects.back();
        }

        GameObject* SceneView::InstantiateGameObject(GameObject* _gameObject)
        {
            gameObjects.push_back(new GameObject(*_gameObject));
            gameObjects.back()->index = gameObjects.size() - 1;

            return gameObjects.back();
        }

        void SceneView::DestroyGameObject(GameObject* _gameObject)
        {
            for (int i = 0; i < _gameObject->children.size(); i++) {
                delete _gameObject->children[i];
            }
            delete _gameObject;
        }
#pragma endregion

#pragma region Initialization
        void SceneView::Init()
        {
            currentDisplay = Display(gameWindow->width, gameWindow->height, gameWindow);

            UserInit();

            mainCamera = GetMainCamera();
            currentDisplay.Setup(FindAllComponentsOfType<SpriteRenderer>(), mainCamera);

            for (auto& g : gameObjects) {
                g->Init();
            }

            Start();
        }

        void SceneView::UserInit()
        {
            GameObject* cameraObject = CreateGameObject("Main Camera");
            cameraObject->tags.push_back(Tag::Main_Camera);
            cameraObject->AddComponent(new Camera(cameraObject, &currentDisplay, currentDisplay.resolution, 1));

            CreateSpriteObject("Dummy", ASSETS_FOLDER + "Dummy.png", 24, Vector2f(0, 0));

            GameObject* gridObject = CreateGameObject("Grid");
            gridObject->AddComponent(new Grid(gridObject, 20, 20));
        }

        void SceneView::Start()
        {
            for (auto& go : gameObjects)
                go->Start();
        }
#pragma endregion

#pragma region Core Loop
        void SceneView::Update(float _elapsedTime)
        {
            for (auto& go : gameObjects)
                go->Update(_elapsedTime);

            /// DEBUG
            ///
            if (mainCamera != nullptr)
            {
                mainCamera->Input(_elapsedTime, *gameWindow->window);
            }
            ///
        }

        void SceneView::EventUpdate(Event& _event, float _elapsedTime)
        {
            /// DEBUG
            ///
            if (mainCamera != nullptr)
            {
                mainCamera->EventInput(_elapsedTime, _event, *gameWindow->window);
            }
            ///
        }

        void SceneView::Render(RenderWindow* _window)
        {
            if (mainCamera == nullptr) return;
            currentDisplay.Render();
        }
#pragma endregion

#pragma region Utility Methods
        GameObject* SceneView::FindGameObjectWithName(string _name)
        {
            for (auto& go : gameObjects) {
                if (go->name == _name) {
                    return go;
                }
            } return nullptr;
        }

        GameObject* SceneView::FindGameObjectWithTag(Tag _tag)
        {
            for (auto& go : gameObjects) {
                for (int i = 0; i < go->tags.size(); ++i) {
                    if (go->tags[i] == _tag)
                        return go;
                }
            } return nullptr;
        }
#pragma endregion

#pragma region Shortcut Methods
        void SceneView::CreateSpriteObject(string _name, string _sprite, int _ppu, Vector2f _position)
        {
            GameObject* sp = CreateGameObject(_name);
            sp->AddComponent(new SpriteRenderer(sp, _sprite, _ppu));
            sp->transform.localPosition = _position;
        }
#pragma endregion
    }
}
