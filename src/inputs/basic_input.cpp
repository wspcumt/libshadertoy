#include <epoxy/gl.h>

#include "shadertoy/gl.hpp"

#include "shadertoy/inputs/basic_input.hpp"

#include "shadertoy/utils/assert.hpp"

using namespace shadertoy;
using namespace shadertoy::inputs;

using shadertoy::utils::log;
using shadertoy::utils::error_assert;

basic_input::basic_input() : loaded_(false)
{
	min_filter(GL_NEAREST);
	mag_filter(GL_NEAREST);
}

void basic_input::load()
{
	if (!loaded_)
	{
		log::shadertoy()->trace("Loading input {}", static_cast<const void *>(this));

		load_input();
		loaded_ = true;
	}
}

void basic_input::reset()
{
	if (loaded_)
	{
		log::shadertoy()->trace("Resetting input {}", static_cast<const void *>(this));

		reset_input();
		loaded_ = false;
	}
}

gl::texture *basic_input::use()
{
	// Load if needed
	load();

	return use_input();
}

GLint basic_input::min_filter() const
{
	GLint mf;
	sampler_.get_parameter(GL_TEXTURE_MIN_FILTER, &mf);
	return mf;
}

void basic_input::min_filter(GLint new_min_filter)
{
	sampler_.parameter(GL_TEXTURE_MIN_FILTER, new_min_filter);
}

GLint basic_input::mag_filter() const
{
	GLint mf;
	sampler_.get_parameter(GL_TEXTURE_MAG_FILTER, &mf);
	return mf;
}

void basic_input::mag_filter(GLint new_mag_filter)
{
	sampler_.parameter(GL_TEXTURE_MAG_FILTER, new_mag_filter);
}

void basic_input::wrap(GLint new_wrap)
{
	sampler_.parameter(GL_TEXTURE_WRAP_S, new_wrap);
	sampler_.parameter(GL_TEXTURE_WRAP_T, new_wrap);
	sampler_.parameter(GL_TEXTURE_WRAP_R, new_wrap);
}

gl::texture *basic_input::bind(GLuint unit)
{
	sampler_.bind(unit);
	auto tex(use());

	// Check that we have a texture object
	error_assert(tex != nullptr, "Failed to get texture to bind to unit {} for input {}", unit,
				 static_cast<const void *>(this));

	tex->bind_unit(unit);
	return tex;
}
