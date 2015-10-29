// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BackgroundTask.h"
#include "RealSenseUtility.h"
#include "RealSenseFaceWorker.generated.h"

class DataCollector;
class URealSenseJoint;
class URealSenseHand;
class URealSenseFace;
class URealSenseFaceExpressions;
class URealSenseFaceLandmarkPoint;

//To do: separate this into three modules one for face one for hand, and one extra for raw streams
//NB: copy structs with raw types, which allows for safe and quick pointer access without locks

/**
 * 
 */
UCLASS()
class URealSenseFaceWorker : public UBackgroundTask 
{
	friend class DataCollector;

	GENERATED_BODY()
public:
	//Called on Game thread
	void StartTask();
	void EndTask();
	void ConsumerTick(float DeltaTime);

	//Custom Game thread interaction
	void EnableHandDetection(bool enable);
	void EnableGestureDetection(bool enable, FString singleGesture);
	void EnableFaceDetection(bool enable);

	void SetInterfaceDelegate(UObject* object);

protected:
	//Called on Input thread
	void OnTaskTick() override;
	void OnTaskInit() override;
	void OnTaskShutdown() override;

	//Consumer Processing
	void ProcessHandData();
	void ProcessFaceData();

	void CheckGesturesForHand(PXCHandData::IHand* hand);

	//Temp UObjects
	URealSenseJoint* tempJoint = nullptr;
	URealSenseHand* tempHand = nullptr;
	URealSenseFace* tempFace = nullptr;
	URealSenseFaceExpressions* tempExpressions = nullptr;
	URealSenseFaceLandmarkPoint* tempLandmark = nullptr;

	FThreadSafeBool consumerHasRead;
	bool HandEnabled = false;
	bool FaceEnabled = false;
private:
	DataCollector *collector = nullptr;
};
