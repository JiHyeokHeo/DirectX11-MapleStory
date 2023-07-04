#include "jnsPlayScene.h"
#include "CommonSceneInclude.h"

namespace jns
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		CreateMainCamera();
		CreateUICamera();
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::CreateMainCamera()
	{
		GameObject* maincamera = object::InstantiateUIandBG<GameObject>(eLayerType::Camera);
		maincamera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* maincameraComp = maincamera->AddComponent<Camera>();
		maincameraComp->TurnLayerMask(eLayerType::UI, false);
		maincamera->AddComponent<CameraScript>();
	}

	void PlayScene::CreateUICamera()
	{
		GameObject* uicamera = object::InstantiateUIandBG<GameObject>(eLayerType::Camera);
		uicamera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* uicameraComp = uicamera->AddComponent<Camera>();
		uicameraComp->TurnLayerMask(eLayerType::Player, false);
		uicameraComp->TurnLayerMask(eLayerType::BG, false);
	}

	void PlayScene::CreatePlayerUI()
	{
		// 1600 x 900 Display Resolution
		object::InstantiateUIandBG<ExpBar>(eLayerType::UI);
		object::InstantiateUIandBG<ExpMaxBar>(eLayerType::UI);
		object::InstantiateUIandBG<SkillQuickSlotBackUI>(eLayerType::UI);
		
		GameObject* mStatus = object::InstantiateUIandBG<CenterStatus>(eLayerType::UI);
		GameObject* mHpBar= object::InstantiateUIandBG<HpBar>(eLayerType::UI);
		mHpBar->GetComponent<Transform>()->SetParent(mStatus->GetComponent<Transform>());
		GameObject* mMpBar = object::InstantiateUIandBG<MpBar>(eLayerType::UI);
		mMpBar->GetComponent<Transform>()->SetParent(mStatus->GetComponent<Transform>());
		
		
		
	}
}