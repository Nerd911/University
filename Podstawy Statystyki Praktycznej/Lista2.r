tab = read.table("http://www.math.uni.wroc.pl/~mbogdan/Podstawy/Dane/individuals.dat")
par(mfrow=c(1,1))
income_mean = mean(tab[[5]])
income_median = median(tab[[5]])
income_sd = sd(tab[[5]])
income_iqr = IQR(tab[[5]])
tab[[3]] >= 5
round(length(tab[tab[[3]] >= 5,3])/length(tab[[3]]) * 100)
income_left = income_mean - 2 * income_sd
income_right = income_mean + 2 * income_sd
length(tab[tab[[5]] >= income_left && tab[[5]] <= income_right,5]) / length(tab[[5]])
income_left
income_right
set.seed(453)
s = tab[sample(dim(tab)[1], 1000), 5]
v = sapply(1:1000, function(i) c(mean(s[1:i]), median(s[1:i]), IQR(s[1:i]), sd(s[1:i])))
plot(v[2,], type = 'l')
sapply(1:1000, function(i) c(mean(s[1:i]), median(s[1:i]), IQR(s[1:i]), sd(s[1:i])))

w = sapply(1:10, function(x) {
  s = tab[sample(dim(tab)[1], 1000), 5]
  return(sapply(1:1000, function(i) c(mean(s[1:i]), median(s[1:i]), IQR(s[1:i]), sd(s[1:i]))))
})

u = array(0, c(10, 4, 1000))
for(i in 1:10)
{
  s = tab[sample(dim(tab)[1], 1000), 5]
  u[i,,] = sapply(1:1000, function(i) c(mean(s[1:i]), median(s[1:i]), IQR(s[1:i]), sd(s[1:i])))
}
matplot(t(u[,1,]), type = "l")
abline(mean(tab[[5]]), 0)
p = round(table(tab[[6]])/dim(tab)[1] * 1000)
l = list(sample(which(tab[6] == names(p)[[1]]), p[1]),
      sample(which(tab[6] == names(p)[[2]]), p[2]),
      sample(which(tab[6] == names(p)[[3]]), p[3]))
for(i in 1:10) {
  p = round(table(tab[, 6])/dim(tab)[1] * i*100)
  indices = c(l[[1]][1:p[1]], l[[2]][1:p[2]], l[[3]][1:p[3]])
  s = tab[indices,]
  v = sapply(1:1000, function(i) c(mean(s[1:i,5]), median(s[1:i,5]), IQR(s[1:i,5]), sd(s[1:i,5]), at_least_bachelor(s[1:i,])))
}
sapply(1:10, function(i) c(mean(tab[[5]][1:100*i]), median(tab[[5]][1:100*i])))
r = matrix(sample(0:1, 10000,replace = TRUE), 1000, 10)
sapply(2:1000, function(i) apply(r[1:i,],2,sum))

tab = read.table("http://www.math.uni.wroc.pl/~mbogdan/Podstawy/Dane/individuals.dat")
par(mfrow=c(1,1))
at_least_bachelor <- function(tab) {
  return(round(length(tab[tab[[3]] >= 5,3])/length(tab[[3]]) * 100))
}
income_mean = mean(tab[[5]])
income_median = median(tab[[5]])
income_sd = sd(tab[[5]])
income_iqr = IQR(tab[[5]])
at_least_bachelor_percent = at_least_bachelor(tab)
income_left = income_mean - 2 * income_sd
income_right = income_mean + 2 * income_sd
length(tab[tab[[5]] >= income_left && tab[[5]] <= income_right,5]) / length(tab[[5]])
u = array(0, c(10, 5, 1000))
for(i in 1:10)
{
  indices = sample(dim(tab)[1], 1000)
  s = tab[indices, 5]
  u[i,,] = sapply(1:1000, function(i) c(mean(s[1:i]), median(s[1:i]), IQR(s[1:i]), sd(s[1:i]), at_least_bachelor(tab[indices,][1:i,])))
}
matplot(t(u[,1,]), type = "l", main = "Trajektorie średniej")
abline(income_mean, 0)
matplot(t(u[,2,]), type = "l", main = "Trajektorie mediany")
abline(income_median, 0)
matplot(t(u[,3,]), type = "l", main = "Trajektorie IQR")
abline(income_iqr, 0)
matplot(t(u[,4,]), type = "l", main = "Trajektorie odchylenia standardowego")
abline(income_sd, 0)
matplot(t(u[,5,]), type = "l", main = "Trajektorie procenta osób z conajmniej licencjatem")
abline(at_least_bachelor_percent, 0)


p = round(table(tab[[6]])/dim(tab)[1] * 1000)
l = list(sample(which(tab[6] == names(p)[[1]]), p[1]),
         sample(which(tab[6] == names(p)[[2]]), p[2]),
         sample(which(tab[6] == names(p)[[3]]), p[3]))
for(i in 1:10) {
  p = round(table(tab[, 6])/dim(tab)[1] * i*100)
  indices = c(l[[1]][1:p[1]], l[[2]][1:p[2]], l[[3]][1:p[3]])
  s = tab[indices,]
  v = sapply(1:(i*100), function(x) c(mean(s[1:x,5]), median(s[1:x,5]), IQR(s[1:x,5]), sd(s[1:i,5]), at_least_bachelor(s[1:i,])))
  print(v[1,])
  #matplot(v[1], type = "l", main = "Trajektorie średniej")
  #abline(income_mean, 0)
  #matplot(v[2], type = "l", main = "Trajektorie mediany")
  #abline(income_median, 0)
  #matplot(v[3], type = "l", main = "Trajektorie IQR")
  #abline(income_iqr, 0)
  #matplot(v[4], type = "l", main = "Trajektorie odchylenia standardowego")
  #abline(income_sd, 0)
  #matplot(v[5], type = "l", main = "Trajektorie procenta osób z conajmniej licencjatem")
  #abline(at_least_bachelor_percent, 0)
}
