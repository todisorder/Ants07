reset
set term x11


#plot "../pi4/Distances.txt" using (abs($2)) w histogram, "../pi3/Distances.txt" using (abs($2)) w histogram

plot "../pi4/Distances.txt" using (abs($2)) w lp, "../pi3/Distances.txt" using (abs($2)) w lp,  "../pi5/Distances.txt" using (abs($2)) w lp,  "../pi2p5/Distances.txt" using (abs($2)) w lp,  "../pi7/Distances.txt" using (abs($2)) w lp


set term x11
