"""
Author: lc3311
Last updated: 16/03/16

Issues:
- JPT2CPT() not giving correct output
"""

#! /usr/bin/env python
# -*- coding: utf-8 -*-

from IDAPICourseworkLibrary import *
from numpy import *

# function to compute the prior distribution of the variable root from the data
def Prior(data, root, states):

        # initially fill an array with 0s, length of array is number of states
        prior = zeros((states[root]), float)

        # must sum to 1, so increment proportionally
        inc = 1.0 / len(data)

        # for each row in data
        for i in data:
                # increment the probability of each state
                prior[i[root]] += inc
        return prior

# function to count occurrences of two variables var1 and var2 with state1 and state2 in the data
def CountBoth(data, var1, var2, state1, state2):

        count_both = 0

        # loop through each pair of variable data
        for i,j in zip(data[:,var1],data[:,var2]):
                # increment the count if they are equal to the states
                if (i == state1 and j == state2):
                        count_both += 1
        return count_both

# function to compute a CPT with parent node and child node from the data array
# it is assumed that the states are designated by consecutive integers starting with 0
def CPT(data, child, parent, states):

        # initially fill a 2D array with 0s
        cPT = zeros((states[child], states[parent]), float)

        # count the frequency of each parent state
        count = bincount(data[:,parent])

        # loop through each child state
        for i in range(states[child]):
                # loop through each parent state
                for j in range(states[parent]):
                        # enter the conditional probability into cPT (count(child&parent)/count(parent))
                        try:
                                cPT[i][j] = float(CountBoth(data,child,parent,i,j))/count[j]
                        except ZeroDivisionError:
                                cPT[i][j] = 0
        return cPT

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

# function to convert a joint probability table to a conditional probability table
# CURRENTLY INCORRECT - SUM(aJPT[:,i]) CHANGES OVER EACH ITERATION
def JPT2CPT(aJPT):

        # loop through every column in the JPT
        for i in range(aJPT.shape[1]):
                # divide each value in the column by the sum of the column
                for k in range(aJPT.shape[0]):
                        aJPT[k][i] /= sum(aJPT[:,i])
        return aJPT

# function to create a naive Bayesian network given the data, the number of variables and roots,
# and the states of the variables and roots
def CreateNetwork(data, variable_count, root_count, states):

        # create an empty network
        network = []

        # append the root prior probabilities
        for i in range(root_count):
                network.append(Prior(data,i,states))

        # append the node CPTs 
        for j in range(root_count, variable_count, 1):
                network.append(CPT(data,j,0,states))

        return array(network)
        
# function to query a naive Bayesian network, assuming only 1 root node
def Query(query, network):

        # initially fill a 2D array with 0s
        rootPdf = zeros((network[0].shape[0]), float)

        # multiply all the lambda evidence together - element-wise
        lam_ev = 1
        for i in range(len(query)):
                lam_ev *= network[i+1][query[i]]

        # matrix multiplication of the prior probability and the lambda evidence
        rootPdf = transpose(network[0]) * lam_ev

        # normalise the pdf
        norm = 1 / sum(rootPdf)
        rootPdf = norm * rootPdf

        return rootPdf
        
"""
MAIN FUNCTION
"""

# load the data
variable_count, root_count, states, data_count, datain = ReadFile("Neurones.txt")
data = array(datain)

# title
AppendString("IDAPIResults01.txt","Coursework One Results by lc3311")
AppendString("IDAPIResults01.txt","")

# Q1
AppendString("IDAPIResults01.txt","The prior probability of node 0")
prior = Prior(data, 0, states)
AppendList("IDAPIResults01.txt", prior)

# Q2
AppendString("IDAPIResults01.txt","The link matrix P(2|0) calculated from the data")
cpt = CPT(data, 2, 0, states)
AppendArray("IDAPIResults01.txt", cpt)

# Q3
AppendString("IDAPIResults01.txt","The joint probability matrix P(2&0) calculated from the data")
jpt = JPT(data, 2, 0, states)
AppendArray("IDAPIResults01.txt", jpt)

# Q4
AppendString("IDAPIResults01.txt","The link matrix P(2|0) calculated from P(2&0)")
j2c = JPT2CPT(jpt)
AppendArray("IDAPIResults01.txt",j2c)

# Q5
network = CreateNetwork(data, variable_count, root_count, states)
AppendString("IDAPIResults01.txt","The results of query [4,0,0,0,5] on the naive network")
pdf = Query([4,0,0,0,5], network)
AppendList("IDAPIResults01.txt",pdf)

AppendString("IDAPIResults01.txt","The results of query [6,5,2,5,5] on the naive network")
pdf = Query([6,5,2,5,5], network)
AppendList("IDAPIResults01.txt",pdf)
