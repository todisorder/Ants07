#do for [iter=1:30] {
#	do for [ant=0:9]
#    outfile = sprintf('aa/LOOK/Position%03.0f-%03.0f.png',iter,ant)
#    set output outfile
#    plot ant."T".iter.".txt"
#}

#set term png
#set xrange [-10:10]
#set yrange [-10:10]
#
#do for [iter=1:600] {
#do for [ant=1:10]{
#outfile = sprintf('aa/LOOK/Ant%03.0f-Iter%03.0f.png',ant,iter)
#set output outfile
#plot "aa/AntPos-".ant.".txt" every ::iter::iter w lp
#}
#}

reset

set term x11 1
a=1
#set xrange [0:*]
plot for [i=1:1] for [folder in "5 6 7"] "./".folder."/AntPos-".i.".txt" using 2:a w lp tit folder
set xrange [*:*]

set term x11 2
#set ylabel ""
plot for [i=1:1] for [folder in "5 6 7"] "./".folder."/AntVel-".i.".txt" using 3 w l tit folder




#set term x11 10
#dir="LastResult"
#a=1
#plot for [i=1:1] "./".dir."/AntPos-".i.".txt" using a w l, "./pi5/AntPos-".i.".txt" using a w l, "./pi2-13/AntPos-".i.".txt" using a w l, "./pi7/AntPos-".i.".txt" using a w l, "./pi9s2/AntPos-".i.".txt" using a w l
#
#set term x11 2
#
#b=3
#plot for [i=1:1] "./pi4/AntVel-".i.".txt" using b w l, "./pi5/AntVel-".i.".txt" using b w l, "./pi2-13/AntVel-".i.".txt" using b w l, "./pi7/AntVel-".i.".txt" using b w l, "./pi9s2/AntVel-".i.".txt" using b w l
#
#set term x11 3
#
#plot for [i=1:1] "./pi4/AntVel-".i.".txt" using 1:2 w lp, "./pi5/AntVel-".i.".txt" using 1:2 w lp, "./pi2-13/AntVel-".i.".txt" using 1:2 w lp, "./pi7/AntVel-".i.".txt" using 1:2 w lp, "./pi9s2/AntVel-".i.".txt" using 1:2 w lp
#
#set term x11 4
#
#set yrange [-1:30]
#plot for [i=1:1] "./pi4/AntPos-".i.".txt" using 1:2 w l, "./pi5/AntPos-".i.".txt" using 1:2 w l, "./pi2-13/AntPos-".i.".txt" using 1:2 w l, "./pi7/AntPos-".i.".txt" using 1:2 w l, "./pi9s2/AntPos-".i.".txt" using 1:2 w l
#

