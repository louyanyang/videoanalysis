#ifndef __DATA_H__
#define __DATA_H__

#include <opencv2/core/core.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <boost/variant.hpp>

namespace ocean
{
	namespace ai
	{
		namespace core
		{

			//class data
			//{
			//public:
			//	data();
			//	/*data(int rows, int cols, int type);
			//	data(int rows, int cols, int type, void* data);
			//	data(const data& m, const cv::Rect& roi);
			//	data(const data& m);
			//	data& operator = (const data& m);*/
			//	virtual ~data();
			//public:

			//    virtual int cols() const = 0;
			//	virtual int rows() const = 0;
			//	virtual int type() const = 0;
			//	virtual int step() const = 0;

			//protected:

			//
			//};


			///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			//class data_cpu : public data
			//{
			//public:
			//	data_cpu();
			//	data_cpu(int rows, int cols, int type);
			//	data_cpu(int rows, int cols, int type, void* data_cpu);
			//	data_cpu(const data_cpu& m, const cv::Rect& roi);
			//	data_cpu(const data_cpu& m);
			//	data_cpu& operator = (const data_cpu& m);
			//	virtual ~data_cpu();

			//	virtual int cols() const override;
			//	virtual int rows() const override;
			//	virtual int type() const override;
			//	virtual int step() const override;

			//private:
			//	cv::Mat getmat();

			//private:
			//	cv::Mat mat;
			//};


			///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			//class data_gpu : public data
			//{
			//public:
			//	data_gpu();
			//	data_gpu(int rows, int cols, int type);
			//	data_gpu(int rows, int cols, int type, void* data_gpu);
			//	data_gpu(const data_gpu& m, const cv::Rect& roi);
			//	data_gpu(const data_gpu& m);
			//	data_gpu& operator = (const data_gpu& m);
			//	virtual ~data_gpu();


			//	virtual int cols() const override;
			//	virtual int rows() const override;
			//	virtual int type() const override;
			//	virtual int step() const override;

			//private:

			//	cv::gpu::GpuMat mat_gpu;

			//};




		}/*ocean*/
	}/*ai*/
}/*ocean*/



#endif