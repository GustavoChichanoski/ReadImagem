Background = imread('.\img\gal.bmp');
kernel = [1,0,1;0,1,0;1,0,1];
Background = conv2(Background,kernel);
fullFileName = fullfile(folder,'eigrnface.bmp');
imwrite(Background,fullfileName);