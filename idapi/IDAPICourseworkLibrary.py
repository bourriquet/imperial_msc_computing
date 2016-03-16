"""
PROVIDED FILE
"""

#! /usr/bin/env python                                                          
# -*- coding: utf-8 -*-                                                         

import Image
import glob, os
import numpy

# Function to read in data from a file in the format defined by Duncan          
def ReadFile(filename):

    f = open(filename);

    # the first line contains the number of variables. the function int converts a
    # string to an integer                                                      
    noVariables = int(f.readline())

    # the second line contains the number of root nodes                         
    noRoots = int(f.readline());

    # the third line contains the number of states of each variable             
    # this command extracts a list of integers. The split method breaks the line into a list of substrings                                                     
    # The map function applies a function (int) to a list (the substrings) to produce a list of integers.                                                      
    noStates = map(int,((f.readline()).split()))

    # the fourth line contains a single integer the number of data points       
    noDataPoints = int(f.readline())

    # all the subsequent lines of the file are data points. Each line is extracted as a list of integers which is                                              
    # appended to the list datain.                                              
    datain = []
    for x in range(noDataPoints):
        datain.append(map(int,((f.readline()).split())))

    f.close()
    return [noVariables, noRoots, noStates, noDataPoints, datain]
    
# Function to write an array to a results file                                                          
# the array is assumed to be either of proababilities of dependencies                                   
def AppendArray(filename, anArray):
    f = open(filename, 'a')
    for row in range(anArray.shape[0]):
        for col in range(anArray.shape[1]):
            f.write( '%6.3f ' % (anArray[row,col]))
        f.write('\n')
    f.write('\n\n')
    f.close()
    
#Function to write a list to a results file                                                             
def AppendList(filename, aList):
    f = open(filename, 'a')
    for row in range(aList.shape[0]):
        f.write( '%6.3f ' % (aList[row]))
    f.write('\n\n')
    f.close()

#Function to write a string to a results file                                                           
def AppendString(filename, aString):
    f = open(filename, 'a')
    f.write('%s\n' % (aString))
    f.close()
    
#                                                                                                       
# Image handline functions                                                                              
#                                                                                                       
# These functions turn images into data sets and vice versa                                             
#                                                                                                       
# Function to turn a principal component into an image and save it. The assumed resolution os 92 by 112 pixels.                                                                                                
# The component is a one dimensional representation of an image with each row concatinated              
def SaveEigenface(component,filename):
    theMax = max(component)
    theMin = min(component)
    scale = 255.0/(theMax-theMin)
    eigenfaceImage = map(int,(component - theMin) * scale)
    im = Image.new('L',(92,112))
    for y in range(im.size[1]):
        for x in range(im.size[0]):
            im.putpixel((x,y),eigenfaceImage[x+92*y])
    im.save(filename)
#                                                                                                       
# Function to convert images into a data format equivalent to the above format where each row of an array is                                                                                                   
# one image with rows concatinated into a single vector.                                                
# The images for this project are assumed to be all of resolution 92 by 112 pixels and are taken from   
# the current directory in .pgm format                                                                  
def ReadImages():
    datain = []
    for infile in glob.glob("*.pgm"):
        #filename, ext = os.path.splitext(infile)                                                       
        #print filename                                                                                 
        im = Image.open(infile)
        pixels = []
        for y in range(im.size[1]):
            for x in range(im.size[0]):
                pixels.append(im.getpixel((x,y)))
        datain.append(pixels)
    return datain

def ReadOneImage(filename):
    datain = []
    im = Image.open(filename)
    for y in range(im.size[1]):
        for x in range(im.size[0]):
            datain.append(im.getpixel((x,y)))
    return datain
    
#Functions to save and read an eigenface basis to a file                                                
#Needed for testing tasks 4.4 to 4.6 in the event that task 4.3 is unattempted or unsucessful           
def WriteEigenfaceBasis(pcBasis):
    f = open("EigenfaceBasis.txt", "w")
    for row in range(pcBasis.shape[0]):
        for col in range(pcBasis.shape[1]):
            f.write( '%12.10f ' % (pcBasis[row,col]))
        f.write('\n')
    f.write('\n\n')
    f.close()
def ReadEigenfaceBasis():
    f = open("PrincipalComponents.txt");
    datain = []
    for line in range(10):
        datain.append(map(float,(f.readline().split())))
    f.close()
    return numpy.array(datain)
