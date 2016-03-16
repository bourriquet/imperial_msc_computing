"""
Author: lc3311
Last updated: 02/03/16
"""

from IDAPICourseworkLibrary import *
from numpy import *

# function to compute the mean vector of a data matrix
def Mean(data):
	real_data = data.astype(float)
	mean = []

	# compute the mean of each column - avoid zero division
	if len(real_data):
		mean = real_data.sum(0)/len(real_data)

	return array(mean)

# function to compute the covariance matrix of a data matrix
def Covariance(data):
	real_data = data.astype(float)
	var_count = data.shape[1]
	covar = zeros((var_count, var_count), float)

	m = Mean(data)
	X = real_data - m
	X_T = transpose(X)

	# S = (1/N)(X_T)(X)
	# compute the covariance of each variable - avoid zero division
	if (len(real_data) > 0):
		covar = dot(X_T, X) / len(real_data)

	return covar

# function to create .jpg files of the principal components
def CreateEigenfaceFiles(basis):

	# save a file for each component
	for i in range(0, len(basis)):
		filename = "PrincipalComponent" + str(i) + ".jpg"
		SaveEigenface(basis[i], filename)

# function to read an image file and project it onto the principal components
def ProjectFace(basis, m, image):
	magnitudes = []

	image_data = ReadOneImage(image)

	# find the component magnitudes
	magnitudes = dot((image_data - m), transpose(basis))
	
	return array(magnitudes)

# function to save .jpg files of image reconstructions from component magnitudes
def CreatePartialReconstructions(a_basis, a_mean, component_mags):
	
	# mean face
	SaveEigenface(a_mean, "Reconstructed0.jpg")

	# iteratively add components to the mean face
	for i in range(0, len(component_mags)):
		recon = dot(transpose(a_basis[0:i]), component_mags[0:i]) + a_mean
		SaveEigenface(recon, "Reconstructed" + str(i+1) + ".jpg")

# function to perform PCA on a data set
def PrincipalComponents(data):
	orthoPhi = []
	
	m = Mean(data)
	cov = Covariance(data)
	
	X = data - m
	X_T = transpose(X)
	X_X_T = dot(X, X_T)

	# compute the eigenvalues and eigenvectors
	val, vec = linalg.eig(X_X_T)
	vec = dot(X_T, vec)

	# normalise the eigenvectors
	for i in range(0, vec.shape[1]):
		vec[:,i] /= linalg.norm(vec[:,i])

	# sort eigenvalues ascending to descending
	y = zip(val, transpose(vec))
	list.sort(y, reverse = True)

	orthoPhi = zip(*y)[1]

	return array(orthoPhi)

# load the data
variable_count, root_count, states, data_count, datain = ReadFile("HepatitisC.txt")
data = array(datain)

# title
AppendString("IDAPIResults04.txt","Coursework Four Results by lc3311")
AppendString("IDAPIResults04.txt","") #blank line

# Q1
AppendString("IDAPIResults04.txt","The mean vector of the HepatitisC data set")
m = Mean(data)
AppendList("IDAPIResults04.txt",m)

# Q2
AppendString("IDAPIResults04.txt","The covariance matrix of the HepatitisC data set")
c = Covariance(data)
AppendArray("IDAPIResults04.txt",c)

# Q3
basis = array(ReadEigenfaceBasis())
CreateEigenfaceFiles(basis)

# Q4
mean_face = array(ReadOneImage("MeanImage.jpg"))
AppendString("IDAPIResults04.txt","The component magnitudes for 'c.pgm'")
mags = ProjectFace(basis, mean_face, "c.pgm")
AppendList("IDAPIResults04.txt",mags)

# Q5
CreatePartialReconstructions(basis, mean_face, mags)

# Q6
image_data = array(ReadImages())
new_mean = Mean(image_data)
new_basis = PrincipalComponents(image_data)
CreateEigenfaceFiles(new_basis)
new_mags = ProjectFace(new_basis, new_mean, "c.pgm")

CreatePartialReconstructions(new_basis, new_mean, new_mags)
PrincipalComponents(image_data)
