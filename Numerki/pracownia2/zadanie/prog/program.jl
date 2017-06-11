
#Created by Mikołaj Słupiński on 01.12.2016
#=
  This program computes roots of a nonlinear equation using Halley's and quasi-Halley's methods.
=#

"""A function that calculates roots of a nonlinear equation using Halley's method.
   The arguments are:
   x0 - starting point
   f - function representing nonlinear equation
   f1 - derivative of function f
   f2 - second derivative of function f
   eps - value used to compare floating point numbers
   maxIter - maximal number of iterations
   maxVal - maximal value of function, if function returns greater value it diverges

   Return value:
   (retVal, xk, it, message, roundings)
   where
   retVal - value representing success or failure of computations
   xk - the kth rounding of root
   it - number of iterations
   message - string containing informations about result
   roundings - array of roundings of root
"""
function halley(x0, f, f1, f2, eps = 1e-10, maxIter = 100, maxVal = 1000)
  #initializing variables
  xk = x0
  roundings = [xk]
  message = "No convergence after $maxIter iterations."
  retVal = -1
  it = 0

  while(it < maxIter)
    it+=1
    xk = xk - f(xk)/(f1(xk) - (f2(xk)/(2*f1(xk)))*f(xk))
    push!(roundings, xk)

    #function converges to 0
    if(abs(f(xk)) < eps)
      message = "Solution: $xk\nConverges after $it iterations."
      retVal = 0
      break
    end

    #function diverges
    if(abs(f(xk)) > maxVal)
      message = "Solution diverges after $it iterations."
      retVal = -2
      break
    end
  end

  return retVal, xk, it, message, roundings
end

"""A function that calculates roots of a nonlinear equation using quasi-Halley's method.
   The arguments are:
   x0, x1 - starting points
   f - function representing nonlinear equation
   f1 - derivative of function f
   eps - value used to compare floating point numbers
   maxIter - maximal number of iterations
   maxVal - maximal value of function, if function returns greater value it diverges

   Return value:
   (retVal, xk, it, message, roundings)
   where
   retVal - value representing success or failure of computations
   xk - the kth rounding of root
   it - number of iterations
   message - string containing informations about result
   roundings - array of roundings of root
"""

function quasiHalley(x0, x1, f, f1, eps = 1e-10, maxIter = 100, maxVal = 1000)
  #initializing variables
  xk1 = x0
  xk = x1
  roundings = [xk1, xk]
  message = "No convergence after $maxIter iterations."
  retVal = -1
  it = 0

  while(it < maxIter)
    it+=1
    x_temp = xk
    xk = xk - f(xk)/(f1(xk) - ((f1(xk) - f1(xk1))/(2*(xk - xk1)*f1(xk)))*f(xk))
    xk1 = x_temp
    push!(roundings, xk)

    #function converges to 0
    if(abs(f(xk)) < eps)
      message = "Solution: $xk\nConverges after $it iterations."
      retVal = 0
      break
    end

    if(abs(f(xk)) > maxVal)
      message = "Solution diverges after $it iterations."
      retVal = -2
      break
    end
  end

  return retVal, xk, it, message, roundings
end
