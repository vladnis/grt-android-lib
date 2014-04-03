GRT_SRC_DIR = ../GRT
GRT_CLASSIFICATION_MODULES = ClassificationModules/AdaBoost/*.cpp ClassificationModules/AdaBoost/WeakClassifiers/*.cpp \
                             ClassificationModules/ANBC/*.cpp \
                             ClassificationModules/BAG/*.cpp \
                             ClassificationModules/DecisionTree/*.cpp \
                             ClassificationModules/DTW/*.cpp \
                             ClassificationModules/GMM/*.cpp \
                             ClassificationModules/KNN/*.cpp \
                             ClassificationModules/LDA/*.cpp \
                             ClassificationModules/RandomForests/*.cpp \
                             ClassificationModules/Softmax/*.cpp \
                             ClassificationModules/SVM/*.cpp \
                             ClassificationModules/SVM/LIBSVM/*.cpp \
                             ClassificationModules/HMM/*.cpp \
                             ClassificationModules/MinDist/*.cpp
GRT_CLUSTERING_MODULES = ClusteringModules/GaussianMixtureModels/*.cpp \
                         ClusteringModules/KMeans/*.cpp \
                         ClusteringModules/HierarchicalClustering/*.cpp \
                         ClusteringModules/SelfOrganizingMap/*.cpp
GRT_CONTEXT_MODULES = ContextModules/*.cpp
GRT_DATA_STRUCTURES = DataStructures/*.cpp
GRT_FEATURE_EXTRACTION_MODULES = FeatureExtractionModules/FFT/*.cpp \
                                 FeatureExtractionModules/KMeansQuantizer/*.cpp \
                                 FeatureExtractionModules/MovementIndex/*.cpp \
                                 FeatureExtractionModules/MovementTrajectoryFeatures/*.cpp \
                                 FeatureExtractionModules/PCA/*.cpp \
                                 FeatureExtractionModules/SOMQuantizer/*.cpp \
                                 FeatureExtractionModules/TimeDomainFeatures/*.cpp \
                                 FeatureExtractionModules/TimeseriesBuffer/*.cpp \
                                 FeatureExtractionModules/ZeroCrossingCounter/*.cpp
GRT_PIPELINE = CoreModules/*.cpp
GRT_POST_PROCESSING_MODULES = PostProcessingModules/*.cpp
GRT_PRE_PROCESSING_MODULES = PreProcessingModules/*.cpp
GRT_REGRESSION_MODULES = RegressionModules/ArtificialNeuralNetworks/MLP/*.cpp RegressionModules/LinearRegression/*.cpp RegressionModules/LogisticRegression/*.cpp RegressionModules/MultidimensionalRegression/*.cpp
GRT_UTIL = Util/*.cpp
_GRT_SRC = $(GRT_CLASSIFICATION_MODULES) $(GRT_CLUSTERING_MODULES) $(GRT_CONTEXT_MODULES) $(GRT_DATA_STRUCTURES) \
           $(GRT_FEATURE_EXTRACTION_MODULES) $(GRT_PIPELINE) $(GRT_POST_PROCESSING_MODULES) $(GRT_PRE_PROCESSING_MODULES) \
           $(GRT_REGRESSION_MODULES) $(GRT_UTIL)
GRT_SRC = $(patsubst %,$(GRT_SRC_DIR)/%,$(_GRT_SRC))
GRT_OBJS = $(patsubst %.cpp,%.o,$(GRT_SRC))
GRT_HEADERS = -I$(GRT_SRC_DIR)
GRT_STATIC_LIB = libgrt.a
GRT_SHARED_LIB = libgrt.so
LIBS_FOLDER = libraries
PLATFORM = x86
CC_local = g++
AR_local = ar
CC_armeabi = arm-linux-androideabi-g++
AR_armeabi = arm-linux-androideabi-ar
CC_x86 = i686-linux-android-g++
AR_x86 = i686-linux-android-ar
AR = ${AR_${PLATFORM}}
CC = ${CC_${PLATFORM}}
CFLAGS = -g -Wall -fPIC
GRT_OBJS_DIR = objs

LIBS_armeabi = -llog
LIBS_x86 = -llog
LIBS = ${LIBS_${PLATFORM}}

#Build the GRT static library for OSC and Linux
all: static shared

buildobj: $(GRT_SRC)
	@echo "----------------- Building object files -----------------"
	$(CC) -c $(GRT_SRC) $(GRT_HEADERS) $(CFLAGS) $(LIBS)
	mv -f `find . -maxdepth 1 -name "*.o"` $(GRT_OBJS_DIR)

#Builds the GRT as a static library for OSX and Linux
static: buildobj
	@echo "----------------- Building GRT static library -----------------"
	$(AR) rcs $(LIBS_FOLDER)/$(PLATFORM)/$(GRT_STATIC_LIB) $(GRT_OBJS_DIR)/*.o

#Builds the GRT as a shared library for OSX and Linux
shared: buildobj
	@echo "----------------- Building GRT shared library -----------------"
	$(CC) -shared $(GRT_OBJS_DIR)/*.o -o $(LIBS_FOLDER)/$(PLATFORM)/$(GRT_SHARED_LIB)

#Precompile header files
precompileHeaders:
	$(CC) $(GRT_SRC_DIR)/GRT.h -o GRT.h.gch

.PHONY: clean
clean:
	rm -f *.o $(GRT_OBJS_DIR)/*.o
