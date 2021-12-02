#pragma once

namespace math
{
	// Constants that we need for maths stuff
#define Const_URotation180        32768
#define Const_PI                  3.14159265358979323
#define Const_RadToUnrRot         10430.3783504704527
#define Const_UnrRotToRad         0.00009587379924285
#define Const_URotationToRadians  Const_PI / Const_URotation180 

	int ClampYaw(int angle) {
		static const auto max = Const_URotation180 * 2;

		while (angle > max)
		{
			angle -= max;
		}

		while (angle < 0) {
			angle += max;
		}
		return angle;
	}
	int ClampPitch(int angle) {
		if (angle > 16000) {
			angle = 16000;
		}
		if (angle < -16000) {
			angle = -16000;
		}
		return angle;
	}

	FRotator VectorToRotation(FVector vVector)
	{
		FRotator rRotation;

		rRotation.Yaw = atan2(vVector.Y, vVector.X) * Const_RadToUnrRot;
		rRotation.Pitch = atan2(vVector.Z, sqrt((vVector.X * vVector.X) + (vVector.Y * vVector.Y))) * Const_RadToUnrRot;
		rRotation.Roll = 0;

		return rRotation;
	}

	FVector RotationToVector(FRotator R)
	{
		float fYaw = R.Yaw * Const_URotationToRadians;
		float fPitch = R.Pitch * Const_URotationToRadians;
		float CosPitch = cos(fPitch);
		FVector Vec = FVector(cos(fYaw) * CosPitch,
			sin(fYaw) * CosPitch,
			sin(fPitch));
		return Vec;
	}

	float VectorMagnitude(FVector Vec) {
		return sqrt((Vec.X * Vec.X) + (Vec.Y * Vec.Y) + (Vec.Z * Vec.Z));
	}

	void Normalize(FVector& v)
	{
		float size = VectorMagnitude(v);

		if (!size)
		{
			v.X = v.Y = v.Z = 1;
		}
		else
		{
			v.X /= size;
			v.Y /= size;
			v.Z /= size;
		}
	}


	float VectorMagnitude(Vec2 Vec) {
		return sqrt((Vec.x * Vec.x) + (Vec.y * Vec.y));
	}
	void Normalize(Vec2& v)
	{
		float size = VectorMagnitude(v);

		if (!size)
		{
			v.x = v.y = 1;
		}
		else
		{
			v.x /= size;
			v.y /= size;
		}
	}


	void GetAxes(FRotator R, FVector& X, FVector& Y, FVector& Z)
	{
		X = RotationToVector(R);
		Normalize(X);
		R.Yaw += 16384;
		FRotator R2 = R;
		R2.Pitch = 0.f;
		Y = RotationToVector(R2);
		Normalize(Y);
		Y.Z = 0.f;
		R.Yaw -= 16384;
		R.Pitch += 16384;
		Z = RotationToVector(R);
		Normalize(Z);
	}

	FVector VectorSubtract(FVector s1, FVector s2)
	{
		FVector temp{};
		temp.X = s1.X - s2.X;
		temp.Y = s1.Y - s2.Y;
		temp.Z = s1.Z - s2.Z;

		return temp;
	}

	FVector VectorAdd(FVector s1, FVector s2)
	{
		FVector temp;
		temp.X = s1.X + s2.X;
		temp.Y = s1.Y + s2.Y;
		temp.Z = s1.Z + s2.Z;

		return temp;
	}

	FVector VectorScale(FVector s1, float scale)
	{
		FVector temp;
		temp.X = s1.X * scale;
		temp.Y = s1.Y * scale;
		temp.Z = s1.Z * scale;

		return temp;
	}

	float VectorDotProduct(const FVector& A, const FVector& B)
	{
		float tempx = A.X * B.X;
		float tempy = A.Y * B.Y;
		float tempz = A.Z * B.Z;

		return (tempx + tempy + tempz);
	}

	void AimAtVector(FVector TargetVec, FVector PlayerLocation, FRotator& AimRot)
	{
		FVector AimVec;
		AimVec.X = TargetVec.X - PlayerLocation.X;
		AimVec.Y = TargetVec.Y - PlayerLocation.Y;
		AimVec.Z = TargetVec.Z - PlayerLocation.Z;

		FRotator AimAtRot = VectorToRotation(AimVec);
		AimRot = AimAtRot;
	}

	FVector GetAngleTo(FVector TargetVec, FVector OriginVec)
	{
		FVector Diff;
		Diff.X = TargetVec.X - OriginVec.X;
		Diff.Y = TargetVec.Y - OriginVec.Y;
		Diff.Z = TargetVec.Z - OriginVec.Z;

		return Diff;
	}

	float GetDistance(FVector to, FVector from) {
		float deltaX = to.X - from.X;
		float deltaY = to.Y - from.Y;
		float deltaZ = to.Z - from.Z;

		return (float)sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
	}

	float GetCrosshairDistance(float Xx, float Yy, float xX, float yY)
	{
		return sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
	}
}

