"""
Author: lc3311
Last updated: 10/02/16
"""

#! /usr/bin/env python
# -*- coding: utf-8 -*-

from IDAPICourseworkLibrary import *
from numpy import *

"""
FUNCTIONS FROM COURSEWORK 1
"""

# function to count occurences of two variables var1 and var2 with state1 and state2 in the data
def CountBoth(data, var1, var2, state1, state2):

        count_both = 0

        # loop through each pair of variable data
        for i,j in zip(data[:,var1],data[:,var2]):
                # increment the count if they are equal to the states
                if (i == state1 and j == state2):
                        count_both += 1
        return count_both

# function to calculate the joint probability table of two variables in the data set
def JPT(data, row, col, states):

        # initially fill a 2D array with 0s
        jPT = zeros((states[row], states[col]), float)

        # loop through each row data state
        for i in range(states[row]):
                # loop through each col data state
                for j in range(states[col]):
                        # enter the joint probability into jPT (count(row&col)/count(data))
                        jPT[i][j] = float(CountBoth(data,row,col,i,j))/len(data)

        return jPT

"""
COURSEWORK 2
"""

# function to calculate the mutual information score of a joint probability table
def MutualInformation(jpt):

        # Dep(A,B) = sum(P(ai&bj)log2((P(ai&bj)/(P(ai)P(bj)))

        mi = 0.0

        # loop through each row
        for i, row in enumerate(jpt):

                # sum each row (P(ai))
                r_total = sum(row)

                # avoid zero division
                if r_total == 0:
                        continue

                # loop through each column
                for j, cell in enumerate(row):

                        # avoid zero devision (if P(bj) = 0)
                        if sum(jpt.transpose()[j]) == 0:
                                continue

                        # don't increment if the cell is 0
                        if cell == 0:
                                continue

                        # increment the mutual information score
                        mi += cell * log2(cell / (r_total * sum(jpt.transpose()[j])))

        return mi
        
# function to construct a dependency matrix for all of the variables
def DependencyMatrix(data, variable_count, states):

        # initially fill a 2D array with 0s
        MIMatrix = zeros((variable_count,variable_count))

        # loop through the rows
        for i in range(0, variable_count):
                # loop through the columns
                for j in range(0, variable_count):

                        # compute an MI score for each pair of variables
                        jpt = JPT(data, i, j, states)
                        MIMatrix[i][j] = MutualInformation(jpt)

        return MIMatrix

# function to construct a dependency list for the variables, sorted by magnitude (largest first)
def DependencyList(dm):

        dl = []

        # loop through each row in the dependency matrix        
        for i in range(0, len(dm)):
                # avoid duplicates (get upper triangle matrix) and self-dependencies
                for j in range(i+1, len(dm[i])):
                        dl.append((dm[i][j], i, j))

        # sort the list from largest to smallest dependency
        dl = sorted(dl, reverse=True)

        return array(dl)

# function to construct the maximally weighted spanning tree
def SpanningTreeAlgorithm(dl, variable_count):

        spanning_tree = []

        # loop through each dependency
        for i in dl:
                # check if the variables are already connected in some way i.e. avoid loops
                if not AlreadyConnected(spanning_tree, i[1], i[2]):
                        spanning_tree.append(i)

        return array(spanning_tree)
        
# function to check if two nodes are already connected in some way
def AlreadyConnected(tree, node1, node2, path=[]):

        # for each connection in the tree
        for i in tree:

                # return true if the nodes are already connected
                if ((i[1] == node1 and i[2] == node2) or (i[2] == node1 and i[1] == node2)):
                        return True

                # recursively check if loops will be formed, by adding the current nodes to the path
                elif (i[1] == node1 and i[2] not in path):
                        if AlreadyConnected(tree, i[2], node2, path+[i[1]]):
                                return True
                elif (i[2] == node1 and i[1] not in path):
                        if AlreadyConnected(tree, i[1], node2, path+[i[2]]):
                                return True
                                

"""
MAIN FUNCTION
"""

# load the data
variable_count, root_count, states, data_count, datain = ReadFile("HepatitisC.txt")
data = array(datain)

# title
AppendString("IDAPIResults02.txt","Coursework Two Results by lc3311")
AppendString("IDAPIResults02.txt","")

# Q2
AppendString("IDAPIResults02.txt","The dependency matrix for the HepatitisC data set")
dm = DependencyMatrix(data, variable_count, states)
AppendArray("IDAPIResults02.txt", dm)

# Q3
AppendString("IDAPIResults02.txt","The sorted dependency list for the HepatitisC data set")
dl = DependencyList(dm)
AppendArray("IDAPIResults02.txt", dl)

# Q4
AppendString("IDAPIResults02.txt","The maximally weighted spanning tree for the HepatitisC data set")
st = SpanningTreeAlgorithm(dl, variable_count)
AppendArray("IDAPIResults02.txt", st)

