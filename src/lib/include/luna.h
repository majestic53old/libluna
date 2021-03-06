/**
 * libluna
 * Copyright (C) 2015 David Jolly
 * ----------------------
 *
 * libluna is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libluna is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LUNA_H_
#define LUNA_H_

//#define NDEBUG

#ifndef LUNA
#define LUNA libluna
#endif // LUNA

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "luna_define.h"
#include "luna_exception.h"

using namespace LUNA;

#ifndef COMP
#define COMP component
#endif // COMP

#include "luna_display.h"
#include "luna_input.h"
#include "luna_shader.h"
#include "luna_vertex.h"

using namespace LUNA::COMP;

namespace LUNA {

	typedef enum {
		LUNA_ERR_NONE = 0,
		LUNA_ERR_FAIL,
		LUNA_ERR_INVALID_ARGUMENT,
	} luna_err_t;

	#define LUNA_SUCCESS(_ERR_) ((_ERR_) == LUNA_ERR_NONE)

	enum {
		LUNA_EVT_SETUP,
		LUNA_EVT_START,
		LUNA_EVT_STOP,
		LUNA_EVT_TEARDOWN,

		// user-defined
	};

	typedef luna_err_t (*luna_draw_cb)(
		__in SDL_Window *,
		__in SDL_GLContext,
		__in void *
		);

	typedef luna_err_t (*luna_evt_cb)(
		__in void *
		);

	typedef luna_err_t (*luna_tick_cb)(
		__in SDL_Window *,
		__in SDL_GLContext,
		__in uint32_t,
		__in void *
		);

	typedef class _luna_draw_config {

		public:

			_luna_draw_config(
				__in_opt luna_draw_cb callback = NULL,
				__in_opt void *context = NULL
				);

			_luna_draw_config(
				__in const _luna_draw_config &other
				);

			~_luna_draw_config(void);

			_luna_draw_config &operator=(
				__in const _luna_draw_config &other
				);

			void clear(void);

			void invoke(
				__in SDL_Window *window,
				__in SDL_GLContext screen
				);

			void set(
				__in luna_draw_cb callback,
				__in_opt void *context = NULL
				);

			virtual std::string to_string(
				__in_opt bool verbose = false
				);

		protected:

			luna_draw_cb m_callback;

			void *m_context;

	} luna_draw_config, *luna_draw_config_ptr;

	typedef class _luna_event_config {

		public:

			_luna_event_config(void);

			_luna_event_config(
				__in const _luna_event_config &other
				);

			virtual ~_luna_event_config(void);

			_luna_event_config &operator=(
				__in const _luna_event_config &other
				);

			void add(
				__in uint32_t type,
				__in luna_evt_cb callback,
				__in_opt void *context = NULL
				);

			void clear(void);

			bool contains(
				__in uint32_t type
				);

			void invoke(
				__in uint32_t type
				);

			void remove(
				__in uint32_t type
				);

			size_t size(void);

			virtual std::string to_string(
				__in_opt bool verbose = false
				);

		protected:

			std::map<uint32_t, std::pair<luna_evt_cb, void *>>::iterator find(
				__in uint32_t type
				);

			std::map<uint32_t, std::pair<luna_evt_cb, void *>> m_config;

	} luna_event_config, *luna_event_config_ptr;

	typedef class _luna_tick_config {

		public:

			_luna_tick_config(
				__in_opt luna_tick_cb callback = NULL,
				__in_opt void *context = NULL
				);

			_luna_tick_config(
				__in const _luna_tick_config &other
				);

			~_luna_tick_config(void);

			_luna_tick_config &operator=(
				__in const _luna_tick_config &other
				);

			void clear(void);

			void invoke(
				__in SDL_Window *window,
				__in SDL_GLContext screen,
				__in uint32_t tick
				);

			void set(
				__in luna_tick_cb callback,
				__in_opt void *context = NULL
				);

			virtual std::string to_string(
				__in_opt bool verbose = false
				);

		protected:

			luna_tick_cb m_callback;

			void *m_context;

	} luna_tick_config, *luna_tick_config_ptr;

	typedef class _luna {

		public:

			~_luna(void);

			static _luna *acquire(void);

			luna_display_ptr acquire_display(void);

			luna_input_ptr acquire_input(void);

			luna_shader_ptr acquire_shader(void);

			luna_shader_program_ptr acquire_shader_program(void);

			luna_vertex_ptr acquire_vertex(void);

			GLuint add_buffer(
				__in GLenum target,
				__in size_t count
				);

			void add_event(
				__in uint32_t type,
				__in luna_evt_cb callback,
				__in_opt void *context = NULL
				);

			GLuint add_shader(
				__in const std::string &input,
				__in bool is_file,
				__in GLenum type
				);			

			GLuint add_shader_program(
				__in const std::vector<GLuint> &ids
				);

			GLuint add_vertex(
				__in size_t count
				);

			void bind_buffer(
				__in GLenum target,
				__in_opt GLuint id = 0
				);

			void bind_vertex(
				__in_opt GLuint id = 0
				);

			size_t buffer_count(
				__in GLuint id
				);

			void clear_draw(void);

			void clear_events(void);

			void clear_shaders(void);

			void clear_shader_programs(void);

			void clear_tick(void);

			void clear_vertex_buffer(void);

			bool contains_buffer(
				__in GLuint id
				);

			bool contains_event(
				__in uint32_t type
				);

			bool contains_shader(
				__in GLuint id
				);

			bool contains_shader_program(
				__in GLuint id
				);

			bool contains_vertex(
				__in GLuint id
				);

			size_t event_count(void);

			void initialize(void);

			void invoke_event(
				__in uint32_t type
				);

			static bool is_allocated(void);

			bool is_initialized(void);

			bool is_running(void);

			void remove_buffer(
				__in GLuint id
				);

			void remove_event(
				__in uint32_t type
				);

			void remove_shader(
				__in GLuint id
				);

			void remove_shader_program(
				__in GLuint id
				);

			void remove_vertex(
				__in GLuint id
				);

			void set_buffer_data(
				__in GLenum target,
				__in const void *data,
				__in size_t length,
				__in GLenum usage
				);

			void set_draw(
				__in const luna_draw_config &config
				);

			void set_events(
				__in const luna_event_config &config
				);

			void set_tick(
				__in const luna_tick_config &config
				);

			size_t shader_count(void);

			GLint shader_program_attribute(
				__in GLuint id,
				__in const std::string &name
				);

			size_t shader_program_count(void);

			GLenum shader_type(
				__in GLuint id
				);

			GLint shader_program_uniform(
				__in GLuint id,
				__in const std::string &name
				);

			void start(
				__in const luna_draw_config &draw_config,
				__in const luna_tick_config &tick_config,
				__in_opt const luna_event_config &event_config = luna_event_config(),
				__in_opt const luna_display_config &display_config = luna_display_config(),
				__in_opt const luna_input_config &input_config = luna_input_config()
				);

			void stop(void);

			std::string to_string(
				__in_opt bool verbose = false
				);

			void uninitialize(void);

			void use_shader_program(
				__in_opt GLuint id = 0
				);

			static std::string version(void);

			size_t vertex_count(
				__in GLuint id
				);

		protected:

			_luna(void);

			_luna(
				__in const _luna &other
				);

			_luna &operator=(
				__in const _luna &other
				);

			static void _delete(void);

			static void external_initialize(void);

			static void external_uninitialize(void);

			void setup(
				__in const luna_draw_config &draw_config,
				__in const luna_tick_config &tick_config,
				__in_opt const luna_event_config &event_config = luna_event_config(),
				__in_opt const luna_display_config &display_config = luna_display_config(),
				__in_opt const luna_input_config &input_config = luna_input_config()
				);

			void teardown(void);

			bool m_initialized;

			static bool m_initialized_external;

			static _luna *m_instance;

			luna_draw_config m_draw_config;

			luna_event_config m_event_config;

			luna_display_ptr m_instance_display;

			luna_input_ptr m_instance_input;

			luna_shader_ptr m_instance_shader;

			luna_shader_program_ptr m_instance_shader_program;

			luna_vertex_ptr m_instance_vertex;

			bool m_running;

			uint32_t m_tick;

			luna_tick_config m_tick_config;

	} luna, *luna_ptr;
}

#endif // LUNA_H_
