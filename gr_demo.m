% This code is free to use for any non-commercial purposes.
% If you use this code, please cite:
%   Rémi Giraud, Vinh-Thong Ta and Nicolas Papadakis
%   Evaluation Framework of Superpixel Methods with a Global Regularity Measure
%   Journal of Electronic Imaging (JEI),
%   Special issue on Superpixels for Image Processing and Computer Vision, 2017
%
% (C) Rémi Giraud, 2017
% rgiraud@u-bordeaux.fr, remigiraud.fr/research/gr.php
% University of Bordeaux
%
% Note that implementations of other superpixel metrics can be found here:
% https://www2.eecs.berkeley.edu/Research/Projects/CS/vision/bsds/

clear all
close all
clc

%Image loading
img = imread('peppers.png');

%Decomposition into superpixels
lab_map = int32(superpixels(img,300,'compactness',10));

%Regularity evaluation (MATLAB)
[gr] = gr_metric(lab_map);

%C-mex version (evaluation slightly differs)
mex -O CFLAGS="\$CFLAGS -Wall -Wextra -W -std=c99" ./gr_metric_mex.c -outdir ./
[gr] = gr_metric_mex(int32(lab_map));

%Display
figure,
BW = boundarymask(lab_map);
imshow(imoverlay(img,BW,'cyan'),'InitialMagnification',67)
title(sprintf('Global Regularity (GR) = %1.3f',gr));



