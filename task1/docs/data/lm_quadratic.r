# Data, see solver-perf-processed.results
# Generated by `generate_table.rb r`
Size = c(9, 82, 140, 304, 574, 775, 850, 1070, 1557, 1965)
Time = c(2.0, 3.35, 9.0, 67.2, 408.25, 1014.9, 1309.3, 2601.15, 7844.4, 16175.65)

# Model computation
Size2 <- Size^2
quadratic.model <-lm(Time ~ Size + Size2)
summary(quadratic.model)

## Model: 6.129e-03*x**2 + (-4.283)*x + 4.412e+02
## R-squared:  0.9941
