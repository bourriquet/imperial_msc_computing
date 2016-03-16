"""
Author: lc3311
Last updated: 18/02/16
"""

#! /usr/bin/env python
# -*- coding: utf-8 -*-

from IDAPICourseworkLibrary import *
from numpy import *

"""
FUNCTIONS FROM COURSEWORK 1
"""

# function to compute the prior distribution of the variable root from the data
def Prior(data, root, states):
        prior = zeros((states[root]), float)

        inc = 1.0 / len(data)

        for i in data:
                prior[i[root]] += inc

        return prior

# function to count occurences of two variables var1 and var2 with state1 and state2 in the data
def CountBoth(data, var1, var2, state1, state2):
        count_both = 0

        for i,j in zip(data[:,var1],data[:,var2]):
                if (i == state1 and j == state2):
                        count_both += 1

        return count_both

# function to compute the CPT of a child and parent from the data set
def CPT(data, child, parent, states):
        cPT = zeros((states[child], states[parent]), float)

        count = bincount(data[:,parent])

        for i in range(states[child]):
                for j in range(states[parent]):
                        try:
                                cPT[i][j] = float(CountBoth(data,child,parent,i,j))/count[j]
                        except ZeroDivisionError:
                                cPT[i][j] = 0
        return cPT
        
"""
COURSEWORK 3
"""

# function to compute a CPT of a child with multiple parents from the data set
# it is assumed that the states are designated by consecutive integers starting with 0
def CPT_2(data, child, parent1, parent2, states):

        # initially fill a 3D array with zeros
        cPT = zeros([states[child], states[parent1], states[parent2]], float)

        # increment occurrences of child and both parents in the CPT
        for i in data:
                cPT[i[child]][i[parent1]][i[parent2]] += 1

        # divide each element by the number of occurrences of both parents
        for i in range(0, states[parent1]):
                for j in range(0, states[parent2]):
                        sum = 0.0
                        for k in range(0, states[child]):
                                sum += cPT[k][i][j]
                        for k in range(0, states[child]):
                                if not sum == 0:
                                        cPT[k][i][j] /= sum
        return cPT

# Definition of a Bayesian Network - Neurones
def ExampleBayesianNetwork(data, states):
        arcList = [[0],[1],[2,0],[3,2,1],[4,3],[5,3]]
        cpt0 = Prior(data, 0, states)
        cpt1 = Prior(data, 1, states)
        cpt2 = CPT(data, 2, 0, states)
        cpt3 = CPT_2(data, 3, 2, 1, states)
        cpt4 = CPT(data, 4, 3, states)
        cpt5 = CPT(data, 5, 3, states)
        cptList = [cpt0, cpt1, cpt2, cpt3, cpt4, cpt5]
        return arcList, cptList


# Definition of a Bayesian Network - HepatitisC
def HepatitisBayesianNetwork(data, states):
        cpt0 = Prior(data, 0, states)
        cpt1 = Prior(data, 1, states)
        cpt2 = CPT(data, 2, 0, states)
        cpt3 = CPT(data, 3, 4, states)
        cpt4 = CPT(data, 4, 1, states)
        cpt5 = CPT(data, 5, 4, states)
        cpt6 = CPT(data, 6, 1, states)
        cpt7 = CPT_2(data, 7, 0, 1, states)
        cpt8 = CPT(data, 8, 7, states)

        arcList = [[0],[1],[2,0],[3,4],[4,1],[5,4],[6,1],[7,0,1],[8,7]]
        cptList = [cpt0,cpt1,cpt2,cpt3,cpt4,cpt5,cpt6,cpt7,cpt8]

        return arcList, cptList

# Function to calculate the MDL size of a Bayesian Network
def MDLSize(arcList, cptList, data_count, states):

        # Size(Bn|Ds) = |Bn|(log2N)/2

        mdlSize = 0.0

        # how many parameters do we need to reconstruct the network?
        # for each variable, take 1 away then multiply by the number of states of each parent

        # over each variable
        for i in range(0, len(states)):
                # probabilities add to 1 so need m-1 parameters
                param = states[i] - 1
                # multiply by the number of states of the parents
                for j in arcList[i][1:]:
                        param *= states[j]
                mdlSize += param

        # compute the size
        mdlSize *= log2(data_count)/2

        return mdlSize
        
# Function to calculate the joint probability of a single data point in a Network
def JointProbability(dataPoint, arcList, cptList):
        jP = 1.0

        # over each data point
        for i in range(0, len(dataPoint)):

                # get the corresponding table and arc           
                table = cptList[i]
                arc = arcList[i]

                # for multiplication
                val = 1.0

                # different CPT dimensions for each child/parent config
                # if the variable is a root
                if len(arc) == 1:
                        val = table[dataPoint[i]]
                # if the variable has one parent
                elif len(arc) == 2:
                        val = table[dataPoint[i]][dataPoint[arc[1]]]
                # if the variable has two parents
                elif len(arc) == 3:
                        val = table[dataPoint[i]][dataPoint[arc[1]]][dataPoint[arc[2]]]

                # ignore if the value is 0
                if (val > 0.0):
                        jP *= val

        return jP
        
# Function to calculate the MDLAccuracy from a data set
def MDLAccuracy(data, arcList, cptList):
        mdlAccuracy = 0.0

        # log2P(Ds|Bn) = Sum(log2P(Bn))

        # for each data point, compute the JP
        for i in data:
                mdlAccuracy += log2(JointProbability(i,arcList,cptList))

        return mdlAccuracy

# Function to calculate the MDLScore from a data set
def MDLScore(data, data_count, states, arcList, cptList):

        modelsize = MDLSize(arcList, cptList, data_count, states)
        modelaccuracy = MDLAccuracy(data, arcList, cptList)

        return modelsize - modelaccuracy

# Function to calculate the minimum MDLScore of the data set by removing one arc from the network
def MinMDL(data, data_count, stats, arcList, cptList, score):

        # current minimum is the score from the current network
        minimum = score

        # check every arc in the list
        for arc in arcList:
                copy = cptList[:]

                # only want to remove arcs of a variable if they aren't root nodes
                for i in arc[1:]:

                        # remove the arc
                        arc.remove(i)

                        # create a temporary CPT and remove the CPT of the child from the list
                        temp = None
                        copy.pop(arc[0])        # copy.remove(arc[0]) throws an error

                        # recalculate the CPT for the child
                        if len(arc) == 1:
                                temp = Prior(data, arc[0], states)
                        elif len(arc) == 2:
                                temp = CPT(data, arc[0], arc[1], states)

                        # insert the recalculated CPT back into the list
                        copy.insert(arc[0], temp)

                        # calculate a new MDLScore
                        new_score = MDLScore(data, data_count, states, arcList, copy)
                        
                        # if this score is a minimum, update the minimum variable
                        if new_score < minimum:
                                minimum = new_score

                        # put back the original arc
                        arc.append(i)

        return minimum
        
"""
MAIN FUNCTION
"""

# load the data
variable_count, root_count, states, data_count, datain = ReadFile("HepatitisC.txt")
data = array(datain)

# title
AppendString("IDAPIResults03.txt","Coursework Three Results by lc3311")
AppendString("IDAPIResults03.txt","")

# Q3
AppendString("IDAPIResults03.txt","The MDL size of the network for the Hepatitis C data set")
arc,cpt = HepatitisBayesianNetwork(data,states)
mdlsize = MDLSize(arc,cpt,data_count,states)
AppendString("IDAPIResults03.txt", str(mdlsize))
AppendString("IDAPIResults03.txt","")

# Q5
AppendString("IDAPIResults03.txt","The MDL accuracy of the network for the Hepatitis C data set")
mdlaccuracy = MDLAccuracy(data,arc,cpt)
AppendString("IDAPIResults03.txt", str(mdlaccuracy))
AppendString("IDAPIResults03.txt","")

AppendString("IDAPIResults03.txt","The MDL score of the network for the Hepatitis C data set")
mdlscore = MDLScore(data, data_count, states, arc, cpt)
AppendString("IDAPIResults03.txt", str(mdlscore))
AppendString("IDAPIResults03.txt","")

# Q6
AppendString("IDAPIResults03.txt","The minimum MDL score of the network by removing one arc")
minmdl = MinMDL(data, data_count, states, arc, cpt, mdlscore)
AppendString("IDAPIResults03.txt",str(minmdl))

