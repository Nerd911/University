EPS = BigFloat(0.000001)

function bairstow(a, u, v)
  n = length(a)
  b = Array{BigFloat}(n)
  c = Array{BigFloat}(n)
  b[n] = a[n]
  c[n] = 0
  c[n - 1] = a[n]
  for i in 1:10
    b[n - 1] = a[n - 1] + u * b[n]
    for j = (n - 2):-1:1
      b[j] = a[j] + u * b[j + 1] + v * b[j + 2]
      c[j] = b[j + 1] + u * c[j + 1] + v * c[j + 2]
    end
    J = c[1] * c[3] - (c[2] ^ 2)
    du = (c[2] * b[2] - c[3] * b[1]) / J
    dv = (c[2] * b[1] - c[1] * b[2]) / J
    if abs(du) < EPS && abs(dv) < EPS
      return (u, v)
    end
    u += du
    v += dv
  end
  return (u, v)
end

function getRoots(u, v)
  u = -u
  v = -v
  delta = (u ^ 2 - 4 * v)
  p1 = (-u / 2)
  p2 = (sqrt(Complex(delta)) / 2)
  return (p1 + p2, p1 - p2)
end

function divPolynomal(a, u, v)
  n = length(a) - 2
  b = Array{BigFloat}(n)
  b[n] = a[n + 2]
  b[n - 1] = a[n + 1] + u * b[n]
  for i in (n - 2):-1:1
    b[i] = a[i + 2] + u * b[i + 1] + v * b[i + 2]
  end
  return b
end

function main()
  set_bigfloat_precision(128)
  u = BigFloat(0.1)
  v = BigFloat(0.1)
  pol = [1, 2, 3, 4, 5]
  (u, v) = bairstow(pol, u, v)
  println(u, " ", v)
  roots = getRoots(u, v)
  println(roots[1], " ", roots[2])
  pol = divPolynomal(pol, u, v)
  println()
  println(pol)
  u = BigFloat(0.1)
  v = BigFloat(0.1)
  (u, v) = bairstow(pol, u, v)
  println(u, " ", v)
  roots = getRoots(u, v)
  println(roots[1], " ", roots[2])
end

main()
