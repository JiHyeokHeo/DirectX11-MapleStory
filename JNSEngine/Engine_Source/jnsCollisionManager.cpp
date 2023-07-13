#include "jnsCollisionManager.h"
#include "jnsGameObject.h"
#include "jnsScene.h"
#include "jnsSceneManager.h"
#include "jnsLayer.h"
#include "jnsCollider2D.h"

namespace jns
{
	std::bitset<LAYER_MAX> CollisionManager::mMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool>CollisionManager::mCollisionMap = {};

	void CollisionManager::Initialize()
	{
	}
	void CollisionManager::Update()
	{
		for (UINT column = 0; column < (UINT)eLayerType::End; column++)
		{
			for (UINT row = 0; row < (UINT)eLayerType::End; row++)
			{
				if (mMatrix[column][row] == true)
				{
					LayerCollision((eLayerType)column, (eLayerType)row);
				}
			}
		}
	}
	void CollisionManager::LayerCollision(eLayerType left, eLayerType right)
	{
		Scene* activeScene = SceneManager::GetActiveScene();

		const std::vector<GameObject*>& lefts
			= activeScene->GetLayer(left).GetGameObjects();
		const std::vector<GameObject*>& rights
			= activeScene->GetLayer(right).GetGameObjects();

		for (GameObject* leftObj : lefts)
		{
			Collider2D* leftCol = leftObj->GetComponent<Collider2D>();

			if (leftCol == nullptr)
				continue;
			if (leftObj->GetState()
				!= GameObject::eState::Active)
				continue;

			for (GameObject* rightObj : rights)
			{
				Collider2D* rightCol = rightObj->GetComponent<Collider2D>();
				if (rightCol == nullptr)
					continue;
				if (leftObj == rightObj)
					continue;
				if (rightObj->GetState()
					!= GameObject::eState::Active)
					continue;

				ColliderCollision(leftCol, rightCol);
			}
		}


	}
	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{	
		// 두 충돌체의 ID bool값을 확인
		ColliderID id = {};
		id.left = left->GetColliderID();
		id.right= right->GetColliderID();

		// 충돌 정보를 가져온다
		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		if (Intersect(left, right))
		{
			// 충돌
			if (iter->second == false)
			{
				// 최초충돌
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
			}
			else
			{
				// 충돌 중
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			// 충돌 X
			if (iter->second == true)
			{
				// 충돌하고 있다가 나갈떄
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
			}
		}
	
	}
	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{		
		const Vector3& leftColCenterPos = left->GetPosition();
		const Vector3& righColCentertPos = right->GetPosition();

		Vector3 colPosDiff = leftColCenterPos - righColCentertPos;

		
		Vector3 leftColRightVec = left->GetOwner()->GetComponent<Transform>()->Right();
		Vector3 rightColRightVec = right->GetOwner()->GetComponent<Transform>()->Right();
		Vector3 leftColUpVec = left->GetOwner()->GetComponent<Transform>()->Up();
		Vector3 rightColUpVec = right->GetOwner()->GetComponent<Transform>()->Up();
		Vector3 leftColLocalScale = left->GetOwner()->GetComponent<Transform>()->GetScale();
		Vector3 rightColLocalScale = right->GetOwner()->GetComponent<Transform>()->GetScale();
		//CheckSplitShaft(collisionInfo.leftColRight, colPosDiff, collisionInfo);
		//CheckSplitShaft(collisionInfo.rightColRight, colPosDiff, collisionInfo);
		//CheckSplitShaft(collisionInfo.leftColUp, colPosDiff, collisionInfo);
		//CheckSplitShaft(collisionInfo.rightColUp, colPosDiff, collisionInfo);
		// 네모 네모 충돌
		// 분리축 이론

		// To do... (숙제)
		// 분리축이 어렵다 하시는분들은
		// 원 - 원 충돌

		//math::

		return false;
	}
	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool enable)
	{
		UINT row = -1;
		UINT col = -1;

		UINT mLeft = (UINT)left;
		UINT mRight = (UINT)right;

		if (mLeft <= mRight)
		{
			row = mLeft;
			col = mRight;
		}
		else
		{
			row = mRight;
			col = mLeft;
		}

		mMatrix[col][row] = enable; 

	}
	void CollisionManager::Clear()
	{
		mMatrix->reset();
		mCollisionMap.clear();
	}

	//void CollisionManager::CheckSplitShaft(Vector3& colNormalVec, Vector3& colPosDiff, const CollisionInfo& collisionInfo)
	//{
	//	Vector3 colPosDiffProjection = (Vector3)colPosDiff.Dot(colNormalVec);

	//	if(colPosDiffProjection > abs(colNormalVec.Dot(collisionInfo.leftColUp * leftColUp.)
	//}

}