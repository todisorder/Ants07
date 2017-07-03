#File plot-png.sh
touch plots.plt
rm plots.plt
touch plots.plt;
touch ./Plots/foo
rm ./Plots/*
#mv ./Resultados/* . &&
echo "reset" >> plots.plt
echo "set parametric" >> plots.plt
echo "Generating gnuplot source code..."

echo "set term png font \"arial,12\"  size 840, 840
#unset xtics
#unset ytics
set title ''
set output \"./Plots/AntPos.png\"
plot \"AntPos.txt\"
set term png font \"arial,12\"  size  600, 600
set output \"./Plots/AntVel.png\"
plot \"AntVel.txt\"
set term png font \"arial,12\"  size  600, 600
set output \"./Plots/AntVelRadius.png\"
plot \"AntVelRadius.txt\"
set term png font \"arial,12\"  size  600, 600
set output \"./Plots/AntVelAngle.png\"
plot \"AntVelAngle.txt\"
set term png font \"arial,12\"  size  600, 600
set output \"./Plots/AntDistance.png\"
plot \"AntDistance.txt\"

#http://stackoverflow.com/questions/33774180/transparent-background-picture-and-the-color-of-certain-points
# De:::::
#   http://www.gnuplotting.org/code/zoom_plot.gnu
reset
set term png size 600,600
set palette gray negative
set output \"./Plots/Trail.png\"
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
splot \"Trail.txt\"  notitle w pm3d
#set term x11
set output \"./Plots/graph.png\"
#splot "popo/Trail.txt"  notitle w pm3d
set palette
plot \"./Plots/Trail.png\" binary filetype=png with rgbimage, \"AntPos.txt\"  using (10*(\$1)+300):(10*(\$2)+300) w l
set term x11
reset


" >> plots.plt

#echo "Done"
echo "set term x11" >> plots.plt
echo "Plotting..."
gnuplot plots.plt;
#echo "Done"
#echo "Building gifs..."
#convert -delay 2 -loop 0 ./Plots/U_1*.png ./Plots/myanimationU_1.gif;
#convert -delay 2 -loop 0 ./Plots/U_2*.png ./Plots/myanimationU_2.gif;
#convert -delay 2 -loop 0 ./Plots/U_food_c*.png ./Plots/myanimationU_food_conc.gif;
#convert -delay 2 -loop 0 ./Plots/U_food_p*.png ./Plots/myanimationU_food_phero.gif;
#echo "Done"

#echo "Building movs..."
#convert  -delay 5 ./Plots/U_1*.png ./Plots/myanimationU_1.mov
#convert  -delay 5 ./Plots/U_2*.png ./Plots/myanimationU_2.mov
#convert  -delay 5 ./Plots/U_food_p*.png ./Plots/myanimationU_food_phero.mov
#echo "Done"
echo "Copying files..."
#rm ./Resultados/*
#mv Pr* ./Resultados
#mv Vel_* ./Resultados
#rm ~/Dropbox/Formigas/*.mov
#cp ./Plots/*.mov ~/Dropbox/Formigas/
#cp ./Plots/*.mov ~/"Google Drive/"
#echo "Done"
echo "Finished!"
