# ES100
# Adam Reid
# Python code used to establish LEN and THETA parameters

# Designed for use with blur
# Run blur after running this file to calculate PSF

# Needed parameters: Distance to vehicle (x,y,z), camera azimuth, camera elevation, shutter speed,  vehicle speed,
# camera focal length

import numpy as np
import math


### DEFINITIONS ###

#0 Calculate orthonormal vector "v" and its plane (elevation, azimuth)
def ortho_v(elevation, azimuth):
    # Degrees to radians
    phi = math.radians(elevation)
    theta = math.radians(azimuth)

    # Get coordinates
    vx = math.cos(theta) * math.sin(phi)
    vy = math.cos(theta) * math.cos(phi)
    vz = math.sin(phi)

    return np.array([vx, vy, vz])

#1 Calculate vector "yi" using distance(x,y,z)
def initial_y(distance_back, distance_along, height):
    return np.array([distance_back, distance_along, height])

#2 Calculate vector "y" using distance traveled (shutter, car speeds)
def array_y(exposure_time, vehicle_speed):
    return np.array([0, exposure_time * vehicle_speed, 0])

#3 Calculate vector "yf"
def final_y(array_y, initial_y):
    return np.array([initial_y[0], initial_y[1] + array_y[1], initial_y[2]])

#4 Calculate initial, final image distances (from lens to sensor)
def image_distance(focal_length, initial_y, final_y):
    initial_yl = math.sqrt(initial_y[0]**2 + initial_y[1]**2 + initial_y[2]**2)
    final_yl = math.sqrt(final_y[0]**2 + final_y[1]**2 + final_y[2]**2)
    initial_image = (initial_yl * focal_length) / (initial_yl - focal_length)
    final_image = (final_yl * focal_length) / (final_yl - focal_length)
    return initial_yl, final_yl, initial_image, final_image

#5 Calculate magnification
def magnification(initial_yl, final_yl, initial_image, final_image):
    initial_mag = initial_image / initial_yl
    final_mag = final_image / final_yl
    return initial_mag, final_mag

#6 Find the "height angle"
def height_angle(initial_y, initial_yl, final_yl):
    initial_ha = np.arccos(initial_y[2] / initial_yl)
    final_ha = np.arccos(initial_y[2] / final_yl)
    return initial_ha, final_ha

#7 Find the "height prime" vector
def height_prime(elevation, initial_ha, final_ha, initial_yl, final_yl):
    ilength_hp = np.cos(math.radians(elevation) + initial_ha) * initial_yl
    flength_hp = np.cos(math.radians(elevation) + final_ha) * final_yl
    initial_hp = [ilength_hp * np.sin(math.radians(elevation)), ilength_hp * np.cos(math.radians(elevation))]
    final_hp = [flength_hp * np.sin(math.radians(elevation)), flength_hp * np.sin(math.radians(elevation))]
    return initial_hp, final_hp

#8 Establish vectors "vi; vf"
def projection_v(initial_hp, final_hp, initial_mag, final_mag, array_y):
    initial_hpm = [initial_hp[0] * initial_mag, initial_hp[1] * initial_mag]
    final_hpm = [final_hp[0] * final_mag, final_hp[1] * final_mag]
    initial_v = [initial_hpm[0], 0, initial_hpm[1]]
    final_v = [final_hpm[0], array_y[1] * ((initial_mag + final_mag) / 2), final_hpm[1]]
    return initial_v, final_v

#9 Calculate vector "u"
def vector_u(initial_v, final_v):
    return np.subtract(initial_v, final_v)

#10 Calculate length of u
def length_u(vector_u):
    return np.sqrt(vector_u[0]**2 + vector_u[1]**2 + vector_u[2]**2)

#11 Find vector u as basis of V
def basis_u(vector_u, ortho_v, initial_y, initial_mag):
    initial_ym = initial_y * initial_mag
    ux = [1 * vector_u[0], 0, (-1) * ((ortho_v[0] * initial_ym[0]) / ortho_v[2]) * vector_u[0]]
    uy = [0, 1 * vector_u[1], (-1) * ((ortho_v[1] * initial_ym[1]) / ortho_v[2]) * vector_u[1]]
    return ux, uy

#12 Calculate theta from u
def theta_u(ux, uy):
    return math.degrees(np.arctan(np.sqrt((ux[0]**2 + ux[1]**2 + ux[2]**2) / (uy[0]**2 + uy[1]**2 + uy[2]**2))))


### INPUTS ###

distanceBack = 2 # int(input("Camera distance from center of lane (meters): "))
distanceAlong = 5 # int(input("Camera distance from vehicle along road (meters): "))
height = 1 # int(input("Camera height (meters): "))

elevationAngle = 343 # int(input("Elevation angle (degrees): "))
azimuthAngle = 21 # int(input("Azimuth angle (degrees): "))

focalLength = 50 * (1/1000) # int(input("Camera focal length (mm): ")) * (1/1000) # Convert to meters
exposureTime = 10 * (1/1000) # int(input("Exposure time (ms): ")) * (1/1000) # Convert to seconds
vehicleSpeed = 35 * (1609.344) * (1/3600) #(int(input("Vehicle speed (mph): "))) * (1609.344) * (1/3600) # Convert to m/s


### CALCULATIONS ###

#0
orthoV = ortho_v(elevationAngle, azimuthAngle)

#1
initialY = initial_y(distanceBack, distanceAlong, height)

#2
arrayY = array_y(exposureTime, vehicleSpeed)

#3
finalY = final_y(initialY, arrayY)

#4
initialYl, finalYl, initialImage, finalImage = image_distance(focalLength, initialY, finalY)

#5
initialMag, finalMag = magnification(initialYl, finalYl, initialImage, finalImage)

#6
initialHa, finalHa = height_angle(initialY, initialYl, finalYl)

#7
initialHp, finalHp = height_prime(elevationAngle, initialHa, finalHa, initialYl, finalYl)

#8
initialV, finalV = projection_v(initialHp, finalHp, initialMag, finalMag, arrayY)

#9
vectorU = vector_u(initialV, finalV)

#10
lengthU = length_u(vectorU)

#11
basisUX, basisUY = basis_u(vectorU, orthoV, initialY, initialMag)

#12
thetaU = theta_u(basisUX, basisUY)

# Length
print(lengthU)
# Theta
print(thetaU)
