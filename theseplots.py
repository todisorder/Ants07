from __future__ import division
from colorsys import hsv_to_rgb
from mpl_toolkits.mplot3d import Axes3D
from random import random, choice
import matplotlib.pyplot as plt 
import numpy as np 

#https://pastebin.com/E9g8NwP1


# vectorfield - main formula
def vectorfield(x, y, z, params):

	b,sc,dt,ax,a1,a2,a3,f,p,q,r,s,v,w,u = params		
	xyz = [x,y,z]

	i = q * np.cos(xyz[a3] / (xyz[a2] + p * (xyz[a1] + q) * np.pi + z) * np.pi)
	j = r * np.sin(xyz[a2] * np.cos(np.pi * x) / (xyz[a2] + r * -(x + s)) * np.pi + x)
	k = w * np.sin(xyz[a1] / (xyz[a2] + v / (xyz[a3] - xyz[a2] + w)) * np.pi + xyz[a1])

	return i, j, k	




def plot(params):

	b,sc,dt,ax,a1,a2,a3,f,p,q,r,s,v,w,u = params

	for pts in range(sc*2):

		hue = random()
		# set up initial coordinates
		x = f * np.cos((pts/sc)*np.pi)
		y = f * np.sin((pts/sc)*np.pi)
		z = f * np.sin((pts/sc)*np.pi)

		xl, yl, zl = [], [], []

		# length of curves
		for t in np.arange(0, 2000, dt):

			i, j, k = vectorfield(x, y, z, params)
			x = x + (i * dt)
			y = y + (j * dt)
			z = z + (k * dt)
			xl.append(x)
			yl.append(y)
			zl.append(z)
			
		# show curves
		ax.plot(xl, yl, zl, '-', zdir='z', alpha=0.4, color = hsv_to_rgb(hue, 1, 1))

	ax.set_xlim((-b,b))
	ax.set_ylim((-b,b))
	ax.set_zlim((-b,b))




def log(params, log=False, savepic=True, show=False):
	
	b,sc,dt,ax,a1,a2,a3,f,p,q,r,s,v,w,u = params	
	n_frames = 1
	zoom_depth = 3.
	unique_id = str(random()*3) + '_'		

	if log:
		
		# create log file of all parameters
		set_wr = open('FS%s log.txt' % unique_id, 'w+')
		set_wr.write('ID: FS %s' % unique_id + '\n')
		set_wr.write('b = %s (initial x,y,z lim)' % str(b) + '\n')
		set_wr.write('u = %s' % str(u) + '\n')
		set_wr.write('p = %s' % str(p) + '\n')
		set_wr.write('q = %s' % str(q) + '\n')
		set_wr.write('r = %s' % str(r) + '\n')
		set_wr.write('s = %s' % str(s) + '\n')
		set_wr.write('v = %s' % str(v) + '\n')
		set_wr.write('w = %s' % str(w) + '\n')
		set_wr.write('f = %s' % str(f) + '\n')
		set_wr.write('for a1,a2,a3: 0 = x, 1 = y, 2 = z' + '\n')
		set_wr.write('a1 = %s' % str(a1) + '\n')
		set_wr.write('a1 = %s' % str(a2) + '\n')

		set_wr.write('a1 = %s' % str(a3) + '\n')
		set_wr.write('number of drawn lines: %.0f' % sc)
		set_wr.close()

	if savepic:
	
		for frames in range(n_frames):

			# zooms from b to b-zoom_depth and back

			fstep = (frames/(1.*n_frames)) * np.pi
			fsin = zoom_depth * (np.sin(fstep))**2
			lim = b - fsin
			
			ax.set_xlim((-lim,lim))
			ax.set_ylim((-lim,lim))
			ax.set_zlim((-lim,lim))

			ax.view_init(-90+frames,30+frames)
			remaining_time = (2880 - (8 * frames))/60.
			
			fname = 'FS' + unique_id + str(frames) + '.png'
			print "Saving: %s" % fname
			plt.savefig(fname, format='png',dpi=300, bbox_inches='tight', pad_inches=0)
	
	if show:
		plt.show()




if __name__ == '__main__':
	
	from sys import argv

	b = 3.5			# axis limits
	sc = 20			# number of lines	
	dt = np.pi/32		# time step
	
	if (len(argv) == 1):
		numpics = 1	
	else:
		numpics = int(argv[1])

	print "Generating %d pictures" %numpics
	for images in range(numpics):
		print "Image: %d" % (images+1)
		
		# set up figures and axes
		fig = plt.figure(figsize=(12, 12))
		ax = fig.add_subplot(111, projection = '3d', aspect='equal')
		ax.axis('off')
		ax.set_axis_bgcolor((0,  0,  0))
		ax.view_init(-90, 30)			# viewing angle
	
		# random vars
		[a1, a2, a3] = [choice(range(3)) for _ in range(3)]	# indices
		f = random() * 4					# initial radius
		u = random() * 5					# scalar size	
		p = (-(u/2) + (u * random())) * np.pi			# random scalars
		[q,r,s,v,w] = [-(u/2)+(u*random()) for _ in range(5)]	# random scalars
		
		params = [b,sc,dt,ax,a1,a2,a3,f,p,q,r,s,v,w,u]
	
		print "Calculating lines..."
		plot(params)
		log(params)