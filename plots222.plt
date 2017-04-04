#do for [iter=1:30] {
#	do for [ant=0:9]
#    outfile = sprintf('aa/LOOK/Position%03.0f-%03.0f.png',iter,ant)
#    set output outfile
#    plot ant."T".iter.".txt"
#}

set term png
set xrange [-10:10]
set yrange [-10:10]

#do for [iter=1:600] {
#do for [ant=1:10]{
#outfile = sprintf('aa/LOOK/Ant%03.0f-Iter%03.0f.png',ant,iter)
#set output outfile
#plot "aa/AntPos-".ant.".txt" every ::iter::iter w lp
#}
#}

do for [iter=1:600] {
outfile = sprintf('../aa/LOOK/AllAnts-Iter%03.0f.png',iter)
set output outfile
plot for [i=1:10] "../aa/AntPos-".i.".txt" every ::iter::iter tit "" w lp
}

set term x11
reset
