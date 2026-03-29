#include <iostream>
#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>


int main(void){

    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
    auto logger = spdlog::default_logger();
    
    logger->info("Reading the image..");
    cv::Mat OriginalImage = cv::imread("D:\\Training\\c++\\ImageProcessing\\opencv\\imgs\\test1.png");

    if(OriginalImage.empty())
    {
        logger->error("Could not read the image");
        return -1;
    }
    logger->info("Image read successfully!");

    cv::Mat HsvImage, mask;

    logger->info("Converting the image to HSV color space..");
    cv::cvtColor(OriginalImage, HsvImage, cv::COLOR_BGR2HSV);

    logger->info("Saving HSV image..");
    cv::imwrite("D:\\Training\\c++\\ImageProcessing\\opencv\\imgs\\hsv_test1.png", HsvImage);
    logger->info("Image Saved..!");

    cv::namedWindow("HSV Trackbars", cv::WINDOW_AUTOSIZE);
    
    int lowH = 0, highH = 179;
    int lowS = 0, highS = 255;
    int lowV = 0, highV = 255;

    cv::createTrackbar("Low H", "HSV Trackbars", &lowH, 179);
    cv::createTrackbar("High H", "HSV Trackbars", &highH, 179);
    cv::createTrackbar("Low S", "HSV Trackbars", &lowS, 255);
    cv::createTrackbar("High S", "HSV Trackbars", &highS, 255);
    cv::createTrackbar("Low V", "HSV Trackbars", &lowV, 255);
    cv::createTrackbar("High V", "HSV Trackbars", &highV, 255);

    while (true)
    {
        
        cv::Scalar lower_bound(lowH, lowS, lowV); // Lower bound for red color in HSV
        cv::Scalar upper_bound(highH, highS, highV); // Upper bound for red color in HSV

        logger->info("Creating a mask for red color..");
        cv::Mat mask1, mask2;
        cv::inRange(HsvImage, lower_bound, upper_bound, mask1);

        mask = mask1;

        // Remove noise from the mask using morphological operations
        logger->info("Removing noise from the mask using morphological operations..");
        cv::erode(mask, mask, cv::Mat());
        cv::dilate(mask, mask, cv::Mat());
        logger->info("Noise removed from the mask..");  

        logger->info("Saving the mask image..");
        cv::imwrite("D:\\Training\\c++\\ImageProcessing\\opencv\\imgs\\mask_test1.png", mask);
        logger->info("Mask image saved..!");

        // Contours
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        logger->info("Contours found: {}", contours.size());

        // Draw contours on the original image
        logger->info("Drawing contours on the original image..");
        cv::Mat ContourImage = OriginalImage.clone();
        cv::drawContours(ContourImage, contours, -1, cv::Scalar(0, 0, 0), 10);
        logger->info("Contours drawn on the original image.."); 

        logger->info("Saving the contour image..");
        cv::imwrite("D:\\Training\\c++\\ImageProcessing\\opencv\\imgs\\contour_test1.png", ContourImage);
        logger->info("Contour image saved..!");
        
        cv::imshow("Original Image", OriginalImage);
        cv::imshow("HSV Image", HsvImage);
        cv::imshow("Mask", mask);
        cv::imshow("Contours", ContourImage);
        
        // Break on ESC key
        if (cv::waitKey(1) == 27) break;

    }

    cv::waitKey(0);
    cv::destroyAllWindows();




    return 0;
}