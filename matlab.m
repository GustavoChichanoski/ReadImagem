Background = imread('.\img\gal.bmp');
kernel = [1,0,1;0,1,0;1,0,1];
Background = conv3(Background,kernel);
fullFileName = fullfile(folder,'eigrnface.bmp');
imwrite(Background,fullfileName);