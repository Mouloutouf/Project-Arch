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
            for (auto& go : gameObjects)
                if (go != nullptr) delete go;
        }

#pragma region Core Methods
        GameObject* SceneView::CreateGameObject(string _name, GameObject* _parent, Transform2D _transform, Layer _layer, vector<Tag> _tags)
        {
            gameObjects.push_back(new GameObject(_name, _parent, _transform, _layer, _tags));
            auto go = gameObjects.back();
            go->index = (int)gameObjects.size() - 1;

            if (inPlay) {
                go->Init();
                go->Start();
            }

            return go;
        }

        GameObject* SceneView::InstantiateGameObject(GameObject* _gameObject)
        {
            gameObjects.push_back(new GameObject(*_gameObject));
            auto go = gameObjects.back();
            go->index = (int)gameObjects.size() - 1;

            for (auto& ch : *go->GetChildren()) {
                gameObjects.push_back(ch);
                ch->index = (int)gameObjects.size() - 1;

                if (inPlay) {
                    ch->Init();
                    ch->Start();
                }
            }

            if (inPlay) {
                go->Init();
                go->Start();
            }

            return go;
        }

        void SceneView::DestroyGameObject(GameObject* _gameObject)
        {
            auto& children = *_gameObject->GetChildren();
            for (int i = 0; i < children.size(); i++) {
                gameObjects.erase(gameObjects.begin() + children[i]->index);
                delete children[i];
            }
            gameObjects.erase(gameObjects.begin() + _gameObject->index);
            delete _gameObject;
        }
#pragma endregion

#pragma region Initialization
        void SceneView::Init()
        {
            currentDisplay = Display(gameWindow->width, gameWindow->height, gameWindow);

            UserInit();
        }

        void SceneView::UserInit()
        {
            GameObject* cameraObject = CreateGameObject("Main Camera");
            cameraObject->AddTag(Tag::Main_Camera);
            cameraObject->AddComponent(new Camera(&currentDisplay, currentDisplay.resolution, 5));

            mainCamera = GetMainCamera();
            currentDisplay.camera = mainCamera;

            cameraObject->AddComponent(new CameraInput(mainCamera, *gameWindow->window));

            auto dmy = CreateSpriteObject("Dummy", ASSETS_FOLDER + "Dummy.png", 24, Vector2f(-4, 0));
            auto kst = CreateSpriteObject("Kastelan", ASSETS_FOLDER + "Kastelan Robot.png", 60, Vector2f(-2, -6));
            kst->SetParent(dmy);
            CreateSpriteObject("Fire", ASSETS_FOLDER + "Fire Orb.png", 14, Vector2f(-6, -2));

            GameObject* gridObject = CreateGameObject("Grid");
            auto grid = gridObject->AddComponent(new Grid(20, 20));
            grid->camera = mainCamera;

            GameObject* constructionInputObject = CreateGameObject("Construction Input");
            constructionInputObject->AddComponent(new ConstructionInput(currentDisplay, gridObject->GetComponent<Grid>()));
        }

        void SceneView::Play()
        {
            inPlay = true;

            for (int i = 0; i < gameObjects.size(); ++i)
                if (gameObjects[i] != nullptr) gameObjects[i]->Init();

            for (int i = 0; i < gameObjects.size(); ++i)
                if (gameObjects[i] != nullptr) gameObjects[i]->Start();
        }
#pragma endregion

#pragma region Core Loop
        void SceneView::Update(float _elapsedTime)
        {
            for (int i = 0; i < gameObjects.size(); ++i)
                if (gameObjects[i] != nullptr) gameObjects[i]->Update(_elapsedTime);
        }

        void SceneView::EventUpdate(Event& _event, float _elapsedTime)
        {
            for (int i = 0; i < gameObjects.size(); ++i)
                if (gameObjects[i] != nullptr) gameObjects[i]->EventUpdate(_event, _elapsedTime);
        }

        void SceneView::Render()
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
                auto& tags = *go->GetTagsList();
                for (int i = 0; i < tags.size(); ++i) {
                    if (tags[i] == _tag)
                        return go;
                }
            } return nullptr;
        }
#pragma endregion

#pragma region Shortcut Methods
        GameObject* SceneView::CreateSpriteObject(string _name, string _sprite, int _ppu, Vector2f _position)
        {
            GameObject* sgo = CreateGameObject(_name);
            sgo->AddComponent(new SpriteRenderer(sgo, &currentDisplay, _sprite, _ppu));
            sgo->transform.localPosition = _position;
            return sgo;
        }
#pragma endregion
    }
}
