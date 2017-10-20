#include "stdafx.hpp"
#include "shadertoy/BufferConfig.hpp"

using namespace std;
using namespace oglplus;

namespace fs = boost::filesystem;

using namespace shadertoy;

bool InputConfig::enabled() const
{
	return !id.empty() && !type.empty() &&
			(type != "texture" || !source.empty());
}

InputConfig::InputConfig()
	: id(),
	  type(),
	  source(),
	  wrap(TextureWrap::Repeat),
	  minFilter(TextureMinFilter::Linear),
	  magFilter(TextureMagFilter::Linear)
{
}
