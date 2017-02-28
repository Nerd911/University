#Created by Mikołaj Słupiński on 05.01.2017
#=
  This program computes roots of a system of nonlinear equations using Newton's method.
=#

T(n, x) = cos(n* acos(x)) #a value of n-th Chebyshev's polynomial of the first kind
u(n, k) = cos(k*pi/(n+1)) #a k-th extremum of n-th Chebyshev's polynomial of the first kind

"""A function calculating coefficients in quadrature"""
function a(j, n, f)
  eps = (j == n) ? 1 : 2
  res = 0.5 * f(u(n-1, 0))*T(0,u(n-1, j))
  for k in 1:n-1
    res = res + f(u(n-1, k))*T(k,u(n-1, j))
  end
  if n != 0
    res = res + 0.5 * f(u(n-1, n)) * T(n,u(n-1, j))
  end

  return (eps/n)*res
end


b(k, n, f) = (a(2*k - 2, n, f) - a(2*k, n, f)) / (4*k - 2) #Approximated integral intervals

"""A function approximating integrals
  Arguments:
  n - number of approximation points, must be an even number
  f - approximated function

  Return value:
  single floating point number representing value of integral on interval [-1,1]
"""
function I(n, f)
  res = 0.0
  for k in 1:(n/2)
    res = res + b(k, n, f)
  end
  return 2.0 * res
end
