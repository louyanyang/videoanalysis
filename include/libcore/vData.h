#ifndef __DATA_H__
#define __DATA_H__

#include <opencv2/core/core.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <boost/variant.hpp>
#include "libcore/ocean_ai_va_inl.h"

namespace ocean
{
	namespace ai
	{
		namespace core
		{

			class vData
			{
			protected:

				typedef boost::variant<cv::Mat, cv::gpu::GpuMat> internal_type;
			
			public:
				vData(){};
				virtual ~vData(){};

			public:

			    virtual int cols() const = 0;
				virtual int rows() const = 0;
				virtual int type() const = 0;
				virtual int step() const = 0;
				virtual int channels() const = 0;
				virtual void* data() const = 0;
				virtual DataType data_type() const = 0;
				virtual internal_type toCV() = 0;
		
			};


			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			class vData_cpu : public vData
			{
			public:
				vData_cpu();
				vData_cpu(int rows, int cols, int type);
				vData_cpu(int rows, int cols, int type, void* data_cpu);
				vData_cpu(const vData_cpu& m, const cv::Rect& roi);
				vData_cpu(const vData_cpu& m);
				vData_cpu& operator = (const vData_cpu& m);
				virtual ~vData_cpu();

				virtual int cols() const override;
				virtual int rows() const override;
				virtual int type() const override;
				virtual int step() const override;
				virtual int channels() const override;
				virtual void* data() const override;
				virtual DataType data_type() const override;
				virtual internal_type toCV() override;

			private:
				cv::Mat locateROI(const cv::Rect& roi) const;

		    public:
				cv::Mat mat;
			};


			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			class vData_gpu : public vData
			{
			public:
				vData_gpu();
				vData_gpu(int rows, int cols, int type);
				vData_gpu(int rows, int cols, int type, void* data_gpu);
				vData_gpu(const vData_gpu& m, const cv::Rect& roi);
				vData_gpu(const vData_gpu& m);
				vData_gpu& operator = (const vData_gpu& m);
				virtual ~vData_gpu();


			public:

				virtual int cols() const override;
				virtual int rows() const override;
				virtual int type() const override;
				virtual int step() const override;
				virtual int channels() const override;
				virtual void* data() const override;
				virtual DataType data_type() const override;
				virtual internal_type toCV() override;

			private:

				cv::gpu::GpuMat locateROI(const cv::Rect& roi) const;

			public:

				cv::gpu::GpuMat mat_gpu;

			};




		}/*ocean*/
	}/*ai*/
}/*ocean*/



#endif