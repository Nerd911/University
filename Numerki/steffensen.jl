setprecision(128)
function steffensen(f, eps::BigFloat, x0::BigFloat)
  xn = x0

  while(abs(f(xn)) > eps)
    xn = xn - ((f(xn)) ^ 2) / (f(xn + f(xn)) - f(xn))
    println(xn - 5.885327439818610774324520457029037628825e-01)
  end

  return xn
end

f(x::BigFloat) = e^(-x) - sin(x)

println(steffensen(f, BigFloat(1e-30), BigFloat(4.0)))
