---
title: "Lista1"
author: "Mikołaj Słupiński"
date: "12 marca 2018"
output: pdf_document
---

```{r setup, include=FALSE}
knitr::opts_chunk$set(echo = TRUE)
```

## Zadanie 1

Test zadanie 1
```{r zad1}
tab=read.table("http://www.math.uni.wroc.pl/~mbogdan/Podstawy/Dane/table1_6.TXT")
 
# a)
 
colnames(tab) = c("id", "średnia", "IQ", "płeć", "Piers-Harris")
par(mfrow = c(1,3))
hist(tab[[2]])
hist(tab[[3]])
hist(tab[[5]])
mężczyzna = subset(tab, tab[4] == "M")
kobieta = subset(tab, tab[4] == "F")
par(mfrow = c(2,3))
hist(mężczyzna[[2]])
hist(mężczyzna[[3]])
hist(mężczyzna[[5]])
hist(kobieta[[2]])
hist(kobieta[[3]])
hist(kobieta[[5]])
```

## Including Plots

You can also embed plots, for example:

```{r pressure, echo=FALSE}
plot(pressure)
```

Note that the `echo = FALSE` parameter was added to the code chunk to prevent printing of the R code that generated the plot.
