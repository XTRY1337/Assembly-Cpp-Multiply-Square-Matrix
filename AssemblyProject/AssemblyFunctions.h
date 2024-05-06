#ifndef ASSEMBLYFUNCTIONS_H
#define ASSEMBLYFUNCTIONS_H

#pragma once

extern "C" {
    // Main Function
    void MultiplyMatrixWithAssembly(float* resultMatrix, float* matrixOne, float* matrixTwo, int size);

    // Transpose Function
    void TransposeMatrixAssembly(float* matrixToTranspose, int size);
}

#endif