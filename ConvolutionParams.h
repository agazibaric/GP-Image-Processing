#include <ECF/ECF_base.h>

class ConvolutionParams {
    public:
        int width;
        int height;
        int convolutionSize;
        double percentage;
        int includeCentralPixel;
        
        int delta;
        int imageSize;

        // Number of rows and cols for submatrix search
        int nRows;
        int nCols;

        // Submatrix starting position on the image
        int rowStart;
        int colStart;
};

using ConvolutionParamsP = boost::shared_ptr<ConvolutionParams>;
