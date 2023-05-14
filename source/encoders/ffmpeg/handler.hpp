#pragma once
#include "warning-disable.hpp"
#include <cstdint>
#include <map>
#include <string>
extern "C" {
#include <obs.h>
#include <libavcodec/avcodec.h>
}
#include "warning-enable.hpp"

namespace streamfx::encoder::ffmpeg {
	class ffmpeg_factory;
	class ffmpeg_instance;

	struct handler {
		handler(std::string codec);

		virtual bool has_keyframes(ffmpeg_factory* factory);
		virtual bool has_threading(ffmpeg_factory* factory);
		virtual bool is_hardware(ffmpeg_factory* factory);
		virtual bool is_reconfigurable(ffmpeg_factory* factory, bool& threads, bool& gpu, bool& keyframes);

		virtual void adjust_info(ffmpeg_factory* factory, std::string& id, std::string& name, std::string& codec);

		virtual std::string help(ffmpeg_factory* factory);

		virtual void defaults(ffmpeg_factory* factory, obs_data_t* settings);
		virtual void properties(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props);
		virtual void migrate(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings, uint64_t version);
		virtual void update(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings);
		virtual void override_update(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings);
		virtual void log(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings);

		virtual void override_colorformat(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings, AVPixelFormat target_format);

		public:
		typedef std::map<std::string, handler*> handler_map_t;

		static handler_map_t& handlers();
	};
} // namespace streamfx::encoder::ffmpeg
