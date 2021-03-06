// Copyright (c) 2015, RangerUFO
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// 
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// 
// * Neither the name of ranger_event nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef RANGER_EVENT_SIGNAL_HPP
#define RANGER_EVENT_SIGNAL_HPP

#ifndef SWIG
#include "ranger/event/detail/signal_impl.hpp"
#include <functional>
#include <memory>
#endif	// !SWIG

namespace ranger { namespace event {

#ifndef SWIG
class dispatcher;
#endif	// !SWIG

class signal {
public:
#ifndef SWIG
	using event_handler = std::function<void(signal&)>;
#endif	// !SWIG

	signal(dispatcher& disp, int sig)
		: m_impl(new detail::signal_impl(disp, sig)) {
		m_impl->set_handle(this);
	}

#ifndef SWIG
	template <class T>
	signal(dispatcher& disp, int sig, T&& handler)
		: signal(disp, sig) {
		m_event_handler = std::forward<T>(handler);
	}

	signal(const signal&) = delete;
	signal& operator = (const signal&) = delete;

	signal(signal&& rhs) noexcept
		: m_impl(std::move(rhs.m_impl))
		, m_event_handler(std::move(rhs.m_event_handler)) {
		if (m_impl) {
			m_impl->set_handle(this);
		}
	}

	signal& operator = (signal&& rhs) noexcept {
		if (this != &rhs) {
			auto tmp = std::move(rhs);
			swap(tmp);
		}

		return *this;
	}

	template <class T>
	void set_event_handler(T&& handler) {
		m_event_handler = std::forward<T>(handler);
	}

	const event_handler& get_event_handler() const {
		return m_event_handler;
	}
#endif	// !SWIG

	void active() {
		if (m_impl) {
			m_impl->active();
		}
	}

	void close() {
		signal(std::move(*this));
	}

#ifndef SWIG
	void swap(signal& rhs) noexcept {
		if (this != &rhs) {
			using std::swap;
			swap(m_impl, rhs.m_impl);
			swap(m_event_handler, rhs.m_event_handler);

			if (m_impl) {
				m_impl->set_handle(this);
			}

			if (rhs.m_impl) {
				rhs.m_impl->set_handle(&rhs);
			}
		}
	}

private:
	std::unique_ptr<detail::signal_impl> m_impl;
	event_handler m_event_handler;
#endif	// !SWIG
};

#ifndef SWIG
inline void swap(signal& lhs, signal& rhs) noexcept {
	lhs.swap(rhs);
}
#endif	// !SWIG

} }

#endif	// RANGER_EVENT_SIGNAL_HPP
