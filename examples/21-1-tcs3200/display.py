#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os.path
sys.path.insert(1,os.path.normpath(sys.path[0]+"../../python"))

import premain
import argparse
import pickle
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
# import matplotlib.colors
import math

#  Parse command line
#
parser = argparse.ArgumentParser()
group = parser.add_mutually_exclusive_group()
parser.add_argument('-a', dest='average', action='store_true', help="Add average points" )
parser.add_argument('-n', dest='normalize', action='store_true', help="Noralize data in 0..255" )
group.add_argument('-s', dest='sph', action='store_true', help="Spherical view" )
group.add_argument('-c', dest='sph', action='store_false', help="Cartesian view" )
parser.add_argument('--sphere', action='store_true', help="Display sphere" )
parser.add_argument('files', type=argparse.FileType('r'), nargs='+')
args = parser.parse_args()


#  Load data from files
#
data = dict()
for f in args.files:
    #
    # A data file is a dict() whose keys are 6 digits coding R-G-B relative
    # intensities in percentages, and values are the number of occurences.
    #
    data[f.name] = pickle.load(f)
    f.close()


#  Build sets of points
#  Points coordinates are in the range 0..255
#
points = dict()
for tag in data:
    pts=list()
    for key in data[tag]:
        red   = int(key[0:2],16)
        green = int(key[2:4],16)
        blue  = int(key[4:6],16)
        n = data[tag][key]
        pts.append((red,green,blue,n))
    points[tag]=pts
    cout("Loaded %d points from %s\n" % (len(pts), tag))


#  Compute weighted average of each set of points
#
avgs = dict()
rmin = 255
gmin = 255
bmin = 255
rmax = 0
gmax = 0
bmax = 0
for tag in points:
    reds, greens, blues, ns = zip(*points[tag])
    r = int(round(np.average( reds,   weights=ns )))
    g = int(round(np.average( greens, weights=ns )))
    b = int(round(np.average( blues,  weights=ns )))
    avgs[tag]=(r,g,b)

    rmin = min( rmin, np.min( reds ))
    gmin = min( gmin, np.min( greens ))
    bmin = min( bmin, np.min( blues ))

    rmax = max( rmax, np.max( reds ))
    gmax = max( gmax, np.max( greens ))
    bmax = max( bmax, np.max( blues ))


cout("Red:   min=%d max=%d\n" % (rmin, rmax))
cout("Green: min=%d max=%d\n" % (gmin, gmax))
cout("Blue:  min=%d max=%d\n" % (bmin, bmax))


#  Normalize coordinates in the range [0..255]
#
if args.normalize:
    for tag in points:
        pts = list()
        for r,g,b,n in points[tag]:
            r = 255*(r-rmin)/(rmax-rmin)
            g = 255*(g-gmin)/(gmax-gmin)
            b = 255*(b-bmin)/(bmax-bmin)
            pts.append((r,g,b,n))
        points[tag]=pts

        r,g,b=avgs[tag]
        r = 255*(r-rmin)/(rmax-rmin)
        g = 255*(g-gmin)/(gmax-gmin)
        b = 255*(b-bmin)/(bmax-bmin)
        avgs[tag]=(r,g,b)
    rmin = 0
    rmax = 255
    gmin = 0
    gmax = 255
    bmin = 0
    bmax = 255


cout("Average weighted values:\n")
for tag in avgs:
    r,g,b = avgs[tag]
    cout("  %d %d %d  %s\n" % (r,g,b,tag))


#  Color for a set of points is chosen from the average values of the set and
#  the extreme values of all the sets
#
colors = dict()
avgcolors = dict()
for tag in points:
    r,g,b = avgs[tag]
    r = 64 + 192 * (r-rmin) / (rmax-rmin)
    g = 64 + 192 * (g-gmin) / (gmax-gmin)
    b = 64 + 192 * (b-bmin) / (bmax-bmin)
    colors[tag]='#%02x%02x%02x' % (r,g,b)
    avgcolors[tag]='#%02x%02x%02x' % (r/2,g/2,b/2)

#print colors
#sys.exit(0)


#  Place points on a rho=1 sphere
#
if args.sph:
    for tag in points:
        pts0=points[tag]
        pts1=list()
        for (x,y,z,n) in pts0:
            #
            # Convert x,y,z -> r,theta,phi
            #
            rho = np.sqrt(x*x + y*y + z*z)
            phi = np.arccos(1.0*z/rho)
            if x != 0:
                theta = np.arctan(1.0*y/x)
            else:
                theta = np.pi/2

            # Back to cartesian on a rho=1 sphere
            #
            x = np.sin(phi) * np.cos(theta)
            y = np.sin(phi) * np.sin(theta)
            z = np.cos(phi)

            #
            # sin(acos(x)) = sqrt(1 - x*x)
            # sin(atan(x)) = x / sqrt(1 + x*x)
            # cos(atan(x)) = 1 / sqrt(1 + x*x)
            #

            pts1.append((x,y,z,n))
        points[tag]=pts1


#  Build figure
#
fig = plt.figure()
if args.sph:
    ax = fig.add_subplot(111, projection='3d')
else:
    ax = fig.add_subplot(111, projection='3d', xlim=(0,255), ylim=(0,255), zlim=(0,255))

ax.set_xlabel('Red')
ax.set_ylabel('Green')
ax.set_zlabel('Blue')
fig.set_tight_layout(True)


#  Create list of coordinates for each type of point
#
for tag in points:
    c=colors[tag]
    xs, ys, zs, ns = zip(*points[tag])
    ax.scatter(xs, ys, zs, s=[n*5 for n in ns], c=c)

    #  Add a weighted average for each set of points
    #  Coodinates may have been transformed to place points on sphere
    #
    if args.average:
        axs = list()
        ays = list()
        azs = list()
        ans = list()
        axs.append( np.average( xs, weights=ns ) )
        ays.append( np.average( ys, weights=ns ) )
        azs.append( np.average( zs, weights=ns ) )
        ans.append( np.sum(ns) )
        ax.scatter( axs, ays, azs, s=ans, c=avgcolors[tag], alpha=1.0 )


#  Draw the sphere
#
if args.sphere:
    plt.axis('off')
    u = np.linspace(0, np.pi/2)
    v = np.linspace(0, np.pi/2)
    x = np.outer(np.cos(u), np.sin(v))
    y = np.outer(np.sin(u), np.sin(v))
    z = np.outer(np.ones(np.size(u)), np.cos(v))
    ax.plot_wireframe(x, y, z, rstride=1, cstride=1, color='k', alpha=0.1)

    ax.set_xlim(0,1)
    ax.set_ylim(0,1)
    ax.set_zlim(0,1)


if 0:
    import matplotlib.animation as animation

    def update ( n ):
        print 'Update', n

    # ani = animation.FuncAnimation(fig,
    #                               update, 25, fargs=(),
    #                               interval=50, blit=True)
    line_ani = animation.TimedAnimation( fig, 50 )

plt.show()
