C++ implementation of inference of mobilenet

# mobilenet
Mobilenet [1] for reference of multi-label classification. And a run exapmle on voc2007 [2] is provided. The result is exectly the same with the caffe version. The weight is trained on caffe with a pretrained mobilent on Imagenet [3], and splited into several binary files. The convolution and matrix multiplication operations are operated with 'for' loop for showing operational details, and the faster cblas version will be uploaded later.

Examples of test_list.txt and test_labels.txt, and you can create you own files:
test_list.txt
img1_name.jpg
img2_name.jpg
...

test_labels.txt
0 0 0 0 0 1 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0 0 0
...

The network will print the two accuracy resutls (the mAP result is not provided): one label correct and all labels correct. You can also modify utils.cpp to test one image.

#Requirments:
1. opencv

#Note:
1. The code is tested on vs2015. 
2. The 'for' loop operations of convolution and matrix mltiplication refer to [4], but the two-dimensional array in convolution is replaced with one-dimensional array.

#References
[1] Howard A G, Zhu M, Chen B, et al. Mobilenets: Efficient convolutional neural networks for mobile vision applications. arXiv preprint arXiv:1704.04861, 2017.
[2] http://host.robots.ox.ac.uk/pascal/VOC/voc2007/
[3] http://www.image-net.org/
[4] https://blog.csdn.net/qiaofangjie/article/details/18042407