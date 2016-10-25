#!/usr/bin/gnuplot

#
#
#

set terminal png
set style line 1 lc rgb 'black' pt 5

set ylabel "Time in ms"
set xlabel "Measurement ID"
set title "%%HEADER%%"
set grid

set xtics 1
set yrange [%%YMIN%%:%%YMAX%%]

set output "%%OUTPUT_FILE%%"
plot "%%INPUT_FILE%%" ls 1 notitle
