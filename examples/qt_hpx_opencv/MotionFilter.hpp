#ifndef MOTIONFILTER_H
#define MOTIONFILTER_H

#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"

// Boost Accumulators
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/weighted_median.hpp>

class MotionFilter;
typedef boost::shared_ptr<MotionFilter> MotionFilter_SP;

class PSNRFilter;
class Filter;

struct MotionFilterParams {
    int          threshold;
    double       average;
    int          erodeIterations;
    int          dilateIterations;
    double       blendRatio;
    int          displayImage;
};

//
// Filter which computes some motion estimates
//
class MotionFilter {
public:
   MotionFilter();
   MotionFilter(MotionFilterParams motionFilterParams);
  ~MotionFilter();
  //
  virtual void process(const cv::Mat &image);
  //
  void DeleteTemporaryStorage();
  void countPixels(const cv::Mat &image);

  Filter      *renderer;

  //
  // output values
  //
  double       motionEstimate;
  double       logMotion;
  double       rollingMean;
  double       normalizedMotion;
  double       eventLevel;

  //
  // GUI tunable parameters:
  MotionFilterParams mfp;

  int          threshold;
  double       average;
  int          erodeIterations;
  int          dilateIterations;
  double       blendRatio;
  int          displayImage;
  //
  // GUI non-tunable params
  double       triggerLevel;
  int          frameCount;

  //
  // Temporary images
  //
  cv::Size  imageSize;
  cv::Mat   greyScaleImage;
  cv::Mat   thresholdImage;
  cv::Mat   blendImage;
  cv::Mat   movingAverage;
  cv::Mat   difference;
  cv::Mat   floatImage;
  cv::Size  text_size;
  //
  //
  cv::Mat  lastFrame;

protected:
};

#endif
