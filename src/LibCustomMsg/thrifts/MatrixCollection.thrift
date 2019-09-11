struct Vector
{
} (
   yarp.name = "yarp::sig::Vector"
   yarp.includefile="yarp/sig/Vector.h"
  )

struct Matrix
{
} (
   yarp.name = "yarp::sig::Matrix"
   yarp.includefile="yarp/sig/Matrix.h"
  )


struct MatrixCollection {
    1: map<string, Vector> vectors;
    2: map<string, Matrix> matrices;
}
