#!/usr/bin/gnuplot

#
#
#

set terminal png

# Line width of the axes
set border linewidth 1.5

# Props
set key outside
set key right top

set ylabel "Time in ms"
set xlabel "Molecule size"
set title  "Model vs. Data"
set grid
set xrange [0:2000]

# Line styles
set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2 pt 9
set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2

# Function
f(x) = 2.393e-06*x**3 + (-7.500e-04)*x**2 + 4.696e-01*x + (-3.422e+01)

# PNG file
set output "images/solver-perf-model.png"

# Plot
plot f(x) title 'Model(n^3)' with lines linestyle 2, \
     'data/solver-perf-processed.results' title 'Data' with p linestyle 1

