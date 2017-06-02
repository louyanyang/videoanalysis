#ifndef __VMAT_H__
#define __VMAT_H__

#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include "libcore/vData.h"
#include "libcore/buffers_manager.h"
#include "libcore/ocean_ai_va_inl.h"




namespace ocean
{
	namespace ai
	{
		namespace core
		{

			
			class vMat
			{
				friend class BuffersManager;

				typedef boost::variant<cv::Mat, cv::gpu::GpuMat> internal_type;
				typedef boost::shared_ptr<ocean::ai::core::vData> data_type;
				typedef boost::weak_ptr<BuffersManager> manager_type;

			public:
				vMat();
				vMat(const vMat& m, const cv::Rect& roi);
				vMat(const vMat& m);
				 ~vMat();


			public:

				int rows() const;
				int cols() const;
				int step() const;
				int type() const;
				int channels() const;
				int data_type() const;
				void *data() const;

				vMat& operator()(const cv::Rect& roi);

				internal_type toCV();
			private:
				vMat(DataType data_type, int rows, int cols, int type, manager_type manager_ptr);
				vMat(const vMat& vmat, manager_type manager_ptr);

			private:

				data_type m_data;
				manager_type m_manager;

			};


		}
	}/*ai*/
}/*ocean*/



#endif