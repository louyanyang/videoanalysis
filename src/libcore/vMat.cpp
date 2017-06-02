#include "libcore/vMat.h"
//#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>



namespace ocean
{
	namespace ai
	{
		namespace core
		{
			vMat::vMat(){}
			vMat::vMat(DataType data_type, int rows, int cols, int type)
			{
				switch (data_type)
				{
				case ocean::ai::core::DataType::DATA_CPU:
					m_data = boost::make_shared<vData_cpu>(rows,cols,type);
					break;
				case ocean::ai::core::DataType::DATA_GPU:
					m_data = boost::make_shared<vData_gpu>(rows, cols, type);
					break;
				default:
					throw std::logic_error("unknown data type!");
				}
			
			}
			//vMat::vMat(DataType data_type, int rows, int cols, int type, void* data_ptr /*= nullptr*/)
			//{
			//	switch (data_type)
			//	{
			//	case ocean::ai::core::DataType::DATA_CPU:
			//		m_data = boost::make_shared<vData_cpu>(rows, cols, type,data_ptr);
			//		break;
			//	case ocean::ai::core::DataType::DATA_GPU:
			//		m_data = boost::make_shared<vData_gpu>(rows, cols, type,data_ptr);
			//		break;
			//	default:
			//		throw std::logic_error("unknown data type!");
			//	}
			//
			//}
			vMat::vMat(const vMat& m, const cv::Rect& roi)
			{
				m_data = m.m_data;
			}
			vMat::vMat(const vMat& m)
			{
			
			}
			vMat::~vMat(){}



		}/*core*/
	}/*ai*/
}/*ocean*/