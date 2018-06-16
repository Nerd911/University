n = 1000
mu1 = 10
mu2 = 1
s = 1
X = rnorm(n, mu1, s)
Y = rnorm(n, mu2, s)
X_avg = mean(X)
Y_avg = mean(Y)
Z = (abs(X_avg - Y_avg)/s)*sqrt(n/2)

n1 = 5
n2 = 10
mu1 = 10
mu2 = 1
s1 = 1
s2 = 5
X = rnorm(n1, mu1, s1)
Y = rnorm(n2, mu2, s1)
X_avg = mean(X)
Y_avg = mean(Y)
s1_sq = var(X)
s2_sq = var(Y)

T = abs(X_avg - Y_avg)/sqrt(s1_sq/n1 + s2_sq/n2)

library(stringr)
tab = read.table("http://www.math.uni.wroc.pl/~mbogdan/Podstawy/Dane/dane5.txt", skip = 5, fill = TRUE, na.strings = ".", fileEncoding="WINDOWS-1252", stringsAsFactors = FALSE)
tab$V1 = as.integer(str_trim(tab$V1))
tab$V2 = as.integer(str_trim(tab$V2))
tab$V3 = as.integer(str_trim(tab$V3))
tab$V4 = as.integer(str_trim(tab$V4))
tab
hist(tab[tab$V1 == 2, 2])
hist(tab[tab$V1 == 1, 2])
hist(tab[tab$V1 == 1, 3])
hist(tab[tab$V1 == 1, 4])
boxplot(tab[tab$V1 == 2, 2], tab[tab$V1 == 1, 2], tab[tab$V1 == 1, 3], tab[tab$V1 == 1, 4], names = c("Grupa\nkontrolna", "Grupa\nbadawcza\n2 dzień", "Grupa\nbadawcza\n4 dzień", "Grupa\nbadawcza\n14 dzień"))


tab = read.table("http://www.math.uni.wroc.pl/~mbogdan/Podstawy/Dane/individuals.dat")
#Kobiety
qqnorm(tab[tab[4] == 2, 5], col = "red")
#Mężczyźni
qqnorm(tab[tab[4] == 1, 5], col = "blue", add = TRUE)

q1 <- qqnorm(tab[tab[4] == 2, 5], plot.it = FALSE)
q2 <- qqnorm(tab[tab[4] == 1, 5], plot.it = FALSE)
plot(range(q1$x, q2$x), range(q1$y, q2$y), type = "n", ylab = "Sample Quantiles", xlab = "Theoretical Quantiles")
points(q1)
points(q2, col = "red", pch = 3)
transincome = tab[tab[5] >= 0, 5]^0.25
transincome
transincome.genre = tab[tab[5] >= 0, 4]
transincome.sector = tab[tab[5] >= 0, 6]
transincome.education = tab[tab[5] >= 0, 3]
q1 <- qqnorm(transincome[transincome.genre == 2], plot.it = FALSE)
q2 <- qqnorm(transincome[transincome.genre == 1], plot.it = FALSE)

plot(range(q1$x, q2$x), range(q1$y, q2$y), type = "n", ylab = "Sample Quantiles", xlab = "Theoretical Quantiles")
points(q1)
points(q2, col = "red", pch = 3)
boxplot(transincome[transincome.sector == 5], transincome[transincome.sector == 6], transincome[transincome.sector == 7], names = c("sektor\nprywatny", "sektor\nrządowy", "samozatrudnienie"))
