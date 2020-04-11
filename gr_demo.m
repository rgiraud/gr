
clear all
close all
clc

%Image loading
img = imread('peppers.png');

%Decomposition into superpixels
lab_map = int32(superpixels(img,300,'compactness',10));

%Regularity evaluation (MATLAB)
[gr] = gr_metric(lab_map);

%Display
figure,
BW = boundarymask(lab_map);
imshow(imoverlay(img,BW,'cyan'),'InitialMagnification',67)
title(sprintf('Global Regularity (GR) = %1.3f',gr));



