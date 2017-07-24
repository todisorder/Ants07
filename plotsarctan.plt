reset
set term x11 1

fst = 20
ants = 30


plot for [i=fst:ants] "AntVel-".i.".txt"  using (($6)-($7)):(atan((($6)-($7))/(($6)+($7)) * tan(3.14159/4.))) w p pt 2 ps 1 lc rgb "red" notitle,\
            for [i=fst:ants] "AntVel-".i.".txt"  using (($6)-($7)):4 w p pt 6 ps 1 lc rgb "blue" notitle

#set term x11 2
#plot for [i=fst:ants]                    "AntVel-".i.".txt" using (($6)-($7)):(atan((($6)-($7))/(($6)+($7)) * tan(3.14159/4.))) w p pt 6 ps 1 lc rgb "red" notitle
#
#set term x11 3
#plot for [i=fst:ants] "AntVel-".i.".txt" using (($6)-($7)):4 w p pt 6 ps 1 lc rgb "blue" notitle