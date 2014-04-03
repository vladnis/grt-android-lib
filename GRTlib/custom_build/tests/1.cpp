#include "GRT.h"

#include <sys/time.h>
#include <time.h>

using namespace GRT;

int main(int argc, const char * argv[]) {
  LabelledClassificationData trainingData;
  struct timeval start, end;
   struct timespec ts_start;
   struct timespec ts_end;

  if (!trainingData.loadDatasetFromFile("/data/local/tmp/1.in")) {
    cout << "ERROR: Failed to load trainig data from file\n";
    return EXIT_FAILURE;
  }

  cout << "DataLoaded\n";

  trainingData.printStats();

  LabelledClassificationData testData = trainingData.partition(80);
  testData.printStats();

  GestureRecognitionPipeline pipeline;
  pipeline.setClassifier(ANBC());

  clock_gettime(CLOCK_MONOTONIC, &ts_start);
  if (!pipeline.train(trainingData) ) {
    cout << "ERROR: Failed to save the pipeline!\n";
    return EXIT_FAILURE;
  }
  clock_gettime(CLOCK_MONOTONIC, &ts_end);

  printf("%ld", ts_end.tv_nsec - ts_start.tv_nsec);

  if (!pipeline.savePipelineToFile("/data/local/tmp/HelloWorldPipeline")) {
    cout << "ERROR: Failes to save the pipeline!\n";
    return EXIT_FAILURE;
  }

  if (!pipeline.loadPipelineFromFile("/data/local/tmp/HelloWorldPipeline")) {
    cout << "ERROR: Failed to load pipeline!\n";
    return EXIT_FAILURE;
  }


  gettimeofday(&start, NULL);
  if (!pipeline.test(testData)) {
    cout << "ERROR: Failed to test the pipeline!\n";
    return EXIT_FAILURE;
  }
  gettimeofday(&end, NULL);

  printf("Time spent in testing: %ld\n", ((end.tv_sec * 1000000 + end.tv_usec)
        - (start.tv_sec * 1000000 + start.tv_usec)));

  //Print some stats about the testing
  cout << "Test Accuracy: " << pipeline.getTestAccuracy() << endl;

  cout << "Precision: ";
  for(UINT k=0; k<pipeline.getNumClassesInModel(); k++){
    UINT classLabel = pipeline.getClassLabels()[k];
    cout << "\t" << pipeline.getTestPrecision(classLabel);
  }cout << endl;

  cout << "Recall: ";
  for(UINT k=0; k<pipeline.getNumClassesInModel(); k++){
    UINT classLabel = pipeline.getClassLabels()[k];
    cout << "\t" << pipeline.getTestRecall(classLabel);
  }cout << endl;

  cout << "FMeasure: ";
  for(UINT k=0; k<pipeline.getNumClassesInModel(); k++){
    UINT classLabel = pipeline.getClassLabels()[k];
    cout << "\t" << pipeline.getTestFMeasure(classLabel);
  }cout << endl;

  Matrix< double > confusionMatrix = pipeline.getTestConfusionMatrix();
  cout << "ConfusionMatrix: \n";
  for(UINT i=0; i<confusionMatrix.getNumRows(); i++){
    for(UINT j=0; j<confusionMatrix.getNumCols(); j++){
      cout << confusionMatrix[i][j] << "\t";
    }cout << endl;
  }

  return EXIT_SUCCESS;
}
