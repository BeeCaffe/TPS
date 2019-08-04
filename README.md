# TPS
###The thin plate spline interpolation of illumination compensation of projector-camera system.

This program is an implement version of paper '''Robust,Error-Tolerant Photomtric Projector Compensation''',which is used to do a illumination compensation of projector-camera system in txexture screen.However, our goal of implementing this paper is to weak the inner-reflection in the immersive projector-camera
system,as a contrast experiment of our work.And, In the process of reproducing this paper, we have met many problem,so we suppose to provide convenience for those people who suppose to do the same thing.Meanwhile,if you want to get more detail information about this program, you would better to refer the paper of ```Robust Error-Tolerant Photomtric Projector Compensation```.

# Environment
		ubuntu 18.04.1
		g++ 7.4.0
		opencv 3.4.6
		clion


# Useage
## Method one:
- using the IDE of **Clion** open this project
- Enter the sub directory of test/main.cpp
- Click the **Run** button to run ```computeAllWeight```
- Click the **Run** button to run ```compenImages```

Deverse to mention that,you should ```compute all the weight matrix first``` and ```use those weight matrix to compensate images```.And the weight computation process may be time cost.For 1024x768 images, my compute has cost 10 hours to compute all points's weight matrix,and those weights have been saved in specified path,which is able to modify in `config/config.txt`.

## Configure File
- `CameraImagesRoot` : The diectory path where save the camera capture images.
- `ProjectImagesRoot` : The diectory path where save the projection images. 
- `WeightSaveRoot`: where save the weight matrix,for 1024x768 images,it may costs 3GB space.
- `CompenImagesRoot` : where save the images you suppose to compensate.
- `CompenSaveRoot` : where save the compensated images.

# Result
- Uncompensate Image


![Uncompensate Image](https://github.com/BeeCaffe/TPS/blob/master/resource/compen/00061.jpg)
- Compensated Image


![Compensated Image](https://github.com/BeeCaffe/TPS/blob/master/resource/compened/1.jpg)
