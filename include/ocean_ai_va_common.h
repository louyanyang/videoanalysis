#ifndef __OCEAN_AI_VIDEOANALYSIS_COMMON_H__
#define __OCEAN_AI_VIDEOANALYSIS_COMMON_H__


#if (defined(_WIN64)|| defined(_WIN32) || defined(WIN32)) && defined(DLL_EXPORTS)
#define EXPORTS_API __declspec(dllexport)
#else
#define EXPORTS_API
#endif

#include <string>
#include <vector>
#include <boost/cstdint.hpp>
#include <boost/function.hpp>
#include <opencv2/opencv.hpp>

namespace ocean
{
	namespace ai
	{

		enum class STATUS :int
		{
			SUCCESS = 0,
			INVALID_INPUT,
			UNKNOWN_ERROR,
		};

		enum class TaskType:int
		{
			ABSTRACT = 0,               //检测目标、摘取目标关键帧信息
			SYNOPSIS,                   //检测目标，不做摘取
			SEARCH                      //目标半结构化特征提取
		};

		enum class ObjectLabel :int
		{
			PERSON = 0,
			VEHICLE,
			BIKE,
			TRIKE,
		};

		struct InitParams
		{
			int object_filter;
			int skip_num;
			TaskType task_type;
			std::string model_path;
		};


		struct ObjectInfo 
		{
			ObjectLabel label;
			unsigned int track_idx;
			cv::Mat key_img;
			cv::Rect location;
		};

		struct VideoAnalysisResult
		{
			cv::Mat current_frame;
			boost::uint64_t time_stamp;
			std::vector<ObjectInfo> objects;
		};

		typedef boost::function<void(const VideoAnalysisResult&)> VideoAnalysisResultCallback;

	}/*ai*/
} /*ocean*/
#endif