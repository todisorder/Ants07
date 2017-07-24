reset
#set term qt
set term pngcairo truecolor enhanced size 1800,1800
set output "AAAAA.png"
ants = 10
range = 30.
set xrange[-range:range]
set yrange[-range:range]
plot for [i=1:ants] "AntPhase-".i.".txt" every 5 using 1:3:(.3) w circles  lc rgb "blue" fs transparent solid 0.02   noborder tit ''
#set term x11

reset
set term gif animate crop
set output "animate.gif"
iter = 3000
div = 3
n=iter/div #n frames

range = 30.
#ants = 1.
set xrange[-range:range]
set yrange[-range:range]
do for [i=1:n]{
#do for [j=1:ants]{
#plot  "AntPhase-".j.".txt" every ::i::i using 1:3:(.3) w circles  lc rgb "blue" fs transparent solid 0.5   noborder tit ''
#plot sin(x), cos(x) # assim ficam no mesmo...
#plot "Everybody.txt" every :::(2*i)::(2*i) using 1:2:(.3) w circles  lc rgb "blue" fs transparent solid 0.9   noborder tit ''
plot "Everybody.txt" every :::(div*i)::(div*i) using 1:2 w p tit ''
#
#plot sin(x+i*dt)/(1. + i/12.) w l lw 1.5 title sprintf("t=%i",i)
#}
}
set output
set term x11
