# TPS
The thin plate spline interpolation of illumination compensation of projector-camera system.

		This program is an implement version of paper "Robust,Error-Tolerant Photomtric Projector Compensation",which is used to do a illumination compensation of
		projector-camera system in txexture screen.However, our goal of implementing this paper is to weak the inner-reflection in the immersive projector-camera
		system,as a contrast experiment of our work.And, In the process of reproducing this paper, we have met many problem,so we suppose to provide convenience 
		for those people who suppose to do the same thing.Meanwhile,if you want to get more detail information about this program, you would better\<br>to refer the paper of ```Robust Error-Tolerant Photomtric Projector Compensation```.

# Environment
		ubuntu 18.04.1
		g++ 7.4.0
		opencv 3.4.6
		clion

# Useage
## Method one:
		* using the IDE of *CLion* open this projection
		* Enter the sub directory of test/main.cpp
		* Click the *Run* button
		Deverse to mention that,you should compute all the weight matrix first and use those weight matrix to compensate images.and the weight\<br>computation process may be time cost.For 1024x768 images, my compute need 10 hours to compute all points's weight matrix.
