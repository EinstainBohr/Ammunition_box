#include <limits.h> /* PATH_MAX */
#include <stdlib.h>
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "EllipseDetectorYaed.h"
#include <fstream>


using namespace std;
using namespace cv;


int main()
{
    VideoCapture cap(0);
    //if(!cap.isOpened()) return;

    int width = 800;
    int height = 600;

    // Parameters Settings (Sect. 4.2)
    int		iThLength = 16;
    float	fThObb = 3.0f;
    float	fThPos = 1.0f;
    float	fTaoCenters = 0.05f;
    int 	iNs = 16;
    float	fMaxCenterDistance = sqrt(float(width*width + height*height)) * fTaoCenters;

    float	fThScoreScore = 0.6f;

    // Other constant parameters settings.

    // Gaussian filter parameters, in pre-processing
    Size	szPreProcessingGaussKernelSize = Size(5, 5);
    double	dPreProcessingGaussSigma = 1.0;

    float	fDistanceToEllipseContour = 0.1f;	// (Sect. 3.3.1 - Validation)
    float	fMinReliability = 0.8f;	// Const parameters to discard bad ellipses


    // Initialize Detector with selected parameters
    CEllipseDetectorYaed* yaed = new CEllipseDetectorYaed();
    yaed->SetParameters(szPreProcessingGaussKernelSize,
        dPreProcessingGaussSigma,
        fThPos,
        fMaxCenterDistance,
        iThLength,
        fThObb,
        fDistanceToEllipseContour,
        fThScoreScore,
        fMinReliability,
        iNs
        );

    Mat1b gray;
    while(true)
    {
        Mat3b image;
        if(!cap.isOpened()) continue;
        cap >> image;

        cvtColor(image, gray, COLOR_BGR2GRAY);

        vector<Ellipse> ellsYaed;
        Mat1b gray2 = gray.clone();
        yaed->Detect(gray2, ellsYaed);

        vector<Ellipse> gt;

        Mat3b resultImage = image.clone();

        // Draw GT ellipses
        for (unsigned i = 0; i < gt.size(); ++i)
        {
            Ellipse& e = gt[i];
            Scalar color(0, 0, 255);
            ellipse(resultImage, Point(cvRound(e._xc), cvRound(e._yc)), Size(cvRound(e._a), cvRound(e._b)), e._rad*180.0 / CV_PI, 0.0, 360.0, color, 3);
        }

        yaed->DrawDetectedEllipses(resultImage, ellsYaed);

        imshow("Yaed", resultImage);


        waitKey(1);
    }
    return 0;
}


