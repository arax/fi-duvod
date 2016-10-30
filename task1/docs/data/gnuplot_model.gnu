#!/usr/bin/gnuplot

#
#
#

set terminal png

# Line width of the axes
set border linewidth 1.5

# Props
set ylabel "Time in ms"
set xlabel "Molecule size"
set title  "Model vs. Data"
set grid
set xrange [0:2000]

# Line styles
set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2
set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2
set style line 3 linecolor rgb '#00ff00' linetype 1 linewidth 2

# Functions
f(x) = 7.14*x + (-2285.98)
g(x) = 6.129e-03*x**2 + (-4.283)*x + 4.412e+02

# PNG file
set output "images/solver-perf-model.png"

# Plot
plot 'data/solver-perf-processed.results' title 'Data' with p linestyle 1, \
     f(x) title 'Model 1' with lines linestyle 2, \
     g(x) title 'Model 2' with lines linestyle 3
