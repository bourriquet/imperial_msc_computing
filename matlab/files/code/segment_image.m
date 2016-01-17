function [ clusterimage, clustermap, clustermeans ] = segment_image(origimage,numclusters)
% SEGMENT_IMAGE - takes data of an image and clusters into small number of regions of similar colour
%
% Use:
% [ clusterimage, clustermap, clustermeans ] = segment_image(origimage,numclusters)
% Takes:
% origimage - H x W x 3 image data matrix (0-1 val per pixel)
% numclusters - integer number of different colours in final image
% Returns:
% clusterimage - H x W x 3 image data of clustered image (0-1 val per pixel)
% clustermap - H x W matrix of cluster ids
% clustermeans - matrix of cluster means. One row per mean
%
% Tip: you should load the image data first, e.g.
% [ origimage ] = imread('filename.jpg','jpg');
% Then normalise
% origimage = double(origimage)/255.;

	% get the dimensions of the image data, height x width x 3 - rgb image
	imsize = size(origimage);
	% calculate the number of pixels
	numpixels = imsize(1)*imsize(2);
	% repackage the data into an N x 3 matrix (each row is a data point).
	for pixel=1:numpixels
		% turn pixel into pixel location
		[i,j] = ind2sub(imsize(1:2),pixel);
		% insert pixel data into rawdata matrix
        % normalise rgb data in process
		rawdata(pixel,:) = double(origimage(i,j,:));
	end
	% cluster data
	[ clusterids, clustermeans ] = kmeans(rawdata,numclusters);
	% repackage the data into image format
	for pixel=1:numpixels
		% turn pixel into pixel location
		[i,j] = ind2sub(imsize(1:2),pixel);
		% insert cluster mean into corresponding pixel.
		clusterid = clusterids(pixel);
		clusterimage(i,j,:) = clustermeans(clusterid,:);
		% also store a map of each pixel's cluster id
		clustermap(i,j) = clusterid;
    end
    % normalise clusterimage
    clusterimage = clusterimage/256.
end
