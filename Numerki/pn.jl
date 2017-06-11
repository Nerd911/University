setprecision(128)

c(n) = (n == 2) ? BigFloat(0.0) : sqrt(BigFloat(0.5) * (BigFloat(1.0) + c(n-1)))
s(n) = (n == 2) ? BigFloat(1.0) : sqrt(BigFloat(0.5) * (BigFloat(1.0) - c(n-1)))
p(n) = (n == 2) ? BigFloat(2.0) : BigFloat(2.0)^(n - 1) * s(n)
p1(n) = BigFloat(0.5) * BigFloat(2.0) ^ n * sin(BigFloat(2.0)*pi / BigFloat(2.0) ^ n)
for i in 2:256
  print("p($i) = ")
  println(p(i))
  print("p1($i) = ")
  println(p1(i))
end
