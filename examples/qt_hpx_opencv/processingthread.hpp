#ifndef PROCESSING_THREAD_H
#define PROCESSING_THREAD_H
//
#include <hpx/config.hpp>
#include <hpx/parallel/execution.hpp>
#include <hpx/parallel/executors/pool_executor.hpp>
//
#include <QMutex>
#include <QWaitCondition>
//
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QtCore/QObject>
//
#include <boost/shared_ptr.hpp>
#include "ConcurrentCircularBuffer.hpp"
typedef boost::shared_ptr< ConcurrentCircularBuffer<cv::Mat> > ImageBuffer;
typedef boost::circular_buffer< int > IntCircBuff;
class ProcessingThread;
typedef boost::shared_ptr<ProcessingThread> ProcessingThread_SP;
//
class Filter;
#include "MotionFilter.hpp"
#include "FaceRecogFilter.hpp"

enum class ProcessingType: int
{
    motionDetection = 0,
    faceRecognition =1,
};

class ProcessingThread : public QObject{
Q_OBJECT;
public:
   ProcessingThread(ImageBuffer buffer,
                    hpx::threads::executors::pool_executor exec,
                    ProcessingType processingType,
                    MotionFilterParams mfp, FaceRecogFilterParams frfp);
  ~ProcessingThread();
  //
  void CopySettings(ProcessingThread *thread);
  //
  void setRootFilter(Filter* filter) {   this->motionFilter->renderer = filter;
                                         this->faceRecogFilter->setRenderer(filter); }
  void setThreshold(int val) { this->motionFilter->threshold = val; }
  void setAveraging(double val) { this->motionFilter->average = val; }
  void setErodeIterations(int val) { this->motionFilter->erodeIterations = val; }
  void setDilateIterations(int val) { this->motionFilter->dilateIterations = val; }
  void setDisplayImage(int image) { this->motionFilter->displayImage = image; }
  void setBlendRatios(double ratio1) { this->motionFilter->blendRatio = ratio1; }
  //
  void setEyesRecogState(int val) { this->faceRecogFilter->setEyesRecogState((bool)val); }
  void setDecimationCoeff(int val) {
    this->faceRecogFilter->setDecimationCoeff(val); }
  int getProcessingTime() { return this->processingTime_ms; }
  void run();
  bool startProcessing();
  bool stopProcessing();

  void setMotionDetectionProcessing();
  void setFaceRecognitionProcessing();
  MotionFilter_SP       motionFilter;
  FaceRecogFilter_SP    faceRecogFilter;

signals:
    void NewData();

private:
  void updateProcessingTime(int time_ms);

  //
  QMutex           stopLock;
  QWaitCondition   stopWait;
  bool             processingActive;
  bool             abort;
  hpx::threads::executors::pool_executor executor;
  //
  ImageBuffer  imageBuffer;
  ProcessingType processingType;
  int processingTime_ms;
  IntCircBuff processingTimes;
};

#endif
