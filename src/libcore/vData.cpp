#include "libcore/vData.h"


namespace ocean
{
	namespace ai
	{
		namespace core
		{

			vData_cpu::vData_cpu()
			{}

			vData_cpu::vData_cpu(int rows, int cols, int type)
			{
				mat = cv::Mat(rows, cols, type);
			}
			vData_cpu::vData_cpu(int rows, int cols, int type, void* data_cpu)
			{
				mat = cv::Mat(rows, cols, type,data_cpu);
			}
			vData_cpu::vData_cpu(const vData_cpu& m, const cv::Rect& roi)
			{
				mat = m.locateRoi(roi);
			}
			vData_cpu::vData_cpu(const vData_cpu& m)
			{
				mat = m.mat;
			}
			vData_cpu& vData_cpu::operator = (const vData_cpu& m)
			{
				mat = m.mat;
			}

			cv::Mat vData_cpu::locate_roi(const cv::Rect& roi) const
			{
				return mat(roi);
			}
			vData_cpu::internal_type vData_cpu::toCV() 
			{
				return mat;
			}


			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			vData_gpu::vData_gpu()
			{}

			vData_gpu::vData_gpu(int rows, int cols, int type)
			{
				mat_gpu = cv::gpu::GpuMat(rows, cols, type);
			}
			vData_gpu::vData_gpu(int rows, int cols, int type, void* data_gpu)
			{
				mat_gpu = cv::gpu::GpuMat(rows, cols, type, data_gpu);
			}
			vData_gpu::vData_gpu(const vData_gpu& m, const cv::Rect& roi)
			{
				mat_gpu = m.locate_roi(roi);
			}
			vData_gpu::vData_gpu(const vData_gpu& m)
			{
				mat_gpu = m.mat_gpu;
			}
			vData_gpu& vData_gpu::operator = (const vData_gpu& m)
			{
				mat_gpu = m.mat_gpu;
			}

			cv::gpu::GpuMat vData_gpu::locate_roi(const cv::Rect& roi) const
			{
				return mat_gpu(roi);
			}
			vData_gpu::internal_type vData_gpu::toCV()
			{
				return mat_gpu;
			}



		}/*core*/

	}/*ai*/

}/*ocean*/