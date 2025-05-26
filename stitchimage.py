import cv2

#The idea:
'''
SO Here's the idea:
A 360 degree image can be defined as an observer at the center of a spherical net
This spherical net encloses the viewer
The net contains the details of the image and is contourted to fit this
Then the user has some viewing field (a 16x9 screen)
The user can move along the net of this sphere in a 2d representation
The user can move from point 0 -> 360 when moving backwards(aka a cyclic shift/modulus bs shift)
'''
'''
What we need
A way to capture a full view (ensuring that this is true is more of mechanical thing)
A way to create the spherical net
An object - viewer that describes what the user is currently viewing
Translation Logic of that viewer object
'''

def grab_images(amount):
    #lets begin by assuming
    for i in range(amount):
        capture = input("ready? js click it pal")
        