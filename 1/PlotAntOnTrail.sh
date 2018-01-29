#http://stackoverflow.com/questions/33774180/transparent-background-picture-and-the-color-of-certain-points
# De:::::
#   http://www.gnuplotting.org/code/zoom_plot.gnu

reset


set term pngcairo truecolor enhanced size 4*800,800
set output "trail.png"

unset xtics
unset ytics
unset colorbox
set view map
set size ratio -1
#set samples 500,100
#set isosamples 100
set samples 50,10
set isosamples 100

set palette rgb 33,13,10

set yrange [-3:3]
set xrange [-15:15]

f(x)=exp(-abs(x))
g(x)=1.2+0.15*sin(x) +0.13*cos(2.2*x)

splot f(y)*1. w pm3d

set output

############################


reset
set term pngcairo truecolor enhanced size 600,1200
#set palette gray negative
set output "./Phero.png"
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
set xrange [-10:10]
splot "Phero.txt"  notitle w pm3d
#set term x11
set xrange [500:2500]
set yrange [200:600]
set term pngcairo truecolor enhanced size 1200,600
set output "./graph.png"
#splot "popo/Trail.txt"  notitle w pm3d
set lmargin
set rmargin
set bmargin
set tmargin
set palette
unset xtics
unset ytics
#set origin 0.4,0.3
#set size .4,.4
#plot "./Phero.png" binary filetype=png with rgbimage, "AntPos-1.txt"  using (10*($1)+300):(10*($2)+300) w lp lc rgbcolor "blue"
plot "./trail.png" binary filetype=png with rgbimage, "AntPos-1.txt"  using (33*($2)+1500):(400*($1)+405) w l lc rgbcolor "blue" lw 3
#ddx = 1.
#plot "./trail.png" binary filetype=png origin=(-0,-0) dx=ddx dy=ddx with rgbimage, "AntPos-1.txt" using (10.*($2)+700):(1.*($1)+125) w l lc rgbcolor "blue"
set term x11
reset


