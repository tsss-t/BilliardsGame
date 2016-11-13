#include "BiliardsTable.h"


BilliardsTable::BilliardsTable() :GameObject(MV1LoadModel("Data/Model/tableNormal.mv1"))
{
	//goInfo->go = this;
	isStatic = true;
	transform->postion = VGet(0, 0, 0);
	btCompoundShape *tabelShape = new btCompoundShape();

	//test用Box
	//btBoxShape *testBox=new btBoxShape(btVector3(btScalar(4), btScalar(20), btScalar(4)));
	//btTransform testTrans;
	//testTrans.setIdentity();
	//testTrans.setOrigin(btVector3(-55, 30, -28));
	//tabelShape->addChildShape(testTrans, testBox);


	//tableの面
	btBoxShape *tabelPanelH = new btBoxShape(btVector3(btScalar(60), btScalar(2), btScalar(26)));
	btBoxShape *tabelPanelVLeft = new btBoxShape(btVector3(btScalar(26), btScalar(2), btScalar(32)));
	btBoxShape *tabelPanelVRight = new btBoxShape(btVector3(btScalar(26), btScalar(2), btScalar(32)));
	btBoxShape *tabelPanelVMid = new btBoxShape(btVector3(btScalar(4), btScalar(2), btScalar(28)));

	//tableの辺
	btBoxShape *tabelSideRight = new btBoxShape(btVector3(btScalar(1.5f), btScalar(2), btScalar(26)));
	btBoxShape *tabelSideLeft = new btBoxShape(btVector3(btScalar(1.5f), btScalar(2), btScalar(26)));
	btBoxShape *tabelSideFrontLeft = new btBoxShape(btVector3(btScalar(25), btScalar(2), btScalar(1.5f)));
	btBoxShape *tabelSideFrontRight = new btBoxShape(btVector3(btScalar(25), btScalar(2), btScalar(1.5f)));
	btBoxShape *tabelSideBackLeft = new btBoxShape(btVector3(btScalar(25), btScalar(2), btScalar(1.5f)));
	btBoxShape *tabelSideBackRight = new btBoxShape(btVector3(btScalar(25), btScalar(2), btScalar(1.5f)));

	//tableの外辺
	btBoxShape *tabelSideOutLeft = new btBoxShape(btVector3(btScalar(1.5f), btScalar(2), btScalar(34)));
	btBoxShape *tabelSideOutRight = new btBoxShape(btVector3(btScalar(1.5f), btScalar(2), btScalar(34)));
	btBoxShape *tabelSideOutFront = new btBoxShape(btVector3(btScalar(62), btScalar(2), btScalar(1.5f)));
	btBoxShape *tabelSideOutBack = new btBoxShape(btVector3(btScalar(62), btScalar(2), btScalar(1.5f)));

	btTransform panelShiftH, panelShiftVLeft, panelShiftVRight, panelShiftVMid, sideShiftRight, sideShiftLeft,
		sideShiftFrontLeft, sideShiftFrontRight, sideShiftBackLeft, sideShiftBackRight,
		sideOutShiftFront, sideOutShiftBack, sideOutShiftLeft, sideOutShiftRight;
	panelShiftH.setIdentity();
	panelShiftVLeft.setIdentity();
	panelShiftVRight.setIdentity();
	panelShiftVMid.setIdentity();
	sideShiftRight.setIdentity();
	sideShiftLeft.setIdentity();
	sideShiftFrontLeft.setIdentity();
	sideShiftFrontRight.setIdentity();
	sideShiftBackLeft.setIdentity();
	sideShiftBackRight.setIdentity();
	sideOutShiftFront.setIdentity();
	sideOutShiftBack.setIdentity();
	sideOutShiftLeft.setIdentity();
	sideOutShiftRight.setIdentity();

	panelShiftH.setOrigin(btVector3(4, 26, 0));
	panelShiftVLeft.setOrigin(btVector3(-24, 26, 0));
	panelShiftVRight.setOrigin(btVector3(31, 26, 0));
	panelShiftVMid.setOrigin(btVector3(4, 26, 0));
	sideShiftLeft.setOrigin(btVector3(-54, 30, 0));
	sideShiftRight.setOrigin(btVector3(61, 30, 0));
	sideShiftFrontLeft.setOrigin(btVector3(-24.5f, 30, -28.5f));
	sideShiftFrontRight.setOrigin(btVector3(31.5f, 30, -28.5f));
	sideShiftBackLeft.setOrigin(btVector3(-24.5f, 30, 28.5f));
	sideShiftBackRight.setOrigin(btVector3(31.5f, 30, 28.5f));
	sideOutShiftFront.setOrigin(btVector3(4, 30, -32));
	sideOutShiftBack.setOrigin(btVector3(4, 30, 32));
	sideOutShiftLeft.setOrigin(btVector3(-58, 30, 0));
	sideOutShiftRight.setOrigin(btVector3(64, 30, 0));

	tabelShape->addChildShape(panelShiftH, tabelPanelH);
	tabelShape->addChildShape(panelShiftVLeft, tabelPanelVLeft);
	tabelShape->addChildShape(panelShiftVRight, tabelPanelVRight);
	tabelShape->addChildShape(panelShiftVMid, tabelPanelVMid);

	tabelShape->addChildShape(sideShiftRight, tabelSideRight);
	tabelShape->addChildShape(sideShiftLeft, tabelSideLeft);
	tabelShape->addChildShape(sideShiftFrontLeft, tabelSideFrontLeft);
	tabelShape->addChildShape(sideShiftFrontRight, tabelSideFrontRight);
	tabelShape->addChildShape(sideShiftBackLeft, tabelSideBackLeft);
	tabelShape->addChildShape(sideShiftBackRight, tabelSideBackRight);
	tabelShape->addChildShape(sideOutShiftFront, tabelSideOutFront);
	tabelShape->addChildShape(sideOutShiftBack, tabelSideOutBack);
	tabelShape->addChildShape(sideOutShiftLeft, tabelSideOutLeft);
	tabelShape->addChildShape(sideOutShiftRight, tabelSideOutRight);

	//btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	SetRigidBody(0, tabelShape);
	rigidBody->setRestitution(btScalar(1.0f));
	rigidBody->setFriction(0.4f);
	MV1SetupCollInfo(modelHandle, -1, 8, 8, 8);
}


BilliardsTable::~BilliardsTable()
{

}

bool BilliardsTable::Draw()
{
	MV1SetPosition(this->modelHandle, VGet(transform->postion.x , transform->postion.y, transform->postion.z));
	MV1SetRotationXYZ(this->modelHandle, transform->rotation);
	MV1DrawModel(this->modelHandle);
	return true;
}

bool BilliardsTable::Update(float stepTime)
{
	GameObject::Update(stepTime);
	//x++;
	return true;
}
