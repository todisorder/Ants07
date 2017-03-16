reset
set parametric
set term png font "arial,12"  size 240, 840
#unset xtics
#unset ytics
set title ''
set output "./Plots/AntPos.png"
plot "AntPos.txt"
set term png font "arial,12"  size  600, 600
set output "./Plots/AntVel.png"
plot "AntVel.txt"
set term png font "arial,12"  size  600, 600
set output "./Plots/AntVelRadius.png"
plot "AntVelRadius.txt"
set term png font "arial,12"  size  600, 600
set output "./Plots/AntVelAngle.png"
plot "AntVelAngle.txt"
set term png font "arial,12"  size  600, 600
set output "./Plots/AntDistance.png"
plot "AntDistance.txt"

#http://stackoverflow.com/questions/33774180/transparent-background-picture-and-the-color-of-certain-points
# De:::::
#   http://www.gnuplotting.org/code/zoom_plot.gnu
reset
set term png size 600,600
set palette gray negative
set output "./Plots/Trail.png"
set size ratio -1
set view map
set lmargin at screen 0
set rmargin at screen 1
set bmargin at screen 0
set tmargin at screen 1
#There shold be no key tics and border
unset key
#unset tics
#unset border
unset colorbox
splot "Trail.txt"  notitle w pm3d
#set term x11
set output "./Plots/graph.png"
#splot popo/Trail.txt  notitle w pm3d
set palette
plot "./Plots/Trail.png" binary filetype=png with rgbimage, "AntPos.txt"  using (10*($1)+300):(10*($2)+300) w l
set term x11
reset



set term x11
