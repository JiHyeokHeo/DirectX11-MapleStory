#include "jnsRutabysBossBG.h"
#include "jnsResources.h"
#include "jnsTransform.h"

namespace jns
{
	RutabysBossBG::RutabysBossBG()
	{
	}
	RutabysBossBG::~RutabysBossBG()
	{
	}
	void RutabysBossBG::Initialize()
	{
		mr = GetComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"RutabysBossBGMaterial"));
		tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		tr->SetScale(Vector3(8.0f, 4.5f, 0.0f));

		BGBase::Initialize();
	}
	void RutabysBossBG::Update()
	{
		BGBase::Update();
	}
	void RutabysBossBG::LateUpdate()
	{
		BGBase::LateUpdate();
	}
	void RutabysBossBG::Render()
	{
		BGBase::Render();
	}
}