#include "jnsMeshRenderer.h"
#include "jnsGameObject.h"
#include "jnsTransform.h"
#include "jnsRenderer.h"

namespace jns
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenderer)
	{
	}
	MeshRenderer::~MeshRenderer()
	{
	}
	void MeshRenderer::Initialize()
	{
	}
	void MeshRenderer::Update()
	{
	}
	void MeshRenderer::LateUpdate()
	{
	}
	void MeshRenderer::Render()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector3 scale = mMaterial->GetTexture()->GetRatio();
		//tr->SetScale(scale);
		tr->BindConstantBuffer();
		
		mMesh->BindBuffer();
		mMaterial->Binds();
		mMesh->Render();

		mMaterial->Clear();
	}
}