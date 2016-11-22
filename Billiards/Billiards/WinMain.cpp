#include "System.h"
#include <Windows.h>
#include "UILabel.h"
#include "UISprite.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	System* system =System :: GetSystemInstance();
	system->SystemMain();

	return 0;
}
//int main()
//{
//	///-----includes_end-----
//
//	int i;
//	///-----initialization_start-----
//
//	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
//	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
//
//	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
//	btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);
//
//	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
//	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
//
//	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
//	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
//
//	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
//
//	dynamicsWorld->setGravity(btVector3(0, -10, 0));
//
//	///-----initialization_end-----
//
//	//keep track of the shapes, we release memory at exit.
//	//make sure to re-use collision shapes among rigid bodies whenever possible!
//	btAlignedObjectArray<btCollisionShape*> collisionShapes;
//
//
//	///create a few basic rigid bodies
//
//	//the ground is a cube of side 100 at position y = -56.
//	//the sphere will hit it at y = -6, with center at -5
//	{
//		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
//
//		collisionShapes.push_back(groundShape);
//
//		btTransform groundTransform;
//		groundTransform.setIdentity();
//		groundTransform.setOrigin(btVector3(0, -56, 0));
//
//		btScalar mass(0.);
//
//		//rigidbody is dynamic if and only if mass is non zero, otherwise static
//		bool isDynamic = (mass != 0.f);
//
//		btVector3 localInertia(0, 0, 0);
//		if (isDynamic)
//			groundShape->calculateLocalInertia(mass, localInertia);
//
//		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
//		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
//		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
//		btRigidBody* body = new btRigidBody(rbInfo);
//
//		//add the body to the dynamics world
//		dynamicsWorld->addRigidBody(body);
//	}
//
//
//	{
//		//create a dynamic rigidbody
//
//		//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
//		btCollisionShape* colShape = new btSphereShape(btScalar(1.));
//		collisionShapes.push_back(colShape);
//
//		/// Create Dynamic Objects
//		btTransform startTransform;
//		startTransform.setIdentity();
//
//		btScalar	mass(1.f);
//
//		//rigidbody is dynamic if and only if mass is non zero, otherwise static
//		bool isDynamic = (mass != 0.f);
//
//		btVector3 localInertia(0, 0, 0);
//		if (isDynamic)
//			colShape->calculateLocalInertia(mass, localInertia);
//
//		startTransform.setOrigin(btVector3(2, 10, 0));
//
//		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
//		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
//		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
//		btRigidBody* body = new btRigidBody(rbInfo);
//
//		dynamicsWorld->addRigidBody(body);
//	}
//
//
//
//	/// Do some simulation
//
//
//	///-----stepsimulation_start-----
//	for (i = 0; i<150; i++)
//	{
//		dynamicsWorld->stepSimulation(1.f / 60.f, 10);
//
//		//print positions of all objects
//		for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
//		{
//			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
//			btRigidBody* body = btRigidBody::upcast(obj);
//			btTransform trans;
//			if (body && body->getMotionState())
//			{
//				body->getMotionState()->getWorldTransform(trans);
//
//			}
//			else
//			{
//				trans = obj->getWorldTransform();
//			}
//			printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
//		}
//	}
//
//	///-----stepsimulation_end-----
//
//	//cleanup in the reverse order of creation/initialization
//
//	///-----cleanup_start-----
//
//	//remove the rigidbodies from the dynamics world and delete them
//	for (i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
//	{
//		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
//		btRigidBody* body = btRigidBody::upcast(obj);
//		if (body && body->getMotionState())
//		{
//			delete body->getMotionState();
//		}
//		dynamicsWorld->removeCollisionObject(obj);
//		delete obj;
//	}
//
//	//delete collision shapes
//	for (int j = 0; j<collisionShapes.size(); j++)
//	{
//		btCollisionShape* shape = collisionShapes[j];
//		collisionShapes[j] = 0;
//		delete shape;
//	}
//
//	//delete dynamics world
//	delete dynamicsWorld;
//
//	//delete solver
//	delete solver;
//
//	//delete broadphase
//	delete overlappingPairCache;
//
//	//delete dispatcher
//	delete dispatcher;
//
//	delete collisionConfiguration;
//
//	//next line is optional: it will be cleared by the destructor when the array goes out of scope
//	collisionShapes.clear();
//}
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更,初期化,裏画面設定
//
//	int x, y, Mouse, Wheel, Image;
//	double size = 1.0;
//	//float q = 0;
//	int model;
//	model = MV1LoadModel("Data/Model/tableNormal.MV1");
//
//	FLOAT2 positionPre = { 0,0 };
//	FLOAT2 moveDis = { 0,0 };
//	//奥行0.1～1000までをカメラの描画範囲とする
//	SetCameraNearFar(0.1f, 1000.0f);
//	VECTOR xAxis, yAxis, zAxis;
//	Label * L1 = new Label();
//	L1->string = "test";
//	L1->SetPosition({ 100,100 });
//	
//	Sprite* s1 = new Sprite("Data/2D/1.png",17,6,3,80,69);
//	s1->SetPosition({ 200,100 });
//	s1->SimpleMove(3.0f, { 200,100 }, { 600,200 }, TweenType::Once);
//	s1->SetTweenColor(1.0f, TweenType::PingPong);
//	//(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
//	//SetCameraPositionAndTarget_UpVecY(VGet(0, 10, -20), VGet(0.0f, 10.0f, 0.0f));
//	SetCameraPositionAndAngle(VGet(0, 10, -20), 0, 0, 0);
//	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
//
//#pragma region input
//		Mouse = GetMouseInput();                //マウスの入力状態取得
//		Wheel = GetMouseWheelRotVol();  //ホイールの回転量取得
//		GetMousePoint(&x, &y);                //マウスの座標取得
//
//		moveDis = { x - positionPre.u,y - positionPre.v };
//		positionPre = { (float)x,(float)y };
//
//		//viewMatrix = GetCameraViewMatrix();
//
//
//		if (Mouse & MOUSE_INPUT_LEFT) { //マウスの左ボタンが押されていたら
//			DrawString(0, 0, "左ボタンが押されています", GetColor(255, 255, 255));
//			float x = GetCameraPosition().x;
//			float y = GetCameraPosition().y;
//			float z = GetCameraPosition().z;
//
//
//
//		}
//		if (Mouse & MOUSE_INPUT_RIGHT) { //マウスの左ボタンが押されていたら
//			DrawString(300, 0, "右ボタンが押されています", GetColor(255, 255, 255));
//
//			SetCameraPositionAndAngle(GetCameraPosition(),
//				GetCameraAngleVRotate() + moveDis.v* PI / 180, GetCameraAngleHRotate(), 0);
//			SetCameraPositionAndAngle(GetCameraPosition(), GetCameraAngleVRotate(), GetCameraAngleHRotate() + moveDis.u*PI / 180, 0);
//
//
//
//		}
//		if (Mouse & MOUSE_INPUT_MIDDLE) { //マウスの左ボタンが押されていたら
//			DrawString(300, 0, "中ボタンが押されています", GetColor(255, 255, 255));
//			//translateMatrix = MGetTranslate(VGet(moveDis.u*0.1f, -moveDis.v*0.1f, 0));
//			VECTOR cameraRight = GetCameraRightVector();
//			VECTOR cameraUp = GetCameraUpVector();
//			SetCameraPositionAndAngle(
//			{
//				GetCameraPosition().x - cameraRight.x*0.1f*moveDis.u + cameraUp.x*0.1f*moveDis.v,
//				GetCameraPosition().y - cameraRight.y*0.1f*moveDis.u + cameraUp.y*0.1f*moveDis.v,
//				GetCameraPosition().z - cameraRight.z*0.1f*moveDis.u + cameraUp.z*0.1f*moveDis.v }, GetCameraAngleVRotate(), GetCameraAngleHRotate(), 0
//				);
//
//		}
//		if (Wheel > 0) {        //ホイールが+方向に回転していたら
//			VECTOR cameraFront = GetCameraFrontVector();
//			SetCameraPositionAndAngle(
//			{
//				GetCameraPosition().x + cameraFront.x,
//				GetCameraPosition().y + cameraFront.y,
//				GetCameraPosition().z + cameraFront.z }, GetCameraAngleVRotate(), GetCameraAngleHRotate(), 0
//				);
//			//translateMatrix = MInverse(MGetTranslate(VGet(0, 0, 1.0f)));
//		}
//		if (Wheel < 0) {        //ホイールが－方向に回転していたら
//								//translateMatrix = MInverse(MGetTranslate(VGet(0, 0, -1.0f)));
//			VECTOR cameraFront = GetCameraFrontVector();
//			SetCameraPositionAndAngle(
//			{
//				GetCameraPosition().x - cameraFront.x,
//				GetCameraPosition().y - cameraFront.y,
//				GetCameraPosition().z - cameraFront.z }, GetCameraAngleVRotate(), GetCameraAngleHRotate(), 0
//				);
//		}
//#pragma endregion
//		
//
//		MV1DrawModel(model);
//		s1->Update(1.0f/60.0f);
//		s1->Draw();
//		L1->Draw();
//
//	}
//
//	DxLib_End();
//	return 0;
//}
//
