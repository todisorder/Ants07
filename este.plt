set term png




reset
set xrange [-16:16]
set yrange [-16:16]


do for [iter=1:1000:10] {
	do for [ant=0:2] {
#    outfile = sprintf('PositionAnt%03.0f-iter%03.0f.png',ant,iter)
#    set output outfile
#    plot "AntPos-".(ant+1).".txt" every ::iter-30::iter w l
}
    outfile = sprintf('AllAnts-iter%03.0f.png',iter)
    set output outfile
    plot for [ant=0:50] "AntPos-".(ant+1).".txt" every ::iter-30::iter tit"" w l
}



set term x11
reset