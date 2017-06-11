#Created by Mikołaj Słupiński on 15.10.2016
#=
  This program computes inverse of a matrix using LUP decomposition.
=#

"""This function performs LUP decomposition of matrix.
Arguments:
A is a matrix to be decomposed.
P is array of permutations.
eps is a value to aproximate zeros.
Th result is stored in matrix A.
"""
function luDecompose(A::Array{Float64,2}, P::Array{Int64}, eps::Float64 = 1e-10)
  size = length(A[1,:])
  kd = 1
  for i in 1:size
    P[i] = i
  end

  for k in 1:size-1
    p = 0.0
    for i in k:size
      t = A[i][k]
      if t < 0.0
        t *= -1.0
      end
      if t > p
        p = t
        kd = i
      end
    end

    if abs(p) < eps
      return -1 #singular matrix
    end

#Rows swap
    T = P[kd]
    P[kd] = P[k]
    P[k] = T

    for i in 1:size
      t = A[kd, i]
      A[kd, i] = A[k, i]
      A[k, i] = t
    end

    for i in k+1:size #substraction needed to decompose A as LU
      A[i,k] = A[i,k]/A[k,k]
      for j in k+1:size
        A[i, j] -= A[i, k] * A[k, j]
      end
    end
    return 0
  end
end

"""This function calculates inverse of the matrix A given in the LU decomposed form
and its pivot.
Arguments:
P is an array of permutations.
LU is LU decommposed matrix.
Result is stored in LU matrix.
"""
function luInverse(LU::Array{Float64, 2}, P::Array{Int64})
  size = length(LU[1,:])

#initializing vectors
  X = zeros(Float64, size)
  Y = zeros(Float64, size)

#identity matrix
  B = eye(size)

#solving equation Ly = Pb
  for i in 1:size
    for n in 1:size
      t = 0.0
      for m in 1:n-1
        t += LU[n, m]*Y[m]
      end
      Y[n] = B[i, P[n]] - t
    end

#solving Ux = y
    for n in size:-1:1
      t = 0.0
      for m in n+1:size
        t += LU[n, m] * X[m]
      end
        X[n] = (Y[n] - t)/LU[n, n]
    end

    for j in 1:size
      B[i, j] = X[j] #copying X into the row of B
    end
  end
#B contains now transposed inverse of matrix A

#Transposing B and moving it to LU
  for i in 1:size
    for j in 1:size
      LU[i, j] = B[j, i]
    end
  end
#LU is now inverse of A
  return 0
end
