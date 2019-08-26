#ifndef _SHADERTOY_BACKENDS_GL4_WRAPPER_CONTEXT_HPP_
#define _SHADERTOY_BACKENDS_GL4_WRAPPER_CONTEXT_HPP_

#include "shadertoy/backends/gl4/pre.hpp"

#include "shadertoy/backends/gx/backend.hpp"
#include "shadertoy/backends/gx/state_tracker.hpp"

SHADERTOY_BACKENDS_GL4_NAMESPACE_BEGIN
struct backend_ops
{
	void GetIntegerv(GLenum pname, GLint *params) const;
	GLenum GetError() const;
	void UseProgram(GLuint program) const;

	void bind_texture_unit(GLuint unit, std::optional<std::reference_wrapper<const gx::texture>> texture) const;
	void bind_sampler_unit(GLuint unit, std::optional<std::reference_wrapper<const gx::sampler>> sampler) const;

	void bind_texture(GLenum target, std::optional<std::reference_wrapper<const gx::texture>> texture) const;
	void active_texture(GLuint unit) const;
};

/**
 * @brief OpenGL state tracker
 */
class shadertoy_EXPORT backend : public gx::state_tracker<backend_ops, gx::backend>
{
	public:
	backend(const backend &) = delete;
	backend &operator=(const backend &) = delete;

	/**
	 * @brief Creates a new context state tracker
	 *
	 * @param state_tracking true if this context tracks state
	 * @param checks_enabled true if this context checks calls
	 */
	backend(bool state_tracking = true, bool checks_enabled = true);

	// gx backend implementation
	// Factory methods

	std::unique_ptr<gx::buffer> make_buffer(GLenum target) override;

	std::unique_ptr<gx::framebuffer> make_framebuffer() override;

	std::unique_ptr<gx::program> make_program() override;

	std::unique_ptr<gx::attrib_location> make_attrib_location(GLint location) override;

	std::unique_ptr<gx::uniform_location> make_uniform_location(const gx::program &program, GLint location) override;

	std::unique_ptr<gx::query> make_query(GLenum target) override;

	std::unique_ptr<gx::renderbuffer> make_renderbuffer() override;

	std::unique_ptr<gx::sampler> make_sampler() override;

	std::unique_ptr<gx::shader> make_shader(GLenum shaderType) override;

	std::unique_ptr<gx::texture> make_texture(GLenum target) override;

	std::unique_ptr<gx::vertex_array> make_vertex_array() override;

	std::unique_ptr<gx::draw_state> make_draw_state() override;

	// Bind methods

	void bind_default_framebuffer(GLenum target) override;

	// Viewport methods

	void get_viewport(GLint viewport[4]) const override;

	void set_viewport(GLint x, GLint y, GLsizei width, GLsizei height) override;

	/**
	 * @brief Return the current context
	 */
	static backend &current();
};
SHADERTOY_BACKENDS_GL4_NAMESPACE_END

#endif /* _SHADERTOY_BACKENDS_GL4_WRAPPER_CONTEXT_HPP_ */
