reset
set term png size 800,600
set size ratio -1
set view map
set lmargin at screen 0
set rmargin at screen 1
set bmargin at screen 0
set tmargin at screen 1
#There shold be no key tics and border
unset key
set output "roda2.png"
set xrange [0:6]
plot for [i=1:100] "AntPos-".i.".txt" every ::00::1000 tit "" w l
set term wxt
