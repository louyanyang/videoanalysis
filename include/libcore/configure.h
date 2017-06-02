#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__


#include <boost/make_shared.hpp>
#include <boost/thread/once.hpp>
#include "configure.pb.h"

namespace ocean
{
	namespace ai
	{
		namespace core
		{
			class Configure
			{
				typedef boost::shared_ptr<Configure> configure_type;
				typedef boost::shared_ptr<va::RunTimeParams> runtime_params_type;
			public:
				~Configure();

			public:

				runtime_params_type GetRunTimeParams();

				std::string Configurations_toString();

			public:
				static configure_type Instance();

				static void GlobalInit(const std::string& path);

			private:
				Configure();

				static void init();

				static void path_init(const std::string& path);

			private:

				static configure_type instance;
				static boost::once_flag init_flag;
				static boost::once_flag global_init_flag;
				static std::string configure_path;

			private:
				runtime_params_type m_runtime_params;


			};


			bool LoadParam(const std::string& filename, std::string& runtime_params);
			bool SaveParam(const std::string& filename, std::string& runtime_params);


		}/*core*/
	}/*ai*/
}/*ocean*/

#endif