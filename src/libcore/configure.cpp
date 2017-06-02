#include <google/protobuf/text_format.h>
#include <fstream>
#include <boost/filesystem.hpp>
#include "libcore/configure.h"



namespace ocean
{
	namespace ai
	{
		namespace core
		{

			boost::once_flag Configure::init_flag = BOOST_ONCE_INIT;
			boost::once_flag Configure::global_init_flag = BOOST_ONCE_INIT;
			Configure::configure_type Configure::instance;
			std::string Configure::configure_path;


			Configure::Configure()
			{
				m_runtime_params = boost::make_shared<va::RunTimeParams>();

				namespace fs = boost::filesystem;
				fs::path path(configure_path + "/configs/runtime_params.config");
				if (fs::exists(path))
				{
					std::string runtime_params_str;
					if (!LoadParam(path.string(), runtime_params_str))
						throw std::logic_error("Load runtime params error!");


					if (!google::protobuf::TextFormat::ParseFromString(runtime_params_str, m_runtime_params.get()))
						throw std::logic_error("Load runtime params error!");
				}
				else
				{
					m_runtime_params->set_log_file("./Logs/algorithm_default");
					m_runtime_params->set_circular_buffer_size(100);
					m_runtime_params->set_block_interval(5);
					m_runtime_params->set_detect_batch_size(2);
					m_runtime_params->set_object_max_num(64);
					m_runtime_params->set_syncqueue_size(10000);
				}
			}


			Configure::~Configure()
			{}


			Configure::configure_type Configure::Instance()
			{
				boost::call_once(init_flag, &Configure::init);
				return instance;
			}

			void Configure::init()
			{
				instance = boost::shared_ptr<Configure>(new Configure);
			}


			Configure::runtime_params_type Configure::GetRunTimeParams()
			{
				return m_runtime_params;
			}

			void Configure::GlobalInit(const std::string& path)
			{
				boost::call_once(global_init_flag, &Configure::path_init, path);
				Instance();
			}

			void Configure::path_init(const std::string& path)
			{
				if (path.empty())
				{
					configure_path = ".";
				}

				if (path[path.length() - 1] == '/')
				{
					configure_path = path.substr(0, path.length() - 1);
				}
				else
				{
					configure_path = path;
				}
			}


			std::string Configure::Configurations_toString()
			{
				std::string runtime_params_info = m_runtime_params->DebugString();

				runtime_params_info.replace(runtime_params_info.begin(), runtime_params_info.end(), "\n", " | ");
				
				return runtime_params_info;
			}


			bool LoadParam(const std::string& filename, std::string& runtime_params)
			{
				if (filename.empty())
					return false;

				std::fstream fin(filename, std::ios::in);
				if (!fin)
					return false;

				std::istreambuf_iterator<char> beg(fin), end;
				runtime_params = std::string(beg, end);
				return true;
			}

			bool SaveParam(const std::string& filename, const std::string& runtime_params)
			{
				if (filename.empty())
					return false;

				std::fstream fout(filename, std::ios::out);
				if (!fout)
					return false;

				//fout << runtime_params;
				fout.write(runtime_params.c_str(), runtime_params.length());
				return true;
			}

		}/*core*/
	}/*ai*/
}/*ocean*/