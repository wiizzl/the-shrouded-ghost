#pragma once

#include "Vector.h"
#include "Quat.h"
#include "Matrix.h"
#include "Rotator.h"

struct FTransform
{
    FQuat Rotation;
    FVector Translation;
    char UnknownData00[0x4];
    FVector Scale3D;
    char UnknownData01[0x4];

    FTransform() : Rotation(0.f, 0.f, 0.f, 1.f), Translation(0.f), Scale3D(FVector::OneVector)
    {
        for (int i = 0; i < 4; ++i)
        {
            UnknownData00[i] = 0;
            UnknownData01[i] = 0;
        }
    }

    FMatrix ToMatrixWithScale() const;

    FVector TransformPosition(FVector& V) const;

    FTransform(const FRotator& InRotation) : Rotation(InRotation.Quaternion()), Translation(FVector::ZeroVector), UnknownData00{ 0 }, Scale3D(FVector::OneVector), UnknownData01{ 0 } {}
};