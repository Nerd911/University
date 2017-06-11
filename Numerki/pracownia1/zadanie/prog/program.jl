#Created by Mikołaj Słupiński on 20.10.2016
#=
  This program computes roots of a system of nonlinear equations using Newton's method.
=#
include("lufactor.jl")

"""A function that calculates norm of a vector"""
function usrNorm(x)
  res = 0.0
  for y in x
    res += y*y
  end
  return sqrt(res)
end


function findMax(x)
  max = abs(x[1])
  for y in x
    if abs(y) > max
      max = abs(y)
    end
  end
  return max
end

"""A function that calculates roots of system of nonlinear equations.
   The arguments are:
   x0 - starting point
   f - function representing system of nonlinear equations
   J - Jacobian of function f
   maxIter - maximal number of iterations
   epsilon - value used to compare floating point numbers
   maxVal - maximal value of function, if function returns greater value it diverges

   Return value:
   (xn, iter, message, roundings)
   where
   xn - the nth rounding of root
   iter - number of iterations
   message - string containing informations about result
   roundings - array of roundings of root
"""
function newton(x0, f, J, maxIter = 100, epsilon = 1e-14, maxVal = 1000.0)
  #initializing variables
  size = length(x0)
  xn = x0
  P = Array{Int64}(size)
  n = maxIter
  roundings = [xn]
  message = "No convergence after $maxIter iterations."
  retVal = -1

  while(n>0)
    n = n-1
    JJ = J(xn) #evaluating Jacobian
    if luDecompose(JJ, P, epsilon) == -1 #the determinant is equal to 0, matrix is singular
      message = "Matrix is singular"
      retVal = -2
      break
    end

    luInverse(JJ, P) #Reversing Jacobian
    xn = xn - JJ * f(xn)
    push!(roundings, xn)
    if usrNorm(f(xn)) < epsilon #solution converges
      message = "Solution: $xn\nConverges after $(maxIter - n) iterations"
      retVal = 0
      break
    end

    if usrNorm(f(xn)) > maxVal #solution diverges
      message = "Solution diverges"
      retVal = -3
      break
    end

  end
  return xn, maxIter - n, message, roundings
end
