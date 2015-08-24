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

#ifndef RANGER_EVENT_TRIGGER_HPP
#define RANGER_EVENT_TRIGGER_HPP

#ifndef SWIG
#include <functional>

struct event;
struct event_base;
#endif	// !SWIG

namespace ranger { namespace event {

#ifndef SWIG
class dispatcher;
#endif	// !SWIG

class trigger {
public:
#ifndef SWIG
	using event_handler = std::function<void(trigger&)>;
#endif	// !SWIG

	explicit trigger(dispatcher& disp);

#ifndef SWIG
	template <class T>
	trigger(dispatcher& disp, T&& handler)
		: trigger(disp) {
		m_event_handler = std::forward<T>(handler);
	}
#endif	// !SWIG

	~trigger();

#ifndef SWIG
	trigger(const trigger&) = delete;
	trigger& operator = (const trigger&) = delete;

	template <class T>
	void set_event_handler(T&& handler) {
		m_event_handler = std::forward<T>(handler);
	}

	const event_handler& get_event_handler() const {
		return m_event_handler;
	}
#endif	// !SWIG

	void active();
	void close() {
		trigger(std::move(*this));
	}

#ifndef SWIG
private:
	trigger(trigger&& rhs)
		: m_event(rhs.m_event)
		, m_event_handler(std::move(rhs.m_event_handler)) {
		rhs.m_event = nullptr;
	}

	void init(event_base* base);

	struct event* m_event;
	event_handler m_event_handler;
#endif	// !SWIG
};

} }

#endif	// RANGER_EVENT_TRIGGER_HPP