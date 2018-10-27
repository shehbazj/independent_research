#!/usr/bin/env gnuplot

# set terminal pdf noenhanced
set term postscript eps noenhanced color solid 22
set output 'bar.eps'

set style data histogram
set style histogram cluster gap 1

set key inside left

set xlabel 'Block Size'
set ylabel 'Time'

set style fill solid border rgb "black"
set auto x
set yrange [0:150]
plot 'ext4.dat' using 2:xtic(1) title col, \
        '' using 3:xtic(1) title col, \
        '' using 4:xtic(1) title col, \
        '' using 5:xtic(1) title col, \
        '' using 6:xtic(1) title col
